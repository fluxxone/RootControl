#ifndef SDCARD_H
#define SDCARD_H
#include "SDCard/FATFS/src/ff.h"
#include "SDCard/FATFS/src/ffconf.h"
//this class should be singleton, but we have no dynamic memory, so we do what we can
#define SDCARD (static_cast<SDCard&>(SDCard::getInstance()))

class SDCard
{
public:
	static SDCard& getInstance();
	bool isInitialized() {return _initialized;}

protected:
	bool _initialized;
	SDCard();
	FATFS fs;         /* Work area (file system object) for logical drive */
	FIL fsrc;         /* file objects */
	FRESULT res;
	UINT br;
};

#endif // SDCARD_H
