#ifndef SERVER_H
#define SERVER_H

//accept file from client
void accept_file(int client);

//send file to client
void send_file(int client);

//delete file from subserver
void delete_file(int client);

//make sure that only one subserver is editing (deleting and updating?) files at a time (semaphore!)
void get_pass();

void return_pass();

#endif
