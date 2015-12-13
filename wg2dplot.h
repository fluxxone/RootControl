#ifndef WG2DPLOT_H
#define WG2DPLOT_H
#include "widget.h"
#include "debug.h"
#include "sensor.h"
#define MAX_TRACE_NUM 5
#define VALUES_BUFFER_SIZE 16
class wg2DPlot : public Widget
{
public:
	wg2DPlot(int xarg, int yarg, int w, int h, uint8_t numDataPoints = 4 ) : Widget(xarg, yarg), _numDataPoints(numDataPoints){_width = w; _height = h; _numTraces = 0;}
	virtual void setValue(Emitter* emitter, uint32_t val)
	{
		for (uint8_t i = 0; i < _numTraces; i++)
		{
			if (emitter == (Emitter*)(_traces[i].sensor))
			{
				_traces[i].setValue(val);
			}
		}
	}
	virtual uint16_t getPixel(int xcoord, int ycoord);
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay) {return 0;}
	void addTrace(Sensor* sens,uint16_t minVal, uint16_t maxVal, uint16_t color)
	{

		_traces[_numTraces].minValue = minVal;
		_traces[_numTraces].maxValue = maxVal;
		_traces[_numTraces].sensor = sens;
		_traces[_numTraces].traceColor = color;
		_traces[_numTraces]._maxNumValues = _numDataPoints+1;
		sens->addListener(this);
		_numTraces++;
	}

protected:
	class Trace
	{
	public:
		Sensor* sensor;
		Trace()
		{
			_numValues = _valTail = _valHead = 0;
		}

		uint32_t maxValue;
		uint32_t minValue;
		uint16_t traceColor;
		uint16_t nextVal;
		uint16_t currVal;
		uint16_t getValue(int8_t index)
		{
			return _values[(_valTail+index+_numValues) % _numValues];
		}
		uint16_t getLastValue()
		{
			return _values[_valHead-1];
		}
		uint8_t getNumValues(){return _numValues;}
		void setValue(uint16_t val)
		{

			_values[_valHead] = val;
			DEBUG.print("Value on index %d set to %d!\r\n",_valHead,val);
			_valHead = (_valHead + 1) % _maxNumValues;
			if(_numValues < _maxNumValues)
				_numValues = _numValues + 1;
			else
				_valTail = _valHead;
		}
		uint16_t _values[VALUES_BUFFER_SIZE];
		uint8_t _maxNumValues;
		uint8_t _numValues;
		uint8_t _valTail;
		uint8_t _valHead;
	};
	Trace _traces[MAX_TRACE_NUM];
	uint8_t _numTraces;
	uint8_t _numDataPoints;
};

#endif // WG2DPLOT_H
