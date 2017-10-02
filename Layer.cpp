#include "Layer.h"
#include <conio.h>
Layer::Layer(unsigned int blankTextureID) : blankTextureID(blankTextureID)
{
	/*
	tileMatrix = new GraphicObject*[MAP_SQR_Y_DIMENSIONS];
	*/
	for (int i = 0; i < MAP_SQR_Y_DIMENSIONS; i++)
	{
		/*
		tileMatrix[i] = new GraphicObject[MAP_SQR_X_DIMENSIONS];
		*/
		for (int j = 0; j < MAP_SQR_X_DIMENSIONS; j++)
		{
			Vector2i tmp = FrameWork::Converter::instance()->fwc_logicCoordToGraphicCoord(Vector2f(i, j));
			tileMatrix[i][j].setGraphicCoordinate(tmp.getX(), tmp.getY());
			tileMatrix[i][j].renderTextureID(blankTextureID);
		}
	}
}

bool Layer::checkBlank(int sq_x, int sq_y)
{
	if (tileMatrix[sq_x][sq_y].getTextureID() == blankTextureID)
		return true;
	
	return false;
}

void Layer::clear()
{
	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			deleteTile(Vector2i(i, j));
		}
	}
}

unsigned int Layer::getTileType(Vector2i sq_position)
{
	unsigned int test = tileMatrix[sq_position.getX()][sq_position.getY()].getTextureID();
	if (48 <= test && test <= 83)
	{
		return TYPE_TERRAIN;
	}

	else if (84 <= test && test <= 125)
	{
		return TYPE_BUILDING_NOT_HOME;
	}

	else if (tileMatrix[sq_position.getX()][sq_position.getY()].getTextureID() >= 126)
	{
		return TYPE_BUILDING_HOME;
	}
	return TYPE_OTHER;
}