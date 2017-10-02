
#include "DirectedObject.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
DirectedObject::DirectedObject(Vector2f lCoord, unsigned int direction)
	: LogicalObject(lCoord)
{
	dir = direction;
}

//---------------------------------------------------------------------------------------------
//   get object's current direction
//
unsigned int DirectedObject::getDir()
{
	return dir;
}

//---------------------------------------------------------------------------------------------
//   set new direction
//
void DirectedObject::setDir(unsigned int newDirection)
{
	dir = newDirection;
}