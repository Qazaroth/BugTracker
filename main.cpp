#include <iostream>
#include <fstream>
#include <string>

#define print(x) std::cout << x << std::endl
#define separator "***************"

#define bugIDsFile "bugIds.txt"

inline bool path_exists(const std::string &name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

enum BugStatus
{
	UNASSIGNED,
	IN_PROGRESS,
	FIXED,
	UPDATED
};

enum BugPriority
{
	HIGH,
	MEDIUM,
	LOW
};

class Bug
{
private:
	std::string _title;
	std::string _type;
	std::string _priority;
	std::string _description;
	BugStatus _status = UNASSIGNED;

public:
	std::string getTitle() { return _title; };
	std::string getType() { return _type; };
	std::string getPriority() { return _priority; };
	std::string getDescription() { return _description; };
	BugStatus getStatus() { return _status; };

	void setTitle(std::string title) { _title = title; };
	void setType(std::string type) { _type = type; };
	void setPriority(std::string priority) { _priority = priority; };
	void setDescription(std::string description) { _description = description; };
	void setStatus(BugStatus status) { _status = status; };
};

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

	ofstream f(name + ".txt");//"/bugs/" + name + ".txt");

	if (f.good()) f << data;
	else print("Error occured while opening file " << name << "!");

	f.close();
}

void createBugFile(int id, Bug bug)
{
	using namespace std;

	string status = "Unassigned";

	switch (bug.getStatus())
	{
	case UNASSIGNED:
		status = "Unassigned";
		break;
	case IN_PROGRESS:
		status = "In progress";
		break;
	case FIXED:
		status = "Fixed";
		break;
	case UPDATED:
		status = "Updated";
		break;
	default:
		status = "Unassigned";
		break;
	}

	string fileName = to_string(id) + " - " + bug.getTitle();
	string data = bug.getPriority() + " | " + bug.getDescription() + " | " + bug.getType() + " | " + status;

	createFile(fileName, data);
}

int main()
{
	
	if (!path_exists(bugIDsFile))
		createFile(bugIDsFile, "0");

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

		switch (choice)
		{
		case 1:
			bug.setTitle("Test");
			bug.setDescription("Test Description");
			bug.setPriority("HIGH");
			bug.setStatus(UNASSIGNED);
			bug.setType("Type A");

			latestId++;

			createBugFile(latestId, bug);
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