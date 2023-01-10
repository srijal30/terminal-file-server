#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"
#include "networking.h"

#include <unistd.h>

int main(){
	//setup the server
	init_server();

	//only subservers beyond this point!
	//subserver that is the manager for file system
	printf("subserver %d is connected!\n", getpid());


	return 0;
}