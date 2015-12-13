#include "wg2dplot.h"
#include "sensor.h"
uint16_t wg2DPlot::getPixel(int xcoord, int ycoord)
{
	uint16_t xc = xcoord - x;
	uint16_t yc = ycoord - y;
	uint16_t pix = 0xFFFF;

	uint16_t interval = ((_width+1)/_numDataPoints);

	if(xc == 0 || yc == 0 || xc == _width || yc == _height || xc % interval == 0)
	{
		pix = ~pix;
	}
	uint16_t val = 0;
	for (uint8_t i = 0; i < _numTraces; i++)
	{
		int8_t dataInd =  xc / interval;
		if(_traces[i].getNumValues() - xc / interval - 1 < 0)
			continue;
		if(xc % interval == 0)
		{
			_traces[i].currVal = _traces[i].getValue(dataInd);
			_traces[i].nextVal = _traces[i].getValue(dataInd+1);
			val = _traces[i].currVal;
		}
		else
		{
			val = _traces[i].currVal + ((xc % interval)*(_traces[i].nextVal - _traces[i].currVal))/(interval-1);
		}
		int yval = _height-(val-_traces[i].minValue)*_height/(_traces[i].maxValue-_traces[i].minValue);
		if(yc == yval)
			pix = pix & _traces[i].traceColor;

	}
	return pix;
}

