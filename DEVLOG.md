# DEVLOG

## 01/09
- created skeletons for server and client
- created helper methods `error_check` and `get_input`
- started networking code for both client and server

## 01/10
- server now creates subservers for every client
- finished method `create_socket` which will establish connections for both clients and servers
- created `REQUEST` and `RESPONSE` structs
- basic networking code finished

## 01/11
- modified networking code to make it more modulated
- created new file for file management methods:
	- `file_content`
	- `create_file`	
	- `delete_file`
	- `file_size`
	- `file_exists`
- worked on handling these requests for client & server
	- `EXIT`
	- `UPLOAD`

## 01/12
- worked on handling these requests for client & server
	- `DELETE`
	- `DOWNLOAD`

## 01/13
- planned GUI design on paper
- reserached how to use ncurses
- started work on refactoring client to incorportate GUI

## 01/14
- added `leftMenu` and `rightMenu` windows
- created GUI loop that runs forever
- created switch statement that will handle input from user

## 01/15
- created `topMenu` and `bottomMenu` for other information + instructions for user
- can now handle `QUERY` request which lists files in server

## 01/16
- added a `debug` method which toggles debug print statemetns
- added semaphore methods in file.c
- added ability to see content of currently selected file or directory
- added signal handlers so that client and server properly disconnect
- fixed many, many, many bugs... here are a few:
	- server didnt send `fileitem` datastructure properly
	- strings were not null terminated in `get_next` method
	- client randomly segfaulted due to freeing uninitialized memory
	- GUI was glitchy due to calling `get_items` between every frame (when it wasn't necassry)