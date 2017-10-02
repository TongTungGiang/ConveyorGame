#ifndef PACKAGE_H
#define PACKAGE_H

#include "GameObject.h"

#define PACKAGE_SPEED 0.002f

class Package : public GameObject
{

private:

	GraphicObject callout;
	unsigned int request;
	float speed;

public:

	Package(Vector2f lCoord, unsigned int textureID, unsigned int direction, unsigned int request);

	unsigned int getRequest();

	void move();
	void render();

	void playMovingAnimation();

	bool checkCollision(LogicalObject object);

};

#endif