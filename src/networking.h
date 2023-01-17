#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_SIZE 50
#define PORT "58008"
#define MAX_CLIENTS 40

enum TYPE{
	EXIT,
	UPLOAD,
	DOWNLOAD,
	DELETE,
	QUERY
};

typedef struct request{
	int type;
	int bytesNext;
} REQUEST;

typedef struct response{
	int status; //1 if sucess, 0 if fail
	int bytesNext; //-1 if no followup msg
	char message[MESSAGE_SIZE];
} RESPONSE;

int init_server();

int connect_server(char* ip);

int create_socket(char* addr, char type);

void cleanup(int sock);

void send_request(int server, int type, int bytesNext);

REQUEST* receive_request(int client);

void send_response(int client, int status, int bytesNext, char* msg);

RESPONSE* receive_response(int server);

char* get_next(int sock, int bytes);

#endif
