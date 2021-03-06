#ifndef PROJECT_H
#define PROJECT_H

typedef enum
{
	SENSOR_ID_HUMIDITY,
	SENSOR_ID_TEMPERATURE,
	SENSOR_ID_REF_HUMIDITY,
	SENSOR_ID_REF_TEMPERATURE,
	SENSOR_ID_DUMMY,
	SENSOR_ID_CLOCK,
	SENSOR_ID_DISPLAY,

	SENSOR_ID_MAX
} SENSOR_ID;
#define COLOR_RED	0xF800
#define COLOR_GREEN	0x07E0
#define COLOR_BLUE	0x001F
#define COLOR_WHITE	0xFFFF
#define COLOR_BLACK	0x0000
#endif // PROJECT_H

