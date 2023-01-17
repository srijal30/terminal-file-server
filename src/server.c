#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>

#include "helpers.h"
#include "networking.h"
#include "server.h"
#include "file.h"

int main(){
	signal(SIGINT, handler);
	debug(1);
	create_semaphore(1, 0666);
	int client = init_server();
	while(1==1){
		REQUEST* req = receive_request(client);
		printf("REQUEST TYPE: %d\n", req->type);
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
		printf("DONE WITH REQUEST\n\n");
	}
	cleanup(client);
	return 0;
}

void accept_file(int client, REQUEST* req){
	gain_access();
	char* file_name = get_next(client, req->bytesNext);
	req = receive_request(client); //get info for content
	char* content = get_next(client, req->bytesNext);
	create_file(file_name, content);
	send_response(client, 1, -1, "File successfully uploaded!");
	free(file_name);
	free(content);
	return_access();
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

void remove_file(int client, REQUEST* req){
	gain_access();
	char* file_name = get_next(client, req->bytesNext);
	if(file_exists(file_name)){
		delete_file(file_name);
		send_response(client, 1, -1, "Deleted the file!");
	}
	else send_response(client, 0, -1, "File doesn't exist!");
	free(file_name);
	return_access();
}

void query(int client, REQUEST* req){
	char* path = get_next(client, req->bytesNext);
	FILEITEM** items = get_items(path);	free(path);
	//get amount of items (excluding NULL)
	int cnt = 0;
	for( ; items[cnt] != NULL; cnt++){}
	send_response(client, 1, cnt, "Queried the items!");
	//send the items to client
	for(int i = 0; i < cnt; i++){
		error_check(write(client, items[i], sizeof(FILEITEM)), "QUERY sending item");
		//send the content
		error_check(write(client, items[i]->content, items[i]->size), "QUERY sending content");
	}
	free_items(items);
}

static void handler(int sig){
	if(sig == SIGINT){
		remove_semaphore();
		exit(0);
	}
}
