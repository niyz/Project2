#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <vector>
#include <iostream>
#include <string>
#include "File.h"

class Directory
{
private:
	std::string name;//Foldername
	std::vector<Directory*> directories;
	std::vector<File> files; //Pointertype?
	Directory* parent; //to Daddy
	Directory* cwd;
	int size; //0-512, vad har filen själv för storlek?
	int blockNr; //1-250

	//rootpointer?

public:
	//Constructor
	Directory();
	Directory(std::string name, Directory* parent, Directory* cwd);
	virtual ~Directory();
	//Copy&Assignment
	Directory(const Directory &originalObject); //Copy
	Directory& operator=(const Directory &originalObject); //tilldening

	//Create folder/file
	bool createFolder(std::string name, Directory*cwd);
	bool createFile(std::string name, int blockNr, int size);
	//Remove items
	bool removeItem(std::string name);

	//Helpfunctions
	Directory* enterFolder(std::string name);
	Directory* leaveFolder();
	std::string getName();
	std::vector<std::string> printContent();
	void printCWD();
	bool hasItems(Directory *dir);
	int getDirectoriesSize();
	std::string getParentName(Directory *parentPtr);
	Directory *getParentPtr(Directory *parentPtr);

};
#endif // !DIRECTORY_H
