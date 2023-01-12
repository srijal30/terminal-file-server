#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

#include "file.h"
#include "client.h"
#include "helpers.h"
#include "networking.h"

int main(){
	//connect to server
	char* ip = get_input("enter IP of server: ");
	int server = connect_server(ip); free(ip);
	

	printf("content: %s\n", file_content("README.md"));	
	exit(0);
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
	int fd; char* file;
	file = get_input("\nenter address of the file: ");
	while((fd = open(file, O_RDONLY) == -1))
		file = get_input("INVALID TRY AGAIN!\nenter address of the file: ");
	//get the info
	struct stat st; stat(file, &st);
	char* file_upload = (char*)malloc(st.st_size);
	read(fd, file_upload, st.st_size);
	//send it to server
	printf("sent requestni\n");
	send_request(server, UPLOAD, st.st_size);
	printf("about to write\n");
	write(server, file_upload, st.st_size);
	//get the response
	RESPONSE* res = receive_response(server);
	printf("MESSAGE: %s\n", res->message);
	//cleanup
	close(fd);
	free(res);
	free(file_upload);
	free(file);
}

void client_download(int server){
	
}

void client_query(int server){
	
}

void client_delete(int server){
	
}

