#ifndef _EMITTER_H_
#define _EMITTER_H_

#define EMITTER_TYPE_EMITTER 0
class Emitter
{
public:
	Emitter(){}
	virtual int getEmitterType(){return EMITTER_TYPE_EMITTER;}

};

#endif //_EMITTER_H_
