#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include <ncurses.h>

#include "client.h"
#include "helpers.h"
#include "networking.h"
#include "file.h"
#include "utils.h"

//GLOBALS
int server;
int height, width;
enum MODE {GLOBAL, LOCAL};
int mode = LOCAL;
FILEITEM** items;
int selected = 0;
char cwd[256];

//NCURSES
WINDOW* leftMenu;
WINDOW* rightMenu;
WINDOW* topMenu;
WINDOW* botMenu;
WINDOW* inner;

int main(){
	//setup
	signal(SIGINT, handler);
	server = client_connect();
	start_curses();

	//gui loop
	while(1){
		//this depends on GLOBAL or LOCAL
		getcwd(cwd, 256);

		//update other vars
		getmaxyx(stdscr, height, width);

		//DRAW NEW GUI
		erase();

		//leftMenu
		werase(leftMenu);
		for(int i = 0; items[i] != NULL; i++){
			if(selected == i) wattron(leftMenu, A_REVERSE);
			mvwprintw(leftMenu, i+1, 1, "%s\n", items[i]->name);
			if(selected == i) wattroff(leftMenu, A_REVERSE);
			if(items[i]->type == 4) mvwprintw(leftMenu, i+1, 1+strlen(items[i]->name), "/");
		}
		box(leftMenu, 0, 0);

		//rightMenu
		werase(rightMenu);
		werase(inner);
		mvwprintw(inner, 0, 0, "%s", items[selected]->content);
		box(rightMenu, 0, 0);

		//topMenu
		werase(topMenu);
		char* msg = "FILEBOX++"; 
		char* msg2 = "© Salaj Rijal";
		mvwprintw(topMenu, 1, 1, msg);
		mvwprintw(topMenu, 1, width-3-strlen(msg2), msg2);
		//instructions
		//local
		if(mode == LOCAL) wattron(topMenu, A_REVERSE);
		mvwprintw(topMenu, 3, 1, "(L) LOCAL");
		if(mode == LOCAL) wattroff(topMenu, A_REVERSE);
		//global
		if(mode == GLOBAL) wattron(topMenu, A_REVERSE);
		mvwprintw(topMenu, 3, 12, "(S) SERVER");
		if(mode == GLOBAL) wattroff(topMenu, A_REVERSE);
		mvwprintw(topMenu, 3, 24, "(ENTER) OPTIONS  (R) REFRESH  (Q) QUIT");
		box(topMenu, 0, 0);
		
		//botMenu
		werase(botMenu);
		mvwprintw(botMenu, 0, 0, "LOCAL PATH: %s\n", cwd);

		//display gui
		refresh();
		wrefresh(leftMenu);
		wrefresh(rightMenu);
		wrefresh(topMenu);
		wrefresh(botMenu);
		wrefresh(inner);

		//handle input
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
			//get options
			case '\n':
				//if dir
				if(items[selected]->type == 4 && mode == LOCAL){
					chdir(items[selected]->name);
					selected = 0;
					update_items();
				}
				//if file
				else if(items[selected]->type == 8){
					int choice = popup();
					switch(choice){
						case DOWNLOAD: client_download(server, items[selected]->name);
						break;
						case UPLOAD: client_upload(server, items[selected]->name);
						break;
						case DELETE:
							if(mode == GLOBAL) client_delete(server, items[selected]->name);
							else if(mode == LOCAL) delete_file(items[selected]->name);
						break;
					}
				}
			break;
			//switch to server files
			case 's': case 'S':
				if(mode == LOCAL){
					mode = GLOBAL;
					selected = 0;
					update_items();
				}
			break;
			//switch to client files
			case 'l': case 'L':
				if(mode == GLOBAL){
					mode = LOCAL;
					selected = 0;
					update_items();
				}
			break;
			//refresh (idk if i need)
			case 'r': case 'R':
				update_items();
			break;
			//quit
			case 'q': case 'Q':
				close_curses();
			break;
		}
	}

	close_curses();
}

void start_curses(){
	//setup ncurses
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, 1);
	//setup vars
	getmaxyx(stdscr, height, width);
	items = get_items(".");
	//setup windows
	leftMenu = newwin(height-8, (width-2)*2/5, 6, 1);
	rightMenu = newwin(height-8, (width-2)*3/5, 6, (width-2)*2/5+2);
	topMenu = newwin(5, width-2, 1, 1);
	botMenu = newwin(1, width-2, height-2, 1);
	inner = newwin(height-10, (width-2)*3/5-2, 7, (width-2)*2/5+3);
}

void close_curses(){
	endwin();
	client_exit(server);
}

//return input of popup
int popup(){
	//setup popup
	WINDOW* modal = newwin(8, 30, height/2-4, width/2-15);
	//header
	//this code makes me wanna cry ;(
	char* msg = "CHOOSE OPTION";
	//char* msg1 = "DOWNLOAD"; char* msg2 = "UPLOAD"; char* msg3 = "CANCEL";
	char* menu[] = { mode == GLOBAL ? "DOWNLOAD" : "UPLOAD", "DELETE", "CANCEL"};
	int cur = 0;
	mvwprintw(modal, 1, (30-strlen(msg))/2, msg);
	//options
	for(int i = 0; i < 3; i++){
		if(cur == i) wattron(modal, A_REVERSE);
		mvwprintw(modal, 3+i, (30-strlen(menu[i]))/2, menu[i]);
		if(cur == i) wattroff(modal, A_REVERSE);
	}
	box(modal, 0, 0);
	wrefresh(modal);
	int input = getch();
	//this is really bad code that it makes me cry ;(
	while(input != '\n'){
		switch(input){
			case 'j': case 'J': case KEY_DOWN:
				if(cur < 2) cur++;
			break;
			case 'k': case 'K': case KEY_UP:
				if(cur > 0) cur--;
			break;
		}
		for(int i = 0; i < 3; i++){
			if(cur == i) wattron(modal, A_REVERSE);
			mvwprintw(modal, 3+i, (30-strlen(menu[i]))/2, menu[i]);
			if(cur == i) wattroff(modal, A_REVERSE);
		}
		wrefresh(modal);
		input = getch();
	}
	delwin(modal);
	if(cur == 1) return DELETE; //DELETE
	if(cur == 2) return -1;  //CANCEL
	else if(cur == 0 && mode == GLOBAL) return DOWNLOAD; //DOWNLOAD
	else return UPLOAD; //UPLOAD
}

static void handler(int sig){
	if(sig == SIGINT) close_curses();
}

void update_items(){
	free_items(items);
	if(mode == GLOBAL) items = client_query(server, ".");
	else items = get_items(".");
}
