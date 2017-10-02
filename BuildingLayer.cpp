#include "BuildingLayer.h"

BuildingLayer::BuildingLayer(unsigned int blankTextureID) : Layer(blankTextureID)
{ 

}

int BuildingLayer::modifyTileMatrix(Vector2i sq_Position, unsigned int textureID)
{
	int x = sq_Position.getX(),
		y = sq_Position.getY(),
		tmp = roadLayer->getTextureID(Vector2i(x, y));
	/*	Các trường hợp được phép vẽ nhà tại 1 ô gồm */
	/*	1. building layer trống tại ô đó đồng thời road layer cũng trống tại ô đó (building thông thường) => được phép vẽ building bất kì	*/
	if ( (this->checkBlank(x, y)) && ( roadLayer->checkBlank(x, y)) )
	{
		tileMatrix[x][y].renderTextureID(textureID);
		return 1;
	}
	/*	2. building layer trống tại ô đó đồng thời switcher layer tại ô đó là một ending point hay starting point => được phép vẽ building 
		loại nhà cửa tượng trưng cho sender hay receiver	*/
	if (this->checkBlank(x, y) && switcherLayer->getTextureID(Vector2i(x, y)) == ENDING_POINT ||
		this->checkBlank(x, y) && switcherLayer->getTextureID(Vector2i(x, y)) == STARTING_POINT)
	{
		if (textureID >= 126)
		{
			tileMatrix[x][y].renderTextureID(textureID);
		}
		return 1;
	}
	return 0;
}

void BuildingLayer::deleteTile(Vector2i sq_Position)
{
	int x = sq_Position.getX(),
		y = sq_Position.getY();

	tileMatrix[x][y].renderTextureID(blankTextureID);
}

void BuildingLayer::render()
{
	for (int j = MAP_SQR_Y_DIMENSIONS - 1; j >= 0; j--)
	{
		for (int i = MAP_SQR_X_DIMENSIONS - 1; i >= 0; i--)
		{
			tileMatrix[i][j].render();
		}
	}
}

void BuildingLayer::setRoadLayerPointer(Layer* roadLayer)
{
	this->roadLayer = roadLayer;
}

void BuildingLayer::setSwitcherLayerPointer(Layer* switcherLayer)
{
	this->switcherLayer = switcherLayer;
}

void BuildingLayer::exportToFile(std::wstring filename)
{
	std::wofstream ofs(filename);

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			ofs << tileMatrix[i][j].getTextureID() << " ";
		}
	}

	ofs.close();
}

void BuildingLayer::importFromFile(std::wstring filename)
{
	std::wifstream ifs(filename);

	unsigned int tmp;

	clear();

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			ifs >> tmp;
			tileMatrix[i][j].renderTextureID(tmp);
		}
	}
}