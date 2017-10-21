#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "Directory.h"
#include "memblockdevice.h"
#include <vector>

class FileSystem
{
private:
	MemBlockDevice mMemblockDevice;
	Directory dirObj;
	Directory *dir = &dirObj;
	int freeBlocks[250] = { 0 }; //if 0 free


public:
	FileSystem();
	~FileSystem();
	
	/* These API functions need to be implemented
	You are free to specify parameter lists and return values
	*/

	/* This function creates a file in the filesystem */
	// createFile(...)
	bool createFile(std::string name, std::string data, Directory *dir);
	/* Creates a folder in the filesystem */
	// createFolderi(...);
	bool createFolderi(std::string name, Directory *dir);

	/* Removes a file in the filesystem */
	// removeFile(...);

	/* Removes a folder in the filesystem */
	// removeFolder(...);

	/* Function will move the current location to a specified location in the filesystem */
	Directory *enterFolder(std::string name, Directory *dir);

	/* This function will get all the files and folders in the specified folder */
	std::vector<std::string> listdir(Directory *dir);

	/* Add your own member-functions if needed */
	std::vector<std::string> splitPath(std::string path); //returnerar en vector av stings(folder name)
	Directory * traverse(std::vector<std::string> stringWords, Directory *dir);
	void setCWD(Directory *dirPtr);
	Directory * getCWD();
	std::vector<std::string> getWD(Directory *dirPtr);

};

#endif // FILESYSTEM_H
