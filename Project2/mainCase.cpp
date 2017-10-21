#include <iostream>
#include "Directory.h"

void printMenu()
{
	std::cout << "1: Create folder" << std::endl;
	std::cout << "2: Create file" << std::endl;
	std::cout << "3: Remove file/folder" << std::endl;
	std::cout << "4: Enter folder" << std::endl;
	std::cout << "5: Leave folder" << std::endl;
	std::cout << "6: List files" << std::endl;
	std::cout << "7: Print cwd" << std::endl;
	std::cout << "8: Exit" << std::endl;


}

int main()
{
	

	int choice = -1;
	printMenu();
	Directory d1;
	Directory *cwd = &d1;
 //Bara root som är en instans av objektet, följande undermappar är pekare till objekt. 
	bool addedFirst = false;

	while (choice != 0)
	{
		
		std::cout << "Menu choice: ";
		std::cin >> choice;
		std::cin.ignore();

		if (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10)
		{
			std::cout << "Wrong input" << std::endl;
		}
		switch (choice)
		{
		case 1:
		{
			if (addedFirst == false)
			{
				std::string folderName;
				std::cout << "Enter foldername:";
				std::getline(std::cin, folderName);
				d1.createFolder(folderName);
				addedFirst = true;
			}
			else
			{
				std::string folderName;
				std::cout << "Enter foldername:";
				std::getline(std::cin, folderName);
				cwd->createFolder(folderName);
			}
			
			break;
		}
		case 2:
		{
			std::string fileName;
			std::cout << "Enter filename:";
			std::getline(std::cin, fileName);
			cwd->createFile(fileName);
			break;
		}
		case 3:
		{
			std::string rmName;
			std::cout << "Enter filename:";
			std::getline(std::cin, rmName);
			cwd->removeItem(rmName);
			break;
		}
		case 4:
		{
			std::string enterName;
			std::cout << "Enter filename:";
			std::getline(std::cin, enterName);
			cwd = cwd->enterFolder(enterName);
			//Skapa en ny pekare, som kan bli nullptr, jämför med cwd, för att inte riskera cwd bli nullptr
			break;
		}
		case 5:
		{
			cwd = cwd->leaveFolder();
			break;
		}
		case 6:
		{
			cwd->printShit();
			break;
		}
		case 7:
		{
			cwd->printCWD();
			break;
		}
		case 8:
		{
			choice = 0;
		}

		default:

			break;
		}
	}
	std::cout << "Exiting.." << std::endl;
	system("pause");
	return 0;
}