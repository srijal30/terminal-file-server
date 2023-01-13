#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <ncurses.h>

#include "file.h"
#include "client.h"
#include "helpers.h"
#include "networking.h"


int main(){
	//connect to server
	char* ip = get_input("enter IP of server: ");
	int server = connect_server(ip); free(ip);


	//I THINK WE NEED 2 THINGS
	//CONTENT and QUERY... QUERY IS FOR OBJECTS, CONTENT IS FOR DISPLAY DATA

	//GUI setup
	FILEITEM** curDir; //should we store content too? (we can just have string)
	int selectedIndex; 
	char* curPath;
	enum mode {GLOBAL, LOCAL};
	int height, width;

	//start ncurses
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr, height, width);

	//creating main menu
	WINDOW* title = newwin(height/5, width*3/5, height/10, width/5);
	box(title, 0, 0);
	mvwprintw(title, 1, 1, "FILE ++");

	//get ip and server
	

		
	wgetch(title);
	endwin();
	exit(0);
	
	while(1){
		//get user input
		int type = 0;
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
				//CHANGE
				printf("SOMETHING WENT WRONG!\n"); 
				exit(1); 
				break;
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
	//get name of file to download

	//send name of file to download

	//receive response

	//receive file

}

void client_query(int server){
	
}

void client_delete(int server){
	//get name of file to delete
	
	//send to server

	//get response
	
}

