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

	//var info setup
	int height, width;
	enum mode {GLOBAL, LOCAL};
	int curMode = LOCAL;
	FILEITEM** items = get_items(".");
	int selected = 0;
	char cwd[256]; getcwd(cwd, 256);
	printf("%s\n", cwd);

	//setup ncurses
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, 1);

	//window setup
	getmaxyx(stdscr, height, width);
	WINDOW* leftMenu = newwin(height-8, (width-2)*2/5, 6, 1);
	WINDOW* rightMenu = newwin(height-8, (width-2)*3/5, 6, (width-2)*2/5+2);

	//gui loop
	while(1){
		//get the new height and width
		//getmaxyx(stdscr, height, width);

		wprintw(rightMenu, "NORMAL TEST\n");
		attron(A_REVERSE);
		wprintw(rightMenu, "REVERSE TEST\n");
		attroff(A_REVERSE);
		//leftMenu
		for(int i = 0; items[i] != NULL; i++){
			mvwprintw(leftMenu, i+1, 1, "%s\n", items[i]->name);
		}

		box(leftMenu, 0, 0);
		//rightMenu

		//display gui
		refresh();
		wrefresh(leftMenu);
		wrefresh(rightMenu);

		//get input
		int input = getch();
		switch(input){
			//cycle up
			case KEY_UP: case 'k':
				if(selected> 0) selected--;	
			break;
			//cycle down	
			case KEY_DOWN: case 'j':
				if(items[selected+1]!=NULL) selected++;
			break;
			//get options (this one finna be hard)
			case KEY_ENTER:
			break;
			//switch to server
			case 'g': case 'G':
			break;
			//refresh (idk if i need)
			case 'r': case 'R':
			break;
		}
	}

	//end ncurses		
	endwin();
	cleanup(server);
	return 0;
}

void client_exit(int server){
	send_request(server, EXIT, -1);
	cleanup(server);
	printf("EXITING...\n");
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

