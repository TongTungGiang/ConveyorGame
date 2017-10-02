#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector2.h"
#include "DirectedObject.h"
#include "GraphicObject.h"

class GameObject : public GraphicObject, public DirectedObject
{
public:
	GameObject() {};
	GameObject(Vector2f lCoord, unsigned int textureID, unsigned int direction);

	struct PerspectiveSort
	{
		bool operator () (GameObject* first, GameObject* second)
		{
			Vector2f t1 = first->getLogicalCoord();
			Vector2f t2 = second->getLogicalCoord();

			if (t1.getX() - PACKAGE_SPEED < t2.getX() && t2.getX() < t1.getX() + PACKAGE_SPEED)
			{
				return t1.getY() > t2.getY();
			}

			else
			{
				return t1.getX() > t2.getX();
			}
		}
	};

	void updateCoordinate(float xLCoord, float yLCoord)
	{
		Vector2i gCoord = FrameWork::Converter::instance()->fwc_logicCoordToGraphicCoord(Vector2f(xLCoord, yLCoord));
		setLogicalCoordinate(xLCoord, yLCoord);
		setGraphicCoordinate(gCoord);
	}
	virtual void render()
	{
		GraphicObject::render();
	}
};

#endif