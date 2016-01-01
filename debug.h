#ifndef DEBUG_H
#define DEBUG_H
#include "sdfile.h"
//this class should be singleton, but we have no dynamic memory, so we do what we can
#define DEBUG (static_cast<Debug&>(Debug::getInstance()))

class Debug
{
public:
	static Debug& getInstance();
	void print(const char* format, ...);
protected:
	Debug();
	char buffer[255];
	SDFile _logfile;
};

#endif // DEBUG_H
