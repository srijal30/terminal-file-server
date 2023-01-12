#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "helpers.h"
#include "networking.h"
#include "server.h"
#include "file.h"

int main(){
	//server setup 
	char buf[5];
	int client = init_server();

	//APPLICATION
	printf("subserver %d is connected to client %d!\n", getpid(), client);
	//wait for requests from client
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
				break;
		}
		free(req);
	}
	//cleanup
	cleanup(client);
	return 0;
}

void accept_file(int client, REQUEST* req){
	//get the name
	char* file_name = (char*)malloc(req->bytesNext);
	error_check(read(client, file_name, req->bytesNext), "ACCEPTING FILE");
	//get the content
	req = receive_request(client);	
	char* content = (char*)malloc(req->bytesNext);
	error_check(read(client, content, req->bytesNext), "ACCEPTING FILE");
	printf("GOT THE CONTENT OF %s\n%s\n", file_name, content);
	//create the file
	create_file(file_name, content);
	free(file_name);
	free(content);
}

