#include "File.h"

File::File()
{
	this->name = "";
	this->size = -1;
	this->blockNr = -1;
}

File::File(std::string name, int blockNr , int size)
{
	this->name = name;
	this->size = size;
	this->blockNr = blockNr;
}

File::~File()
{
	//Statisk
}

File::File(const File & originalObject)
{
	this->name = originalObject.name;
	this->size = originalObject.size;
	this->blockNr = originalObject.blockNr;
}

File & File::operator=(const File & originalObject)
{
	this->name = originalObject.name;
	this->size = originalObject.size;
	this->blockNr = originalObject.blockNr;
	return *this;
}

std::string File::getName()
{
	return this->name;
}

void File::setName(std::string name)
{
	this->name = name;
}

void File::setSize(int size)
{
	this->size = size;
}

void File::setBlockNr(int blockNr)
{
	this->blockNr = blockNr;
}

int File::getBlockNr()
{
	return this->blockNr;
}

int File::getSize()
{
	return this->size;
}
