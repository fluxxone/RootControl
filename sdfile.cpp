#include "sdfile.h"
#include "sdcard.h"
#include "debug.h"
#include "string.h"
#include "CoOS.h"
SDFile::SDFile(const char* filename)
{
	_opened = Open(filename);
}

bool SDFile::Open(const char* filename)
{
	if(_opened)
		Close();
	bool result = false;
	if(SDCARD.isInitialized() && strlen(filename) < 16)
	{
		FRESULT res;
		CoSchedLock();
		res = f_open(&_file,filename,FA_READ|FA_OPEN_ALWAYS|FA_WRITE);
		CoSchedUnlock();
		if (res == FR_OK)
		{
			strcpy(_filename,filename);
			_opened = true;
			result = true;
		}
		else
			;//DEBUG.print("Unable to open file, returned error %d\r\n",res);
	}
	return result;
}
UINT SDFile::Size()
{
	return f_size(&_file);
}

void SDFile::Close()
{
	if(_opened)
	{
		_opened = false;
		CoSchedLock();
		f_close(&_file);
		CoSchedUnlock();
	}
	else
		DEBUG.print("File not opened\r\n");
}

UINT SDFile::Write(char* buffer, UINT bufferSize)
{
	FRESULT res;
	UINT bytesWritten = 0U;
	if(_opened)
	{
		CoSchedLock();
		res = f_lseek(&_file, f_size(&_file));
		CoSchedUnlock();
		if (res != FR_OK)
		{
			f_close(&_file);
			_opened = false;
			DEBUG.print("Error occured during seeking, e = %d\r\n",res);
		}
		else
		{
			CoSchedLock();
			if((res = f_write(&_file,(void*)buffer,bufferSize,&bytesWritten)) != FR_OK)
			{
				bytesWritten = 0U;
				DEBUG.print("Unable to write file, returned error %d\r\n",res);
			}
			CoSchedUnlock();
		}

	}
	return bytesWritten;
}
void SDFile::Sync()
{
	if(_opened)
	{
		CoSchedLock();
		f_sync(&_file);
		CoSchedUnlock();
	}
}

UINT SDFile::Read(char* buffer, UINT bufferSize)
{
	FRESULT res;
	UINT bytesRead = 0U;
	if(_opened)
	{
		CoSchedLock();
		if((res = f_read(&_file,(void*)buffer,bufferSize,&bytesRead)) != FR_OK)
		{
			bytesRead = 0U;
			DEBUG.print("Unable to read file, returned error %d\r\n",res);
		}
		CoSchedUnlock();

	}
	return bytesRead;
}
