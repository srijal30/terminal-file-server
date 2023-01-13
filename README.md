# SatoshiNakamoto 🥷

# Members
* Salaj Rijal
     
# A statement of the problem you are solving and/or a high level description of the project.
A fileserver that clients can connect to manage files "on the cloud". 

MVP features include:
- Upload files
- Download files
- Delete files
- Browse files
- Update files

Extra features that I might add are:
- Organization (directories, categories, etc.)
- Authentication & Permissions
- Search


# A description as to how the project will be used (describe the user interface).
The program will be fully terminal based. At first it will use the default command line, but later I plan to use ncurses to make the GUI nicer.


# A description of your technical design. This should include:

**Topics Covered**   
sockets - connect to server
memory - will need to use throughout
files - store files
dirent/stat - file data


**How you are breaking down the project and who is responsible for which parts.**
<br>I will be doing everything
  
**What algorithms and /or data structures you will be using, and how.**
Will use a response and request struct to make communication easier.
Might use search algorithm to allow user to search for the file they want.

# A timeline with expected completion dates of parts of the project.

1/14/22:
- MVP will be finished
	- Network infastructure
	- Communication b/w server & client
	- Server file management methods

1/16/22:
- Will create an ncurses GUI

1/17/22:
- Will add authentication & user accounts
- Will add search?

