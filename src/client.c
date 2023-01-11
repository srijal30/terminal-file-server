#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "helpers.h"
#include "networking.h"

int main(){
	//ask for ip and port of server
	char* ip = get_input("enter IP of server: ");
	//char* port = get_input("enter PORT of server: "); 
	
	//setup client networking
	int server = connect_server(ip);
	free(ip);

	//the application
	while(1){
		int i; char c;
		char* line = get_input("enter a char and int: ");
		sscanf(line, "%c %d", &c, &i);
	}

	//cleanup
	//add networking cleanup
	return 0;
}


