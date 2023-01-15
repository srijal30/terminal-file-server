#ifndef CLIENT_H
#define CLIENT_H

void client_exit(int server);

void client_upload(int server, char* filename);

void client_query(int server, char* path);

void client_delete(int server, char* filename);

void client_download(int server, char* filename);

#endif
