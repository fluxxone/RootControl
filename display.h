#ifndef DISPLAY_H
#define DISPLAY_H
#define DISPLAY_MAX_SCREENS 8
#define DISPLAY_HEIGHT	240
#define DISPLAY_WIDTH	320
#include "debug.h"
#include "cothread.h"

//this class should be singleton, but we have no dynamic memory, so we do what we can
#define DISPLAY (static_cast<Display&>(Display::getInstance()))

class Screen;
class Widget;


class Display : public CoThread
{
public:
	Display();
	void addScreen(Screen* screen)
	{
		if(_num_screens == 0)
		{
			_active_screen = 0;
		}
		if(_num_screens == DISPLAY_MAX_SCREENS-1)
		{
			DEBUG.print("Maximum number of screens reached, you cannot add new screens\r\n");
			return;
		}
		_screens[_num_screens] = screen;
		_num_screens++;
	}
	Widget* getTargetWidget(uint16_t x, uint16_t y);
	uint8_t getNumScreens() { DEBUG.print("num=%d\r\n",_num_screens); return _num_screens;}
	uint8_t getActiveScreen() { DEBUG.print("act=%d\r\n",_active_screen); return _active_screen;}
	void setActiveScreen(uint8_t arg) { if (arg<_num_screens) _active_screen = arg;}
	static Display& getInstance()
	{
		return *instance;
	}

	virtual void run();

protected:
	static Display* instance;
	Screen* _screens[DISPLAY_MAX_SCREENS];
	uint8_t _num_screens;
	int8_t _active_screen;
};

#endif // DISPLAY_H
