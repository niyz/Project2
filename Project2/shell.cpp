#include <iostream>
#include <sstream>
#include "filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
	"quit","format","ls","create","cat","createImage","restoreImage",
	"rm","cp","append","mv","mkdir","cd","pwd","help"
};
void createFolder(FileSystem &fileSystem, Directory *cwd, std::string commandArr[]);
void createFile(FileSystem &fileSystem, Directory *cwd, std::string commandArr[]);
Directory *changeDirectory(FileSystem &fileSystem, Directory *cwd, std::string commandArr[]);
void listFiles(FileSystem &fileSystem, Directory *cwd);
void printDirectory(FileSystem &fileSystem, Directory *cwd);

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
bool quit();
std::string help();

/* More functions ... */

int main(void) 
{
	FileSystem fs;
	FileSystem *fsPtr = &fs; //?
	Directory *cwd = fs.getCWD(); //?

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output
	bool bRun = true;

	do {
		 //lägger till en till kommentar sasds
		//Lägger till en kommentar
		std::cout << user << ":";
		printDirectory(fs, cwd);
		std::cout << "$ ";
		getline(std::cin, userCommand);
		int size = commandArr->size();

		int nrOfCommands = parseCommandString(userCommand, commandArr);
		if (nrOfCommands > 0) 
		{

			int cIndex = findCommand(commandArr[0]);
			switch (cIndex) 
			{

			case 0: //quit
				bRun = quit();
				break;
			case 1: // format
				break;
			case 2: // ls
				std::cout << "Listing directory" << std::endl;
				listFiles(fs,cwd);
				break;
			case 3: // create
				//TODO: Needs filepath
				createFile(fs,cwd, commandArr);
				break;
			case 4: // cat
				break;
			case 5: // createImage
				break;
			case 6: // restoreImage
				break;
			case 7: // rm
				break;
			case 8: // cp
				break;
			case 9: // append
				break;
			case 10: // mv
				break;
			case 11: //mkdir
				createFolder(fs,cwd, commandArr);
				break;
			case 12: // cd
				cwd = changeDirectory(fs, cwd, commandArr);
				break;
			case 13: 
				printDirectory(fs, cwd);
				break;
			case 14: // help
				std::cout << help() << std::endl;
				break;
			default:
				std::cout << "Unknown command: " << commandArr[0] << std::endl;
			}
		}
	} while (bRun == true);

	return 0;
}




int parseCommandString(const std::string &userCommand, std::string strArr[]) {
	std::stringstream ssin(userCommand);
	int counter = 0;
	while (ssin.good() && counter < MAXCOMMANDS) 
	{
		ssin >> strArr[counter];
		counter++;
	}
	if (strArr[0] == "") 
	{
		counter = 0;
	}
	return counter;
}
int findCommand(std::string &command) {
	int index = -1;
	for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
		if (command == availableCommands[i]) {
			index = i;
		}
	}
	return index;
}

bool quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string help() {
	std::string helpStr;
	helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
	helpStr += "-----------------------------------------------------------------------------------\n";
	helpStr += "* quit:                             Quit OSD Disk Tool\n";
	helpStr += "* format;                           Formats disk\n";
	helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
	helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
	helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
	helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
	helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
	helpStr += "* rm     <file>:                    Removes <file>\n";
	helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
	helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
	helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
	helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
	helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
	helpStr += "* pwd:                              Get current working directory\n";
	helpStr += "* help:                             Prints this help screen\n";
	return helpStr;
}


void createFolder(FileSystem &fs, Directory *cwd, std::string commandArr[])
{
	//std::string folderName;
	//std::cout << "Foldername: ";
	//std::getline(std::cin, folderName);
	fs.createFolderi(commandArr[1], cwd);
}

void createFile(FileSystem &fs, Directory *cwd, std::string commandArr[])
{
	//TODO: Needs filepath
	std::string data;
	std::cout << "Data:";
	std::getline(std::cin, data);
	fs.createFile(commandArr[1], data, cwd);
}

Directory * changeDirectory(FileSystem &fs, Directory *cwd, std::string commandArr[])
{
	std::string pathName;
	for (int i = 1; i < commandArr->size(); i++)
	{
		pathName.append(commandArr[i]);
	}
	//std::cout << "Path: ";
	//std::getline(std::cin, pathName);

	std::vector<std::string> pathNames = fs.splitPath(pathName);
	
	return fs.traverse(pathNames, cwd);

}

void listFiles(FileSystem &fs, Directory *dir)
{
	std::vector<std::string> vectorToFill;
	vectorToFill = fs.listdir(dir);
	int elementsInVector = vectorToFill.size();
	for (int i = 0; i < elementsInVector; i++)
	{
		std::cout << vectorToFill[i] << std::endl;
	}
}

void printDirectory(FileSystem &fs, Directory *cwd)
{
	std::vector<std::string> path;
	path = fs.getWD(cwd);
	int size = path.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << path[i] << "/";
	}

}

