#ifndef COMMAND_BUTTON_H
#define COMMAND_BUTTON_H

#include "Vector2.h"
#include "FrameWork.h"
#include "Definition.h"

class CommandButton
{
private:
	unsigned int iconTextureID_nonActive;
	unsigned int iconTextureID_active;
	Vector2i originCoordinates;
	Vector2i dimensions;
	unsigned int state;
	std::function<void()> command;

public:
	CommandButton(Vector2i coord, Vector2i dimensions, std::function<void()> command, unsigned int iconTextureID_nonActive, unsigned int iconTextureID_active)
		: originCoordinates(coord), dimensions(dimensions), command(command), iconTextureID_active(iconTextureID_active),
		iconTextureID_nonActive(iconTextureID_nonActive), state(NONACTIVE) {}

	~CommandButton() {};

	Vector2i getOriginCoordinates()
	{
		return originCoordinates;
	}

	unsigned int getState()
	{
		return state;
	}

	void setState(unsigned int state)
	{
		this->state = state;
	}

	bool checkIntrusion(Vector2i checkPosition)
	{ 
		int bx = originCoordinates.getX(),
			by = originCoordinates.getY(),
			tx = checkPosition.getX(),
			ty = checkPosition.getY(),
			dx = dimensions.getX(),
			dy = dimensions.getY();

		return (bx < tx && tx < bx + dx && by < ty && ty < by + dy);
	}

	void doCommand()
	{
		command();
	}

	void render()
	{
		int x_coord = originCoordinates.getX(),
			y_coord = originCoordinates.getY();

		if (state == NONACTIVE)
		{
			FrameWork::TextureManager::instance()->fwtm_renderTexture(iconTextureID_nonActive, x_coord, y_coord);
		

		}
		else if (state == HOVER || state == ACTIVE)
		{
			FrameWork::TextureManager::instance()->fwtm_renderTexture(iconTextureID_active, x_coord, y_coord);
		}
	}
};


#endif
