# COMPILING SEPERATE PROGRAMS
compile: server.out client.out

server.out: $(addprefix src/, server.o networking.o helpers.o file.o)
	gcc -Wall -Wextra -g -o server.out $(addprefix src/, server.o helpers.o networking.o file.o)

client.out: $(addprefix src/, client.o networking.o helpers.o file.o utils.o)
	gcc -Wall -Wextra -g -o client.out $(addprefix src/, client.o helpers.o networking.o file.o utils.o) -lncurses


# COMPILING ALL BASE FILES
client.o: $(addprefix src/, client.c client.h helpers.h networking.h file.h)
	gcc -c $(addprefix src/, client.c)

helpers.o: $(addprefix src/, helpers.c)
	gcc -c $(addprefix src/, helpers.c)

networking.o: $(addprefix src/, networking.c networking.h helpers.h)
	gcc -c $(addprefix src/, networking.c)

server.o: $(addprefix src/, server.c helpers.h networking.h file.h)
	gcc -c $(addprefix src/, server.c)

file.o: $(addprefix src/, file.c helpers.h file.h)
	gcc -c $(addprefix src/, file.c)

utils.o: $(addprefix src/, utils.c helpers.h networking.h file.h)
	gcc -c $(addprefix src/, utils.c)

# FOR RUNNING
server: server.out
	./server.out

client: client.out
	./client.out


# EXTRA UTILS
clean:
	rm -rf */*.o */*.out *.out
