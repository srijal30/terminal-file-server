#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_SIZE 50
#define PORT "58008"
#define MAX_CLIENTS 40

//different types of requests that client can send
enum TYPE{
	EXIT,
	UPLOAD,
	DOWNLOAD,
	DELETE,
	QUERY
};

//represents client request being sent to server
typedef struct request{
	int type;
	int bytesNext;
} REQUEST;

//represents server response being sent to client
typedef struct response{
	//1 if sucess, 0 if fail
	int status;
	//-1 if no followup msg
	int bytesNext;
	char message[MESSAGE_SIZE];
} RESPONSE;

//creates the forking server and returns client socket to subserver
int init_server();

//connects subserver to client and returns client socket
int connect_server(char* ip);

//creates a socket and returns it
int create_socket(char* addr, char type);

//closes a socket
void cleanup(int sock);

//sends a request to server
void send_request(int server, int type, int bytesNext);

//returns request received from client
REQUEST* receive_request(int client);

//sends a response to client
void send_response(int client, int status, int bytesNext, char* msg);

//returns response received from server
RESPONSE* receive_response(int server);

//helper method that makes it easer to receive follow-up messages
char* get_next(int sock, int bytes);

#endif
