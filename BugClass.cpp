#include "BugClass.h"

#include <algorithm>

std::string Bug::getPriority() const
{
	std::string res = "MEDIUM";

	switch (_priority)
	{
	case BugPriority::HIGH:
		res = "HIGH";
		break;
	case BugPriority::MEDIUM:
		res = "MEDIUM";
		break;
	case BugPriority::LOW:
		res = "LOW";
		break;
	default:
		res = "MEDIUM";
		break;
	}

	return res;
}

std::string Bug::getStatus() const
{
	std::string res = "Unassigned";

	switch (_status)
	{
	case BugStatus::UNASSIGNED:
		res = "Unassigned";
		break;
	case BugStatus::IN_PROGRESS:
		res = "In progress";
		break;
	case BugStatus::FIXED:
		res = "Fixed";
		break;
	case BugStatus::UPDATED:
		res = "Updated";
		break;
	default:
		res = "Unassigned";
		break;
	}

	return res;
}

void Bug::setPriority(std::string priority)
{
	std::transform(priority.begin(), priority.end(), priority.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (priority == "high")
	{
		this->_priority = BugPriority::HIGH;
	}
	else if (priority == "medium")
	{
		this->_priority = BugPriority::MEDIUM;
	}
	else if (priority == "low")
	{
		this->_priority = BugPriority::LOW;
	}
	else
	{
		this->_priority = BugPriority::MEDIUM;
	}
}

void Bug::setStatus(std::string status)
{
	std::transform(status.begin(), status.end(), status.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (status == "unassigned")
	{
		this->_status = BugStatus::UNASSIGNED;
	}
	else if (status == "in progress")
	{
		this->_status = BugStatus::IN_PROGRESS;
	}
	else if (status == "fixed")
	{
		this->_status = BugStatus::FIXED;
	}
	else if (status == "updated")
	{
		this->_status = BugStatus::UPDATED;
	}
}