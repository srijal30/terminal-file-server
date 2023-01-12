#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "file.h"
#include "client.h"
#include "helpers.h"
#include "networking.h"

int main(){
	//connect to server
	char* ip = get_input("enter IP of server: ");
	int server = connect_server(ip); free(ip);
	
	//the application
	while(1){
		//get user input
		printf("\nCHOOSE ONE:\n\t0: EXIT\n\t1: UPLOAD\n\t2: DOWNLOAD\n\t3: DELETE\n\t4: QUERY\n");
		char* input = get_input("choose one: ");
		int type; sscanf(input, "%d", &type); free(input);
		//determine case
		switch(type){
			case EXIT:
				client_exit(server); break;
			case UPLOAD:
				client_upload(server); break;
			case DOWNLOAD:
				client_download(server); break;
			case DELETE:
				client_delete(server); break;
			case QUERY:
				client_query(server); break;
			default:
				printf("SOMETHING WENT WRONG!\n"); exit(1); break;
		}
	}
	//cleanup
	cleanup(server);
	return 0;
}

void client_exit(int server){
	send_request(server, EXIT, -1);
	cleanup(server);
	printf("EXITING...\n");
	exit(0);
}

void client_upload(int server){
	//get valid filename
	char* file_name = get_input("file to upload: ");
	while(!file_exists(file_name))
		file_name = get_input("FILE DOES NOT EXIST!\nfile to upload: ");
	//get the content
	char* content = file_content(file_name);

	//send message to server
	//name of file
	send_request(server, UPLOAD, strlen(file_name));
	error_check(write(server, file_name, strlen(file_name)), "SENDING FILE");
	//content of file
	send_request(server, UPLOAD, file_size(file_name));
	error_check(write(server, content, file_size(file_name)), "SENDING FILE");

	//get the response
	RESPONSE* res = receive_response(server);
	printf("RESPONSE:\nSTATUS: %d\nBYTES_NEXT: %d\nMESSAGE: %s\n", res->status, res->bytesNext, res->message);
	free(file_name);
	free(content);
}

void client_download(int server){
	
}

void client_query(int server){
	
}

void client_delete(int server){
	
}

