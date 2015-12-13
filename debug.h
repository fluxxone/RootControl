#ifndef DEBUG_H
#define DEBUG_H

//this class should be singleton, but we have no dynamic memory, so we do what we can
#define DEBUG (static_cast<Debug&>(Debug::getInstance()))

class Debug
{
public:
	Debug();
	static Debug& getInstance();
	void print(const char* format, ...);
protected:
	static Debug* instance;
	char buffer[255];
};

#endif // DEBUG_H
