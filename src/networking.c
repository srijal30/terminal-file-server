#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "networking.h"
#include "helpers.h"

#define PORT "58008"

//returns the fd of client for subserver
int init_server(){
	//setup server info
	int sock = create_socket(NULL, 's');

	//listen for clients forever (also give status to user ig about main server's progress)
	while(1==1){
		
		//fork for new client (is fork neccassary?)
	}

	//only subserver makes it to here!
	return -1;
}

//returns fd of the connected server
int connect_server(char* ip){
	//setup client info
	int sock = create_socket(ip, 'c');

	return -1;
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

	//cleanup
	free(hints);
	freeaddrinfo(res);
	return sock;
}



