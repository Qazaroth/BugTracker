#ifndef FHCLASS_DEFINED
#define FHCLASS_DEFINED

#include <iostream>

#include "Logging.h"
#include "BugClass.h"

inline bool static path_exists(const std::string &name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void static createFile(const std::string &name, const std::string data)
{
	using namespace std;

	string fileName = name + ".txt";
	ofstream file(fileName);

	if (file.good()) file << data;
	else print("Error occured while opening file \"" << name << "\"!");

	file.close();
}

std::string static readFile(const std::string &n)
{
	using namespace std;

	std::string name = n + ".txt";

	string data;

	if (path_exists(name))
	{
		ifstream file(name, ios::in);

		while (!file.eof())
		{
			file >> data;
		}
	}

	return data;
}
#endif