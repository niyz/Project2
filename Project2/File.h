#ifndef FILE_H
#define FILE_H
#include <string>

class File
{
private:
	std::string name;
	int size; //0-512, vad har filen själv för storlek?
	int blockNr; //1-250

public:
	File();
	File(std::string name, int blockNr, int size);
	~File();

	File(const File &originalObject); //Copy
	File& operator=(const File &originalObject); //tilldening
	std::string getName();
	void setName(std::string name);
	void setSize(int size);
	void setBlockNr(int blockNr);
	int getBlockNr();
	int getSize();

};
#endif // !FILE_H
