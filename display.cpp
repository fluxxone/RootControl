#include "display.h"
#include "GLCD.h"
#include "widget.h"

void Display::SetPixelMask(uint16_t x, uint16_t y)
{
	widgetMask[(x*DISPLAY_HEIGHT)/8+y]|=(1<<((x*DISPLAY_HEIGHT)%8));
}
bool Display::GetPixelMask(uint16_t x, uint16_t y)
{
	return (widgetMask[(x*DISPLAY_HEIGHT)/8+y])&(1<<((x*DISPLAY_HEIGHT)%8)) > 0;
}

void Display::addWidget(Widget* widget)
{
	widgets[numWidgets++] = widget;

	for(uint16_t i=0;i<DISPLAY_WIDTH;i++)
	{
		for(uint16_t j=0;j<DISPLAY_HEIGHT;j++)
		{
			if((i >= widget->x) && (i <= (widget->x+widget->getWidth())) && (j >= widget->y) && (j <= (widget->y+widget->getHeight())))
				SetPixelMask(i,j);
		}
	}
}

Display::Display()
{
	numWidgets = 0;
	LCD_Initializtion();
	for(uint16_t i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT/8 + DISPLAY_HEIGHT; i++)
		widgetMask[i] = 0;
}
uint16_t Display::getPixels(int x, int y)
{

}
Widget* Display::getTargetWidget(uint16_t x, uint16_t y)
{
	uint16_t k = 0, w = 0;
	bool isOnWidget = false;
	for(k = 0; k < numWidgets; k++)
	{
		if(widgets[k]->isInside(x,y))
		{
			isOnWidget = true, w = k;
			break;
		}
	}
	if(isOnWidget)
		return widgets[w];
	else
		return 0;

}

void Display::run()
{
	while(1)
	{
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
				for(k = 0; k < numWidgets; k++)
				{
					if(widgets[k]->isInside(i,j))
					{
						isOnWidget = true, w = k;
						break;
					}
				}
				if(isOnWidget)
					LCD_WriteRAM(widgets[w]->getPixel(i,j));
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
