#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "helpers.h"
#include "networking.h"

int main(){
	//connect to server
	char* ip = get_input("enter IP of server: ");
	int server = connect_server(ip);
	free(ip);

	//the application
	while(1){
		printf("\nCHOOSE ONE:\n\t0: EXIT\n\t1: UPLOAD\n\t2: DOWNLOAD\n\t3: DELETE\n\t4: QUERY\n");
		char* input = get_input("choose one: ");
		int type; sscanf(input, "%d", &type); free(input);
		switch(type){
			case EXIT:
				printf("EXITING...\n"); cleanup(server); return 0; 
			case UPLOAD:
				client_upload(); break;
			case DOWNLOAD:
				client_download(); break;
			case DELETE:
				client_delete(); break;
			case QUERY:
				client_query(); break;
			default:
				printf("SOMETHING WENT WRONG!\n"); exit(1); break;
		}
	}

	//cleanup
	cleanup(server);
	return 0;
}

void client_upload(){
	char* file = get_input("enter address of the file: ");
	printf("you want to upload %s?\n", file);
	free(file);
	
}

void client_download(){
	
}

void client_query(){
	
}

void client_delete(){
	
}

