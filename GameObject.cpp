#include "GameObject.h"

//---------------------------------------------------------------------------------------------
//   class constructor
//
GameObject::GameObject(Vector2f lCoord, unsigned int textureID, unsigned int direction)
{
	this->setLogicalCoordinate(lCoord);
	this->setGraphicCoordinate(FrameWork::Converter::instance()->fwc_logicCoordToGraphicCoord(lCoord));
	this->textureID = textureID;
	this->dir = direction;
}