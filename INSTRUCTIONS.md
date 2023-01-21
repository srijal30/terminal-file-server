# How to Run

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

# Features
* Browse files and their content from both the local and remote directories
* Upload local files to the remote server
* Download remote files to your local drive
* Delete remove and local files

# Known Bugs

**Bug 0: Random Segfault**<br>
When switching mode from GLOBAL to LOCAL and vice-versa, the program sometimes randomly crash due to segfault.

**How to Fix:**<br>
Run the client again and hope for the best 😁. This behavior is really inconsistent, so it's unlikely to crash again.
<br><br>

**Bug 1: Remote Machines File Name** <br>
When connecting from a client to a server hosted on another machine (For e.g. WSL to marge), the file list for the server displays content instead of filenames. It works just fine for connecting server and client using `localhost`.

**How to Fix:** <br>
Make sure to run both the server and client on the same machine.
