#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "file.h"
#include "networking.h"
#include "helpers.h"

void client_exit(int server){
        send_request(server, EXIT, -1);
        cleanup(server);
        exit(0);
}

void client_upload(int server, char* filename){
        //get content
        char* content = file_content(filename);
        //send name of file
        send_request(server, UPLOAD, strlen(filename));
        error_check(write(server, filename, strlen(filename)), "UPLOAD FILE send name");
        //send content of file
        send_request(server, UPLOAD, file_size(filename));
        error_check(write(server, content, file_size(filename)), "SENDING FILE send content");
        //receive response
        RESPONSE* res = receive_response(server);
        free(content);
}

//NEED TO ADD DESTINATION PATH
void client_download(int server, char* filename){
        //send name of file to download
        send_request(server, DOWNLOAD, strlen(filename));
        error_check(write(server, filename, strlen(filename)), "DOWNLOAD FILE send name");
        //receive response
        RESPONSE* res = receive_response(server);
        //receive file
}

void client_query(int server, char* path){
}

void client_delete(int server, char* filename){
        //get name of file to delete
        //send to server
        //get response
}

int client_connect(){
        char* ip = get_input("enter IP of server: ");
	int sock = connect_server(ip);
	free(ip);
	return sock;
}
