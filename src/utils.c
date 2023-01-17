#include <stdlib.h>
#include <stdio.h>
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
        free(content); free(res);
}

void client_download(int server, char* filename){
        //send name of file to download
        send_request(server, DOWNLOAD, strlen(filename));
        error_check(write(server, filename, strlen(filename)), "DOWNLOAD FILE send name");
        //receive response
        RESPONSE* res = receive_response(server);
        //receive file
	char* content = get_next(server, res->bytesNext); free(res);
	create_file(filename, content); free(content);
}

FILEITEM** client_query(int server, char* path){
	//send path to server
	send_request(server, QUERY, strlen(path));
	error_check(write(server, path, strlen(path)), "CLIENT QUERY send path");
	//recieve resposne
	RESPONSE* res = receive_response(server);
	//get all the file items (MAKE LAST ONE NULL MANUALLY)
	int cnt = res->bytesNext; free(res);
	printf("REACHED HERE\n"); //DEBUG
	FILEITEM** items = (FILEITEM**)calloc((cnt+1), sizeof(FILEITEM*));
	for(int i = 0; i < cnt; i++){
		FILEITEM* newItem = (FILEITEM*)get_next(server, sizeof(FILEITEM));
        //receive the content of newItem
        newItem->content = get_next(server, newItem->size);
		items[i] = newItem;
	}
	items[cnt] = NULL;
	return items;
}

void client_delete(int server, char* filename){
	//send to server
	send_request(server, DELETE, strlen(filename));
	error_check(write(server, filename, strlen(filename)), "CLIENT DELETE send name");
	//get response
	RESPONSE* res = receive_response(server);
	free(res);
}

int client_connect(){
    char* ip = get_input("enter IP of server: ");
	int sock = connect_server(ip);
	free(ip);
	return sock;
}
