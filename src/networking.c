#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

#include <sys/socket.h>
#include <netdb.h>

#include "networking.h"
#include "helpers.h"

int init_server(){
	int sock = create_socket("0.0.0.0", 's');
	error_check(listen(sock, MAX_CLIENTS), "LISTEN SOCKET");
	while(1==1){
		//DO WE NEED TO KEEP TRACK OF CLIENTS??
		int client_sock = accept(sock, NULL, NULL);
		error_check(client_sock, "ACCEPT CLIENT");
		int forkVal = fork();
		if(forkVal == 0) return client_sock;
		else printf("\nSERVER %d CONNECTED TO CLIENT %d\n", forkVal, client_sock);
	}
	return -1;
}

//returns fd of the connected server
int connect_server(char* ip){
	return create_socket(ip, 'c');
}

//close the connection
void cleanup(int sock){
	error_check(close(sock), "CLOSING CONNECTION");
}

//creates a socket for server or client
int create_socket(char* addr, char type){
	//create the hints
	struct addrinfo *hints, *res;
	hints = (struct addrinfo*)calloc(1,sizeof(struct addrinfo));
	hints->ai_family = AF_INET; //IPv4
	hints->ai_socktype = SOCK_STREAM; //TCP
	if(type == 's') hints->ai_flags = AI_PASSIVE;
	//create the address
	error_check(getaddrinfo(addr, PORT, hints, &res), "CREATE ADDRESS");
	//create the socket
	int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	error_check(sock, "CREATE SOCKET");
	//connect OR bind (depending on type)
	if(type == 's') error_check(bind(sock, res->ai_addr, res->ai_addrlen), "BIND SERVER");
	else if(type == 'c') error_check(connect(sock, res->ai_addr, res->ai_addrlen), "CONNECT CLIENT");
	//cleanup
	free(hints);
	freeaddrinfo(res);
	return sock;
}

//send response to the client
void send_response(int client, int status, int bytesNext, char* msg){
	RESPONSE* res = (RESPONSE*)malloc(sizeof(RESPONSE));
	res->status = status;
	res->bytesNext = bytesNext;
	strncpy(res->message, msg, MESSAGE_SIZE);
	error_check(write(client, res, sizeof(RESPONSE)), "SENDING RESPONSE");
	free(res);
}

//receive response from the server (blocks)
RESPONSE* receive_response(int server){
	RESPONSE* res = (RESPONSE*)malloc(sizeof(RESPONSE));
	error_check(read(server, res, sizeof(RESPONSE)), "RECEIVING RESPONSE");
	return res;
}

//send request to the server
void send_request(int server, int type, int bytesNext){
	REQUEST* req = (REQUEST*)malloc(sizeof(REQUEST));
	req->type = type;
	req->bytesNext = bytesNext;
	error_check(write(server, req, sizeof(REQUEST)), "SENDING REQUEST");
	free(req);
}

//receive request from the client (blocks)
REQUEST* receive_request(int client){
	REQUEST* req = (REQUEST*)malloc(sizeof(REQUEST));
	error_check(read(client, req, sizeof(REQUEST)), "RECEIVING REQUEST");
	return req;
}

//gets follow up msg based on bytes
char* get_next(int sock, int bytes){
	char* str = (char*)malloc(bytes);
	error_check(read(sock, str, bytes), "GETTING NEXT");
	return str;
}


