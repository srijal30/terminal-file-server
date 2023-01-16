# DEVLOG

## 01/09
- created skeletons for server and client
- created helper methods `error_check` and `get_input`
- started networking code for both client and server

## 01/10
- server now creates subservers for every client
- finished method `create_socket`
- added REQUEST and RESPONSE structs
- finished networking code

## 01/11
- modified networkin code to make more modulatedS
- created new file for file management methods:
	- `file_content`
	- `create_file`	
	- `delete_file`
	- `file_size`
	- `file_exists`
- worked on these interactions
	- EXIT
	- UPLOAD

## 01/12
- finished interactions (besides QUERY)
	- DELETE
	- DOWNLOAD

## 01/13
- planned GUI design on paper
- started work on GUI

## 01/14
- added function that creates list of all items in directory and well as some info
- base GUI is semi complete
- GUI loop created

## 01/15
- added menu for GUI
- added keyboard input for GUI

## 01/16
- added DEBUG
- added topMenu window
- added bottomMenu window
- integreated features wtih GUI
- added semaphore for file writing access
