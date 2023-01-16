#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>

#include "client.h"
#include "helpers.h"

#include "file.h"
#include "utils.h"

//GLOBALS
int height, width;
enum MODE {GLOBAL, LOCAL};
int mode = LOCAL;
FILEITEM** items;
int selected = 0;
char cwd[256];

int main(){
	//connect to server
	int server = client_connect();

	//setup ncurses
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, 1);

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_BLUE);

	//window setup
	getmaxyx(stdscr, height, width);
	WINDOW* leftMenu = newwin(height-8, (width-2)*2/5, 6, 1);
	WINDOW* rightMenu = newwin(height-8, (width-2)*3/5, 6, (width-2)*2/5+2);

	//gui loop
	while(1){
		//get new info
		//var info setup
		items = get_items("."); //this depends on global or not
		getmaxyx(stdscr, height, width);
		getcwd(cwd, 256);

		//DRAW NEW GUI
		//leftMenu
		werase(leftMenu);
		for(int i = 0; items[i] != NULL; i++){
			if(selected == i) wattron(leftMenu, A_REVERSE);
			//if(items[i]->type = 4) wattron(leftMenu, A_INVIS);
			mvwprintw(leftMenu, i+1, 1, "%s\n", items[i]->name);
			if(selected == i) wattroff(leftMenu, A_REVERSE);
			if(items[i]->type == 4) mvwprintw(leftMenu, i+1, 1+strlen(items[i]->name), "/");
			//wattroff(leftMenu, A_INVIS);
		}
		box(leftMenu, 0, 0);

		//rightMenu
		werase(rightMenu);	

		//display gui
		refresh();
		wrefresh(leftMenu);
		wrefresh(rightMenu);

		//handle input
		int input = getch();
		wprintw(rightMenu, "%d\n", input);
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
			case '\n':
				//LOCAL
				if(mode == LOCAL){
					//if dir
					if(items[selected]->type == 4){
						chdir(items[selected]->name);
						selected = 0;
					}
					//if file
				}
				//GLOBAL
			break;
			//switch to server
			case 'g': case 'G':
			break;
			//refresh (idk if i need)
			case 'r': case 'R':
			break;
			//quit
			case 'q': case 'Q':
			break;
		}
	}

	//end ncurses		
	endwin();
	//cleanup(server);
	return 0;
}