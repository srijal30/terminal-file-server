#ifndef CLIENT_H
#define CLIENT_H

#define BLACK 0
#define BLUE 4
#define C_DIR 1

int popup();

void start_curses();

void close_curses();

static void handler(int sig);

#endif
