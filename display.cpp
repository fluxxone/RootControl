#include "display.h"
#include "screen.h"
#include "GLCD.h"
#include "widget.h"
Display* Display::instance = 0;

Display::Display() : _num_screens(0),_active_screen(-1)
{
	if(instance != 0)
		return;
	instance = this;
	LCD_Initializtion();
}

Widget* Display::getTargetWidget(uint16_t x, uint16_t y)
{
	Screen* currentScreen = _screens[_active_screen];
	return currentScreen->getTargetWidget(x,y);
}

void Display::run()
{
	DEBUG.print("Display thread started!\r\n");
	if(_active_screen == -1)
	{
		DEBUG.print("No active screens, display thread exiting!\r\n");
		return;
	}

	while(1)
	{
		Screen* currentScreen = _screens[_active_screen];
		uint16_t i = 0, j = 0, k = 0, w = 0;
		bool isOnWidget = false;
		LCD_SetCursor(0,0);
		LCD_WriteRAM_Prepare();
		uint16_t c = 0;
		for(j=0;j<DISPLAY_HEIGHT;j++)
		{
			for(i=0;i<DISPLAY_WIDTH;i++)
			{

				isOnWidget = false;
				for(k = 0; k < currentScreen->getNumWidgets(); k++)
				{
					if(currentScreen->widgets[k]->isInside(i,j))
					{
						isOnWidget = true, w = k;
						break;
					}
				}
				if(isOnWidget)
					LCD_WriteRAM(currentScreen->widgets[w]->getPixel(i,j));
				else
				{
					c=0x1F|((0x3f-(j>>2))<<5)|((0x1f-(j>>3))<<11);
					LCD_WriteRAM(c);
				}

			}
		}
		CoTimeDelay(0,0,0,25);
	}
}
