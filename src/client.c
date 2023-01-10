#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "helpers.h"
#include "networking.h"

int main(){
	//ask for ip and port of server
	char* ip = get_input("enter IP of server: ");
	char* port = get_input("enter PORT of server: ");
	
	//setup client networking
	int server = connect_server(ip, port);
	free(ip); free(port);

	//the application
	while(1){
		printf("this is the application!");
		char buf[10];
		fgets(buf, 10, stdin);
	}



	return 0;
}


