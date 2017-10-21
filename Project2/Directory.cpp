#include "Directory.h"

Directory::Directory(const Directory & originalObject)
{
	this->directories = originalObject.directories;
	this->files = originalObject.files;
	this->parent = originalObject.parent;
	this->cwd = originalObject.cwd;
	this->size = originalObject.size;
	this->blockNr = originalObject.blockNr;
}

Directory & Directory::operator=(const Directory & originalObject)
{
	/*if (this != originalObject) TODO: const eller what
	{
	??
	}*/
	this->directories = originalObject.directories;
	this->files = originalObject.files;
	this->parent = originalObject.parent;
	this->cwd = originalObject.cwd;
	this->size = originalObject.size;
	this->blockNr = originalObject.blockNr;
	return *this;
}

Directory::Directory()
{
	this->parent = this; //root
	this->name = "/";
	this->cwd = this;
}

Directory::~Directory()
{
	//Denna kommer behöva rensa flera nivåer av pekare?
}

Directory::Directory(std::string name, Directory * parent, Directory * cwd)
{
	this->name = name;
	this->parent = parent;
	this->cwd = cwd;
}

Directory* Directory::enterFolder(std::string name)
{
	Directory *object = nullptr;
	bool entered = false;
	int index = 0;
	for (unsigned int i = 0; i < directories.size() && entered == false; i++)
	{
		if (name == directories[i]->getName())
		{
			index = i;
			entered = true;
		}
	}
	if (entered == true)
	{
		object = directories[index];
		object->parent = this;
	}
	else
	{
		object = this;
	}
	return object;
}

Directory * Directory::leaveFolder()
{
	return this->parent;
}

std::string Directory::getName()
{
	return this->name;
}

std::vector<std::string> Directory::printContent()
{
	//Print directories
	std::vector <std::string> fileNameVector;
	//dir pekare ska hit, för att få till storlek och rätt directories
	for (unsigned int i = 0; i < this->directories.size(); i++)
	{
		fileNameVector.push_back(this->directories[i]->getName());
	}
	//Print files
	for (unsigned int i = 0; i < this->files.size(); i++)
	{
		fileNameVector.push_back(this->files[i].getName());
		fileNameVector.push_back(std::to_string(this->files[i].getBlockNr()));
		fileNameVector.push_back(std::to_string(this->files[i].getSize()));
	}
	return fileNameVector;
}

void Directory::printCWD()
{
	std::cout << this->getName() << std::endl;
}

bool Directory::hasItems(Directory * dir)
{
	bool hasItems = false;
	if (dir->directories.size() > 0)
	{
		hasItems = true;
	}
	if (dir->files.size() > 0)
	{
		hasItems = true;
	}
	return hasItems;
}

int Directory::getDirectoriesSize()
{
	return this->directories.size();
}

std::string Directory::getParentName(Directory * parentPtr)
{
	return this->parent->getName();
}

Directory * Directory::getParentPtr(Directory * parentPtr)
{
	return this->parent;
}


bool Directory::createFolder(std::string name, Directory *dir)
{
	bool added = false;
	try
	{
		if (name.empty())
		{
			directories.push_back(new Directory("noname", this, this));
		}
		else
		{
			directories.push_back(new Directory(name, dir, this));
		}
		//Skapar förhoppningsvis en Directory med namn, vars parent-pekare pekar på den mapp
		//Som den blev skapad i
		//cwd är samma
		added = true;
	}
	catch (std::string error)
	{
		std::cout << "An error occured: Faulty directory creation" << std::endl;
	}
	return added;
}

bool Directory::createFile(std::string name, int blockNr, int size)
{
	bool added = false;
	if (this->name != "/")
	{
		try
		{
			this->files.push_back(File(name, blockNr, size));
			added = true;
		}
		catch (std::string error)
		{
			std::cout << "An error occured: Faulty file creation" << std::endl;
		}
	}
	else
	{
		std::cout << "Error occured: Cannot create files in root-folder" << std::endl;
	}

	return added;
}

bool Directory::removeItem(std::string name)
{
	bool removed = false;
	for (unsigned int i = 0; i < this->directories.size() && removed == false; i++)
	{
		if (name == this->directories[i]->getName())
		{
			if (!this->directories[i]->hasItems(this)) //kollar sina vectorer efter items, hasItems returnerar true om det finns items
			{
				delete directories[i];
				directories[i] = nullptr;
				removed = true;
			}
			else
			{
				std::cout << "Temp error: folder has items" << std::endl;
				//Om directoryn har något i sig
			}

		}
	}
	for (unsigned int i = 0; i < this->files.size() && removed == false; i++)
	{
		if (name == this->files[i].getName())
		{
			files.erase(files.begin() + i); //ta bort den i:te filen
			removed = true;
		}
	}
	return removed;
}