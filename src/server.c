#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "networking.h"
#include "server.h"

#include <unistd.h>

int main(){
	//setup 
	char buf[5];
	int client = init_server();

	//only subservers beyond this point!
	//subserver that is the manager for file system
	printf("subserver %d is connected to client %d!\n", getpid(), client);

	//wait for requests from client
	while(1==1){
		char type; int bytes;
		read(client, buf, 5);
		sscanf(buf, "%c%d", &type, &bytes);
		printf("type is %c\nbytes are %d\n\n", type, bytes);
	}


	//cleanup
	//add networking cleanup

	return 0;
}
