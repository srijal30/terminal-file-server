#ifndef UTILS_H
#define UTILS_H

//cleanly disconnects client from server and exits program
void client_exit(int server);

//uploads file to server through upload request
void client_upload(int server, char* filename);

//sends a query request to server and returns the list of fileitems in server's storage directory
FILEITEM** client_query(int server, char* path);

//sends a delete request to server
void client_delete(int server, char* filename);

//sends a download request to server
void client_download(int server, char* filename);

//connects client to server and returns socket to server
int client_connect();

#endif
