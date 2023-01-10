#ifndef NETWORKING_H
#define NETWORKING_H

int init_server();

int connect_server(char* ip);

int create_socket(char* addr, char type);

#endif
