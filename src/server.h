#ifndef SERVER_H
#define SERVER_H

#include "networking.h"

//accept file from client
void accept_file(int client, REQUEST* req);

//send file to client
void send_file(int client, REQUEST* req);

//delete file from subserver
void remove_file(int client, REQUEST* req);

#endif
