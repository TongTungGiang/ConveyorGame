#ifndef LOGICAL_OBJECT
#define LOGICAL_OBJECT

#include "Vector2.h"

class LogicalObject
{
protected:
	Vector2f logicalCoordinate;

public:
	LogicalObject() {}

	LogicalObject(Vector2f lCoord)
	{
		logicalCoordinate = lCoord;
	}

	float getLogicalX()
	{
		return logicalCoordinate.getX();
	}

	float getLogicalY()
	{
		return logicalCoordinate.getY();
	}

	Vector2f getLogicalCoord()
	{
		return logicalCoordinate;
	}

	void setLogicalCoordinate(float x, float y)
	{
		logicalCoordinate.setCoordinate(x, y);
	}

	void setLogicalCoordinate(Vector2f lCoord)
	{
		logicalCoordinate = lCoord;
	}
};

#endif