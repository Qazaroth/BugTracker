#include <iostream>
#include <fstream>

#define print(x) std::cout << x << std::endl
#define separator "***************"

#define bugIDsFile "bugIds.txt"

inline bool file_exists(const std::string &name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

struct BugStruct
{
	std::string title;
	std::string type;
	std::string priority;
	std::string description;
	std::string status;
};

void createFile(BugStruct bug)
{

}

std::string readFile(const std::string &name)
{
	using namespace std;

	string data;

	if (file_exists(name))
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

	ofstream f(name);

	if (f.good())
	{
		f << data;
	}
	else
	{
		print("Error occured while opening file " << name << "!");
	}

	f.close();
}

int main()
{
	
	if (!file_exists(bugIDsFile))
		createFile(bugIDsFile, "0");

	print(readFile(bugIDsFile));

	print(separator);
	print("Bug Tracker System");
	print(separator);
	system("pause");
	return 0;
}