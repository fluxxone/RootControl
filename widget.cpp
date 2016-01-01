#include "widget.h"
#include "screen.h"
#include "sensor.h"
Widget::Widget(uint16_t xarg, uint16_t yarg, uint16_t height, uint16_t width):Listener(LISTENER_TYPE_WIDGET)
{
	_x = xarg;
	_y = yarg;
	_height = height;
	_width = width;
}
void Widget::addToDisplay(Screen* display)
{
	display->addWidget(this);
}

void Widget::listen(Sensor* sensor)
{
	sensor->addListener(this);
}
void Widget::update(Emitter* emitter, void* data, DATA_TYPE data_type)
{
	switch (data_type) {
	case DATA_TYPE_UINT32:
		setValue(emitter,*((uint32_t*)data));
		break;
	case DATA_TYPE_INVALID:
		setValue(emitter,0);
		break;
	default:
		break;
	}

}
bool Widget::isInside(uint16_t ax, uint16_t ay)
{
	return ((ax >= _x) && (ax <= (_x+getWidth())) && (ay >= _y) && (ay <= (_y+getHeight())));
}
