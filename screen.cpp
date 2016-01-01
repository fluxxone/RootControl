#include "screen.h"
#include "GLCD.h"
#include "widget.h"
#include "debug.h"
//void Screen::SetPixelMask(uint16_t x, uint16_t y)
//{
//	widgetMask[(x*DISPLAY_HEIGHT)/8+y]|=(1<<((x*DISPLAY_HEIGHT)%8));
//}
//bool Screen::GetPixelMask(uint16_t x, uint16_t y)
//{
//	return (widgetMask[(x*DISPLAY_HEIGHT)/8+y])&(1<<((x*DISPLAY_HEIGHT)%8)) > 0;
//}

void Screen::addWidget(Widget* widget)
{
	if(numWidgets == SCREEN_MAX_NUM_WIDGETS)
	{
		DEBUG.print("Max number of widgets reached, no more will be added to this screen!\r\n ");
		return;
	}
	widgets[numWidgets++] = widget;

	for(uint16_t i=0;i<DISPLAY_WIDTH;i++)
	{
		for(uint16_t j=0;j<DISPLAY_HEIGHT;j++)
		{
			if((i >= widget->getX()) && (i <= (widget->getX()+widget->getWidth())) && (j >= widget->getY()) && (j <= (widget->getY()+widget->getHeight())))
				;//SetPixelMask(i,j);
		}
	}
}

Screen::Screen()
{
	numWidgets = 0;
	for(uint16_t i = 0; i < DISPLAY_WIDTH*DISPLAY_HEIGHT/8 + DISPLAY_HEIGHT; i++)
		;//widgetMask[i] = 0;
}
uint16_t Screen::getPixels(int x, int y)
{

}
Widget* Screen::getTargetWidget(uint16_t x, uint16_t y)
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
