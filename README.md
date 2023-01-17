# SatoshiNakamoto 🥷

# Members
* Salaj Rijal
     
# A statement of the problem you are solving and/or a high level description of the project.
I will create a server that allows clients to download and upload files. It will be a more primitive version of applications like Google Drive and Dropbox. 

MVP features include:
- Upload files
- Download files
- Delete files
- Browse files

# A description as to how the project will be used (describe the user interface).
The program will be fully terminal based. At first I will  make all the features of the program usable through standard in. Later on, I plan to implement a GUI using ncurses.

Since this project requires `ncurses`, make sure you have it installed. You can install it with this command:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

To compile the server and client, run this command:
```
make compile
```

The directory in which you run the server will get filled with all the files that the clients send. For this reason, it is recommended that you run the server in a seperate (preferably empty) directory. Here is an example of me creating a folder for the server and then running it:
```
mkdir storage
cd storage
../server.out
```

To run the client, simply execute this command:
```
make client
```

# A description of your technical design. This should include:

**Topics Covered**   
* Memory Managment
* Sockets & Networking
* Searching Directories
* Reading & Writing to FIles
* Semaphore Resource Management
* Creating New Processes


**How you are breaking down the project and who is responsible for which parts.** <br>
I will be doing everything 😁
  
**What algorithms and /or data structures you will be using, and how.**
<br>
```c
//Storing information about a fileitem (file or directory)
struct fileitem {
	char name[256];
	int size;
	int type;
	char* content;
};

//Represents a request from client to server
struct request{
	int type;
	int bytesNext;
};

//Represents a response to a client request
struct response{
	int status;
	int bytesNext;
	char message[MESSAGE_SIZE];
};
```

# A timeline with expected completion dates of parts of the project.

1/14/22:
- MVP will be finished
	- Network infastructure
	- Communication between Server & Client
	- Server file management methods

1/16/22:
- Creating ncurses GUI

~~1/17/22:~~
- ~~Will add authentication & user accounts~~
- ~~Will add search?~~
