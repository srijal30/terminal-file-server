# COMPILING SEPERATE PROGRAMS
compile: server.out client.out

server.out: $(addprefix src/, server.o networking.o helpers.o)
	gcc -Wall -Wextra -g -o server.out $(addprefix src/, server.o helpers.o networking.o)

client.out: $(addprefix src/, client.o networking.o helpers.o)
	gcc -Wall -Wextra -g -o client.out $(addprefix src/, client.o helpers.o networking.o)


# COMPILING ALL BASE FILES
client.o: $(addprefix src/, client.c client.h helpers.h networking.h)
	gcc -c $(addprefix src/, client.c)

helpers.o: $(addprefix src/, helpers.c)
	gcc -c $(addprefix src/, helpers.c)

networking.o: $(addprefix src/, networking.c networking.h helpers.h)
	gcc -c $(addprefix src/, networking.c)

server.o: $(addprefix src/, server.c helpers.h networking.h)
	gcc -c $(addprefix src/, server.c)


# FOR RUNNING
server: server.out
	./server.out

client: client.out
	./client.out


# EXTRA UTILS
clean:
	rm -rf */*.o */*.out *.out
