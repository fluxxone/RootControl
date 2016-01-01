#ifndef SDFILE_H
#define SDFILE_H
#include "sdcard.h"

class SDFile
{
public:
	SDFile(const char* filename);
	SDFile() :_opened(false){}
	~SDFile(){Close();}
	bool Open(const char* filename);
	void Close();
	UINT Size();
	UINT Write(char* buffer, UINT bufferSize);
	UINT Read(char* buffer, UINT bufferSize);
	void Sync();
protected:
	bool _opened;
	FIL _file;
	char _filename[16];
};

#endif // SDFILE_H
