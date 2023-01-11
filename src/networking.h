#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_SIZE 50
#define PORT "58008"
#define MAX_CLIENTS 10

//SETUP STUFF
int init_server();

int connect_server(char* ip);

int create_socket(char* addr, char type);


//COMMUNICATION STUFF
/*
	TYPES OF REQUESTS:
	0 - EXIT
	1 - UPLOAD FILE
	2 - DOWNLOAD FILES
	3 - DELETE FILE
	4 - QUERY FILES
*/
typedef struct request{
	int type;
	int bytesNext; //-1 no followup msg
} REQUEST;

void send_request(int server, int type, int bytesNext);
REQUEST* receive_request(int client);


typedef struct response{
	int status; //1 if sucess, 0 if fail
	int bytesNext; //-1 if no followup msg
	char message[MESSAGE_SIZE];
} RESPONSE;

void send_response(int client, int status, int bytesNext, char* msg);
RESPONSE* receive_response(int server);

#endif
