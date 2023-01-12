#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "networking.h"
#include "server.h"

#include <unistd.h>

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
				printf("UPLOADING...\n");
				char* file = (char*)malloc(req->bytesNext);
				read(client, file, req->bytesNext);
				printf("CONTENT:\n%s\n", file);
				send_response(client, 1, -1, "IT WORKED THANKS!\n");
				free(file);
				break;
			case DOWNLOAD:
				printf("DOWLOADING...\n");
				break;
			
		}
		free(req);
	}

	//cleanup
	cleanup(client);
	return 0;
}
