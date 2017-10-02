#include "Package.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
Package::Package(Vector2f lCoord, unsigned int textureID, unsigned int direction, unsigned int request)
: GameObject(lCoord, textureID, direction), request(request)
{
	speed = PACKAGE_SPEED;
}

//---------------------------------------------------------------------------------------------
//   get type of package
//
unsigned int Package::getRequest()
{
	return request;
}

//---------------------------------------------------------------------------------------------
//   move package
//
void Package::move()
{
	float x = logicalCoordinate.getX();
	float y = logicalCoordinate.getY();
	switch (dir)
	{
	case NORTH:
		x += speed;
		break;

	case SOUTH:
		x -= speed;
		break;

	case EAST:
		y -= speed;
		break;

	case WEST:
		y += speed;
		break;
	}
	updateCoordinate(x, y);

	callout(Vector2i(graphicCoordinate.getX() + 40, graphicCoordinate.getY() + 50), CALLOUT);
}

//---------------------------------------------------------------------------------------------
//   check collision between a package and a game object
//
bool Package::checkCollision(LogicalObject object)
{
	float objectX = object.getLogicalX();
	float objectY = object.getLogicalY();

	float packageX = logicalCoordinate.getX();
	float packageY = logicalCoordinate.getY();

	if (packageX < objectX - speed || objectX + speed < packageX ||
		packageY < objectY - speed || objectY + speed < packageY)
	{
		return false;
	}
	return true;
}

#define MS_PER_FRAME 30

void Package::playMovingAnimation()
{
	fw_Rectangle tmp_s, tmp_d;
	switch (dir)
	{
	case NORTH:
		FrameWork::fw_setRectDimension(&tmp_s, 32 * (int)(((FrameWork::Timer::instance()->fwt_getTime()) / MS_PER_FRAME) % 16),
			240, 32, 80);
		break;

	case WEST:
		FrameWork::fw_setRectDimension(&tmp_s, 32 * (int)(((FrameWork::Timer::instance()->fwt_getTime()) / MS_PER_FRAME) % 16),
			160, 32, 80);
		break;

	case SOUTH:
		FrameWork::fw_setRectDimension(&tmp_s, 32 * (int)(((FrameWork::Timer::instance()->fwt_getTime()) / MS_PER_FRAME) % 16),
			80, 32, 80);
		break;

	case EAST:
		FrameWork::fw_setRectDimension(&tmp_s, 32 * (int)(((FrameWork::Timer::instance()->fwt_getTime()) / MS_PER_FRAME) % 16),
			0, 32, 80);
		break;
	}
	FrameWork::fw_setRectDimension(&tmp_d, graphicCoordinate.getX() + 32, graphicCoordinate.getY() + 16, 20, 48);
	FrameWork::TextureManager::instance()->fwtm_renderTexture(textureID, tmp_s, tmp_d);
}

void Package::render()
{
	playMovingAnimation();
	callout.render();         // draw the callout
	FrameWork::TextureManager::instance()->fwtm_renderTexture(request, callout.getGraphicX() + 12, callout.getGraphicY() + 13, 0.7f); // draw the request
}
