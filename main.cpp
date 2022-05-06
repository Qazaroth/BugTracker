#include <iostream>
#include <fstream>
#include <string>

#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#include <format>

#include "BugClass.h"
#include "FileHandler.h"
#include "Logging.h"


#define separator "***************"

#define bugIDsFile "bugIds"
#define bugFolder "bugs"
#define templateFile "bugs/templateBug"

void createTemplateFile()
{
	using namespace std;

	string fileName = "bugs/ID - Title";
	string data = "PRIORITY | Description | Type | Status";

	createFile(fileName, data);
}

void createBugFile(int id, Bug bug)
{
	using namespace std;

	string fileName = "bugs/" + to_string(id) + " - " + bug.getTitle();
	string data = bug.getPriority() + " | " + bug.getDescription() + " | " + bug.getType() + " | " + bug.getStatus();

	createFile(fileName, data);
}

void init()
{
	if (!path_exists(bugIDsFile))
		createFile(bugIDsFile, "0");

	if (!path_exists(templateFile))
		createTemplateFile();

	namespace fs = std::experimental::filesystem;

	if (!fs::is_directory(bugFolder) || !fs::exists(bugFolder))
		fs::create_directory(bugFolder);
}

int main()
{
	init();

	int latestId = std::stoi(readFile(bugIDsFile));
	bool endProgram = false;

	while (!endProgram)
	{
		system("cls");
		print(separator);
		print("Bug Tracker System");
		print(separator);
		print("1. File a new bug");
		print("2. Change status of a bug");
		print("3. Get information of a bug");
		print("4. Exit");
		print("");
		print("Enter your choice:");

		int choice = 4;

		std::cin >> choice;

		Bug bug;

		std::string title;
		std::string description;
		std::string bugType;

		char confirm;

		int priority, status;

		switch (choice)
		{
		case 1:
			system("cls");
			print(separator);
			print("Title of bug: (Replace spaces with \"_\")");
			print(separator);
			std::cin >> title;
			std::replace(title.begin(), title.end(), '_', ' ');
			bug.setTitle(title);

			system("cls");
			print(separator);
			print("Description of bug: (Replace spaces with \"_\")");
			print(separator);
			std::cin >> description;
			std::replace(description.begin(), description.end(), '_', ' ');
			bug.setDescription(description);

			system("cls");
			print(separator);
			print("Priority of bug: (Numbers only!)");
			print(separator);
			print("1 - High");
			print("2 - Medium");
			print("3 - Low");
			print(separator);
			std::cin >> priority;

			switch (priority)
			{
			case 1:
				print("Set bug priority to high!");
				bug.setPriority(BugPriority::HIGH);
				break;
			case 2:
				print("Set bug priority to medium!");
				bug.setPriority(BugPriority::MEDIUM);
				break;
			case 3:
				print("Set bug priority to low!");
				bug.setPriority(BugPriority::LOW);
				break;
			default:
				print("Set bug priority to default (Medium)!");
				bug.setPriority(BugPriority::MEDIUM);
				break;
			}
			bug.setStatus(BugStatus::UNASSIGNED);

			system("cls");
			print(separator);
			print("Type of bug: (Replace spaces with \"_\")");
			print(separator);
			std::cin >> bugType;
			std::replace(bugType.begin(), bugType.end(), '_', ' ');
			bug.setType(bugType);
		
			system("cls");
			latestId++;

			print(separator);
			print("Creating a new bug report with specified data:");
			print(separator);
			print("Title: " << bug.getTitle());
			print("Description: " << bug.getDescription());
			print("Priority: " << bug.getPriority());
			print("Status: " << bug.getStatus());
			print("Type: " << bug.getType());
			print(separator);
			print("Are you sure you want to create a new bug report with the above data? (Y/N)");
			std::cin >> confirm;

			print(separator);
			if (confirm == 'y' || confirm == 'Y')
			{
				createBugFile(latestId, bug);
				print("Created a new bug report with data specified above!");
			}
			else
				print("Restarting the bug report process...");
			
			system("pause");
			break;
		case 4:
			endProgram = true;
			break;
		default:
			break;
		}
	}
	return 0;
}