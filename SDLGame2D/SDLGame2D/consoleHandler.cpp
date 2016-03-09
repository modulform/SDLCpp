#include "consoleHandler.h"

std::string getCurrentTime()
{
	std::string helper = "";

	time_t now = time(0);	//get current date/time (local system)
	tm localTime;
	localtime_s(&localTime, &now);
	
	helper.append(std::to_string(localTime.tm_hour));
	helper.append(":");
	helper.append(std::to_string(localTime.tm_min));
	helper.append(":");
	helper.append(std::to_string(localTime.tm_sec));
	
	return helper;
}

void logToConsole(char* msg, const char* details)
{
	time_t now = time(0);	//get current date/time (local system)
	tm localTime;
	localtime_s(&localTime, &now);

	if (details != nullptr)
	{
		std::cout << std::setfill('0') << std::setw(2) << localTime.tm_hour << ":" << std::setw(2) << localTime.tm_min << ":" << std::setw(2) << localTime.tm_sec;
		std::cout << " - " << msg << "(" << details << ")" << std::endl;
	}
	else
	{
		std::cout << std::setfill('0') << std::setw(2) << localTime.tm_hour << ":" << std::setw(2) << localTime.tm_min << ":" << std::setw(2) << localTime.tm_sec;
		std::cout << " - " << msg << std::endl;
	}
}