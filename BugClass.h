#ifndef BUGCLASS_DEFINED
#define BUGCLASS_DEFINED
#include <iostream>

enum class BugStatus
{
	UNASSIGNED,
	IN_PROGRESS,
	FIXED,
	UPDATED
};

enum class BugPriority
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
	BugPriority _priority = BugPriority::MEDIUM;
	std::string _description;
	BugStatus _status = BugStatus::UNASSIGNED;

public:
	std::string getTitle() const { return _title; };
	std::string getType() const { return _type; };
	std::string getPriority() const;
	std::string getDescription() const { return _description; };
	std::string getStatus() const;

	void setTitle(const std::string title) { _title = title; };
	void setType(const std::string type) { _type = type; };
	void setDescription(const std::string description) { _description = description; };

	void setPriority(std::string priority);
	void setPriority(const BugPriority priority) { _priority = priority; };

	void setStatus(const BugStatus status) { _status = status; };
	void setStatus(std::string status);
};
#endif