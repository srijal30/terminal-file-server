#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "networking.h"
#include "helpers.h"

#define PORT "58008"
#define MAX_CLIENTS 10

//returns the fd of client for subserver
int init_server(){
	//setup server info
	int sock = create_socket(NULL, 's');

	//start listening 
	error_check(listen(sock, MAX_CLIENTS), "LISTEN SOCKET");
	while(1==1){
		//wait for client to connect
		int client_sock = accept(sock, NULL, NULL); //do we care about other params
		error_check(client_sock, "ACCEPT CLIENT");
		//create server
		if(fork() == 0) return client_sock;
	}

	//should never reach here
	return -1;
}

//returns fd of the connected server
int connect_server(char* ip){
	return create_socket(ip, 'c');
}


int create_socket(char* addr, char type){
	struct addrinfo *hints, *res;

	//create the hints
	hints = (struct addrinfo*)calloc(1,sizeof(struct addrinfo));
	hints->ai_family = AF_INET; //IPv4
	hints->ai_socktype = SOCK_STREAM; //TCP
	if(type == 's') hints->ai_flags = AI_PASSIVE;

	//create the address
	error_check(getaddrinfo(addr, PORT, hints, &res), "CREATE ADDRESS");

	//create the socket
	int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	error_check(sock, "CREATE SOCKET");

	//bind if server	
	if(type == 's') error_check(bind(sock, res->ai_addr, res->ai_addrlen), "BIND SERVER");
	//connect if client
	else if(type == 'c') error_check(connect(sock, res->ai_addr, res->ai_addrlen), "CONNECT CLIENT");

	//cleanup
	free(hints);
	freeaddrinfo(res);
	return sock;
}



