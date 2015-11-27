#include "widget.h"
#include "display.h"
#include "sensor.h"
Widget::Widget(int xarg, int yarg):Listener(LISTENER_TYPE_WIDGET)
{
	x = xarg;
	y = yarg;
}
void Widget::addToDisplay(Display* display)
{
	display->addWidget(this);
}

void Widget::listen(Sensor* sensor)
{
	sensor->addListener(this);
}
void Widget::update(Emitter* emitter, uint32_t value)
{
	setValue(value);
}
bool Widget::isInside(uint16_t ax, uint16_t ay)
{
	return ((ax >= x) && (ax <= (x+getWidth())) && (ay >= y) && (ay <= (y+getHeight())));
}
