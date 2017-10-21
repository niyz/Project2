#include <iostream>
#include "Directory.h"

int main()
{

	Directory d1; //Bara root som är en instans av objektet, följande undermappar är pekare till objekt. 
	Directory *cwd = d1;
	std::cout << "CWD: ";
	d1.printCWD();


	std::cout << "Create folder: Skola in root" << std::endl;
	d1.createFolder("Skola");
	std::cout << "Enter Skola in root" << std::endl;
	cwd = d1.enterFolder("Skola");
	std::cout << "CWD: ";
	cwd->printCWD();


	std::cout << "Create folder: Matte in Skola" << std::endl;
	cwd->createFolder("Matte");
	std::cout << "Enter Matte in Skola" << std::endl;
	cwd = cwd->enterFolder("Matte");
	std::cout << "CWD: ";
	cwd->printCWD();


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	cwd->createFile("OLDCUNT");

	std::cout << "Prints the contents of CWD: ";

	cwd->printCWD();

	cwd->printShit();

	cwd = cwd->leaveFolder();

	std::cout << std::endl;
	std::cout << std::endl;

	cwd->createFile("NEWCUNT");

	std::cout << "Prints the contents of CWD: ";

	cwd->printCWD();
	cwd->printShit();






	system("pause");
	return 0;
}