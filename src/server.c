#include <stdlib.h>
#include <unistd.h>

#include "helpers.h"
#include "networking.h"
#include "server.h"
#include "file.h"

int main(){
	debug(1);
	int client = init_server();
	while(1==1){
		REQUEST* req = receive_request(client);
		switch(req->type){
			case EXIT:
				cleanup(client);
				exit(0);
			case UPLOAD:
				accept_file(client, req);
				break;
			case DOWNLOAD:
				send_file(client, req);
				break;
			case DELETE:
				remove_file(client, req);
				break;
			case QUERY:
				query(client, req);
				break;
		}
		free(req);
	}
	cleanup(client);
	return 0;
}

//GET ACCESS
void accept_file(int client, REQUEST* req){
	char* file_name = get_next(client, req->bytesNext);
	req = receive_request(client); //get info for content
	char* content = get_next(client, req->bytesNext);
	create_file(file_name, content);
	send_response(client, 1, -1, "File successfully uploaded!");
	free(file_name);
	free(content);
}

void send_file(int client, REQUEST* req){
	char *content, *file_name;
	file_name = get_next(client, req->bytesNext);
	//file might not exist
	if(!file_exists(file_name)) send_response(client, 1, -1, "File doesn't exist!");
	else{
		content = file_content(file_name);
		send_response(client, 1, file_size(file_name), "Preparing to send the file...");
		write(client, content, file_size(file_name));
	}
	free(content);
	free(file_name);
}

//GET ACCESS
void remove_file(int client, REQUEST* req){
	char* file_name = get_next(client, req->bytesNext);
	if(file_exists(file_name)){
		delete_file(file_name);
		send_response(client, 1, -1, "Deleted the file!");
	}
	else send_response(client, 0, -1, "File doesn't exist!");
	free(file_name);
}

//HOW TO SEND NULL?
void query(int client, REQUEST* req){
	char* path = get_next(client, req->bytesNext);
	FILEITEM** items = get_items(path);	free(path);
	//get amount of items (excluding NULL)
	int cnt = 0;
	for( ; items[cnt] != NULL; cnt++){}
	send_response(client, 1, cnt, "Queried the items!");
	//send the items to client
	for(int i = 0; i < cnt; i++) error_check(write(client, items[i], sizeof(FILEITEM)), "QUERY sending item");
	free_items(items);
}

