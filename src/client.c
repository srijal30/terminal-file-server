#include <stdio.h>
#include <string.h>

#include "client.h"
#include "helpers.h"

#define MAXLINE 100

int main(){
	//ask for ip and port of server
	char ip[MAXLINE];
	printf("IP of server: ");
	fgets(ip, MAXLINE, stdin); ip[strlen(ip)-1] = 0;
	
	char port[MAXLINE];
	printf("PORT of server: ");
	fgets(port, MAXLINE, stdin); port[strlen(port)-1] = 0;

	//connect to server

	

	//the application
	while(1){


	}


	return 0;
}


