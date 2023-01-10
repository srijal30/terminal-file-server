# COMPILING SEPERATE PROGRAMS
compile: server.out client.out

server.out: server.o networking.o helpers.o
	gcc -Wall -Wextra -g -o server.out server.o helpers.o networking.o

client.out: client.o networking.o helpers.o
	gcc -Wall -Wextra -g -o client.out client.o helpers.o networking.o


# COMPILING ALL BASE FILES
client.o: client.c client.h helpers.h networking.h 
	gcc -c client.c

helpers.o: helpers.c 
	gcc -c helpers.c

networking.o: networking.c networking.h helpers.h 
	gcc -c networking.c

server.o: server.c helpers.h networking.h 
	gcc -c server.c


# FOR RUNNING
server: server.out
	./server.out

client: client.out
	./client.out


# EXTRA UTILS
clean:
	rm -rf *.o compile *.out server client
