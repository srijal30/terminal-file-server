#ifndef CLIENT_H
#define CLIENT_H

//creates popup where user selects between different requests
int popup();

//starts and allocates mem for ncurses
void start_curses();

//ends the program
void close_curses();

//handles interrupt
static void handler(int sig);

//updates the items
void update_items();

#endif
