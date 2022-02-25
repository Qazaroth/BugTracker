#include <iostream>
#include <fstream>
#include <string>

#ifndef _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#include <format>

#include "BugClass.h"

#define print(x) std::cout << x << std::endl
#define separator "***************"

#define bugIDsFile "bugIds.txt"
#define bugFolder "bugs"
#define templateFile "bugs/templateBug.txt"

inline bool path_exists(const std::string &name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string readFile(const std::string &name)
{
	using namespace std;

	string data;

	if (path_exists(name))
	{
		fstream file(name, ios::in);

		while (!file.eof())
		{
			file >> data;
		}
	}

	return data;
}

void createFile(const std::string &name, const std::string data)
{
	using namespace std;

	string fileName = name + ".txt";
	ofstream file(fileName);

	if (file.good()) file << data;
	else print("Error occured while opening file \"" << name << "\"!");

	file.close();
}

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

int main()
{
	
	if (!path_exists(bugIDsFile))
		createFile(bugIDsFile, "0");

	if (!path_exists(templateFile))
		createTemplateFile();

	namespace fs = std::experimental::filesystem;

	if (!fs::is_directory(bugFolder) || !fs::exists(bugFolder))
		fs::create_directory(bugFolder);

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
		std::string type;

		int priority, status;

		switch (choice)
		{
		case 1:
			system("cls");
			print(separator);
			print("Title of bug? (No spaces allowed!)");
			print(separator);
			std::cin >> title;
			bug.setTitle(title);

			print(separator);
			print("Description of bug: (No spaces allowed!)");
			print(separator);
			std::cin >> description;
			bug.setDescription(description);
			bug.setPriority("HIGH");
			bug.setStatus(BugStatus::UNASSIGNED);
			bug.setType("Input");
		
			system("cls");
			latestId++;

			print(separator);
			print("Creating a new bug with specified data:");
			print(separator);
			print("Title: " << bug.getTitle());
			print("Description: " << bug.getDescription());
			print("Priority: " << bug.getPriority());
			print("Status: " << bug.getStatus());
			print("Type: " << bug.getType());
			createBugFile(latestId, bug);
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