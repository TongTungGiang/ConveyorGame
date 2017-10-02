#ifndef DIRECTED_OBJECT_H
#define DIRECTED_OBJECT_H

#include "Definition.h"
#include "LogicalObject.h"

class DirectedObject : public LogicalObject
{

protected:

	unsigned int dir;

public:
	DirectedObject() {};
	DirectedObject(Vector2f lCoord, unsigned int direction);

	unsigned int getDir();
	void setDir(unsigned int newDirection);

};

#endif