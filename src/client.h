#ifndef CLIENT_H
#define CLIENT_H

int popup();

void start_curses();

void close_curses();

static void handler(int sig);

void update_items();

#endif
