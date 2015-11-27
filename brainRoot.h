#ifndef _BRAINROOT_H_
#define _BRAINROOT_H_
#include "brain.h"

class Emitter;
class BrainRoot : public Brain
{
public:
	//virtual void update(Emitter* emitter, int value);
	virtual void run();
};
#endif //_BRAINROOT_H_
