#include "consoleHandler.h"

void logToConsole(char* msg, const char* details)
{
	if (details != nullptr)
	{
		std::cout << msg << "(" << details << ")" << std::endl;
	}
	else
	{
		std::cout << msg << std::endl;
	}
}