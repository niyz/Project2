#include "filesystem.h"

FileSystem::FileSystem() 
{


}

FileSystem::~FileSystem() 
{

}

bool FileSystem::createFile(std::string name, std::string data, Directory *dir)
{
	bool added = false;
	int sizeOfFile = 0;
	int nameSize = name.size();
	int dataSize = data.size();
	int totalSize = nameSize + dataSize;
	if (data.size() <= 512) //1 char = 1 byte
	{
		std::vector<char> temp(data.begin(), data.end());
		/*std::vector<char> newV;

		for (int i = 0; i < data.size(); i++)
		{
			newV[i] = temp[i];
		}*/

		int blockNr = mMemblockDevice.getFreePointer();
		mMemblockDevice.writeBlock(blockNr, temp);
		added = true;
		sizeOfFile = temp.size();
		dir->createFile(name, blockNr,sizeOfFile);
	}
	else
	{
		std::cout << "Temp error: string.size() returns > 512" << std::endl;
	}
	return added;
}

bool FileSystem::createFolderi(std::string name, Directory *dir)
{
	bool created = false;
	if (dir->createFolder(name, dir) == true)
	{
		int blockNr = mMemblockDevice.getFreePointer();
	/*	mMemblockDevice.writeBlock(blockNr, )
		created = true;*/
	}
	return created;
}

Directory * FileSystem::enterFolder(std::string name, Directory *dir)
{
	return dir->enterFolder(name);
}

std::vector<std::string> FileSystem::listdir (Directory *dir)
{
	std::vector<std::string> vectorToFill;
	vectorToFill = dir->printContent();
	return vectorToFill;
}

std::vector<std::string> FileSystem::splitPath(std::string path)
{
	std::vector<std::string> stringWords;
	std::vector<char> temp;
	int j = 0;
	int i = 0;
	bool finished = false;
	for (i; i < path.size(); i++)
	{
		if (path[i] != '/' /*|| path[i+1] != '\n'*/)
		{
			temp.push_back(path[i]);
			finished = false;
		}
		if (path[i] == '/')
		{
			//temp.push_back(path[i]);
			std::string tempString(temp.begin(), temp.end());
			stringWords.push_back(tempString);
			temp.clear();
			finished = true;
		}
	}
	if (i = path.size() && finished == false)
	{
		std::string tempString(temp.begin(), temp.end());
		stringWords.push_back(tempString);
	}
	return stringWords;
}

Directory * FileSystem::traverse(std::vector<std::string> stringWords, Directory *dir)
{
	Directory *destination = nullptr;
	for (unsigned int i = 0; i < stringWords.size(); i++)
	{
		if (i > 0)
		{
			dir = destination;
		}
		if (stringWords[i] == "..")
		{
			destination = dir->leaveFolder();
		}
		else
		{
			destination = dir->enterFolder(stringWords[i]);
		}
	}
	return destination;
}

void FileSystem::setCWD(Directory * dirPtr)
{
	this->dir = dirPtr;
}

Directory * FileSystem::getCWD()
{
	return this->dir;
}

std::vector<std::string> FileSystem::getWD(Directory * dirPtr)
{
	Directory *walker = dirPtr;
	std::vector<std::string> travels;
	while (walker->getParentName(walker) != walker->getName())
	{
		travels.insert(travels.begin(),walker->getName());
		walker = walker->getParentPtr(walker);
	}
	if (walker->getParentName(walker) == walker->getName())
	{
		travels.insert(travels.begin(), walker->getName());
	}

	return travels;
}




/* Please insert your code */