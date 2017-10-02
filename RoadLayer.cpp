#include "RoadLayer.h"

RoadLayer::RoadLayer(unsigned int blankTextureID) 
	: Layer(blankTextureID)
{
	sDirection tmp;
	tmp.isEnable = false;
	tmp.isIn = true;
	
	/*
	roadInfo = new Road*[MAP_SQR_X_DIMENSIONS];
	*/
	for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
	{
		/*
		roadInfo[i] = new Road[MAP_SQR_Y_DIMENSIONS];
		*/
		for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
		{
			roadInfo[i][j].set_in_number(0);
			roadInfo[i][j].set_out_number(0);

			roadInfo[i][j].setStructDirection(NORTH, tmp);
			roadInfo[i][j].setStructDirection(WEST, tmp);
			roadInfo[i][j].setStructDirection(SOUTH, tmp);
			roadInfo[i][j].setStructDirection(EAST, tmp);
		}
	}
}

void RoadLayer::setBuildingLayerPointer(Layer* buildingLayer)
{
	this->buildingLayer = buildingLayer;
}

void RoadLayer::setSwitcherLayerPointer(Layer* switcherLayer)
{
	this->switcherLayer = switcherLayer;
}

int RoadLayer::addTileDirection(int x, int y, unsigned int direction, bool isIn)
{
	if (buildingLayer->checkBlank(x, y) == false)
	{
		buildingLayer->deleteTile(Vector2i(x, y));
	}

	sDirection tmp;

	tmp = roadInfo[x][y].getStructDirection(direction);
	if (tmp.isEnable == false)
	{
		tmp.isEnable = true;
		tmp.isIn = isIn;
		roadInfo[x][y].setStructDirection(direction, tmp);

		if (isIn)
		{
			int tmp_num = roadInfo[x][y].get_in_number();
			roadInfo[x][y].set_in_number(tmp_num + 1);
		}

		else
		{
			int tmp_num = roadInfo[x][y].get_out_number();
			roadInfo[x][y].set_out_number(tmp_num + 1);
		}
		updateRoadState(Vector2i(x, y));
		switcherLayer->updateSwitcherInformation(Vector2i(x, y));
	}
	return 1;
}

void RoadLayer::deleteTileDirection(Vector2i sq_Position, int direction)
{
	int x, y;
	x = sq_Position.getX();
	y = sq_Position.getY();

	sDirection tmp = roadInfo[x][y].getStructDirection(direction);

	if (tmp.isEnable = false)
	{
		return;
	}

	tmp.isEnable = false;

	roadInfo[x][y].setStructDirection(direction, tmp);

	if (tmp.isIn == true)
	{
		int tmp_num = roadInfo[x][y].get_in_number();
		roadInfo[x][y].set_in_number(tmp_num - 1);
	}
	else
	{
		int tmp_num = roadInfo[x][y].get_out_number();
		roadInfo[x][y].set_out_number(tmp_num - 1);
	}

	updateRoadState(Vector2i(x, y));
	switcherLayer->disableSwitcherDirection(sq_Position, direction);
}

void RoadLayer::deleteTile(Vector2i sq_Position)
{
	int x, y;
	x = sq_Position.getX();
	y = sq_Position.getY();

	for (int i = 0; i < 4; i++)
	{
		sDirection tmp = roadInfo[x][y].getStructDirection(i);
		if (tmp.isEnable == true) // nếu 1 trong 4 hướng xung quanh ô đường đi bị xóa cũng là ô đường thì cần thay đổi các giá trị của ô đó
		{
			switch (i)
			{
			case NORTH: 
				deleteTileDirection(Vector2i(x + 1, y), SOUTH);
				break; 

			case WEST:
				deleteTileDirection(Vector2i(x, y + 1), EAST);
				break;

			case SOUTH:
				deleteTileDirection(Vector2i(x - 1, y), NORTH);
				break;

			case EAST:
				deleteTileDirection(Vector2i(x, y - 1), WEST);
				break;
			}

			deleteTileDirection(Vector2i(x, y), i);
		}
	}

	switcherLayer->deleteTile(sq_Position);
}

void RoadLayer::updateRoadState(Vector2i sq_Position)
{
	int x, y;
	x = sq_Position.getX();
	y = sq_Position.getY();

	sDirection tmp = roadInfo[x][y].getStructDirection(NORTH);
	bool north_enable = tmp.isEnable;
	tmp = roadInfo[x][y].getStructDirection(WEST);
	bool west_enable = tmp.isEnable;
	tmp = roadInfo[x][y].getStructDirection(SOUTH);
	bool south_enable = tmp.isEnable;
	tmp = roadInfo[x][y].getStructDirection(EAST);
	bool east_enable = tmp.isEnable;

	bool caseNorth = (north_enable == true);
	bool caseWest = (west_enable == true);
	bool caseSouth = (south_enable == true);
	bool caseEast = (east_enable == true);

	if (caseNorth && caseWest && caseSouth && caseEast)//1
	{
		tileMatrix[x][y].renderTextureID(ROAD_CROSSROAD);
	}

	else if (caseNorth && caseWest && caseSouth && !caseEast)//2
	{
		tileMatrix[x][y].renderTextureID(ROAD_T_EAST);
	}
	else if (caseNorth && caseWest && !caseSouth && caseEast)//3
	{
		tileMatrix[x][y].renderTextureID(ROAD_T_SOUTH);
	}
	else if (caseNorth && !caseWest && caseSouth && caseEast)//4
	{
		tileMatrix[x][y].renderTextureID(ROAD_T_WEST);
	}
	else if (!caseNorth && caseWest && caseSouth && caseEast)//5
	{
		tileMatrix[x][y].renderTextureID(ROAD_T_NORTH);
	}

	else if (caseNorth && caseWest && !caseSouth && !caseEast)//6
	{
		tileMatrix[x][y].renderTextureID(ROAD_CORNER_ES);
	}
	else if (caseNorth && !caseWest && caseSouth && !caseEast)//7
	{
		tileMatrix[x][y].renderTextureID(ROAD_VERTICAL);
	}
	else if (!caseNorth && caseWest && caseSouth && !caseEast)//8
	{
		tileMatrix[x][y].renderTextureID(ROAD_CORNER_NE);
	}
	else if (caseNorth && !caseWest && !caseSouth && caseEast)//9
	{
		tileMatrix[x][y].renderTextureID(ROAD_CORNER_WS);
	}
	else if (!caseNorth && caseWest && !caseSouth && caseEast)//10
	{
		tileMatrix[x][y].renderTextureID(ROAD_HORIZONTAL);
	}
	else if (!caseNorth && !caseWest && caseSouth && caseEast)//11
	{
		tileMatrix[x][y].renderTextureID(ROAD_CORNER_NW);
	}

	if (caseNorth && !caseWest && !caseSouth && !caseEast)//12
	{
		tileMatrix[x][y].renderTextureID(ROAD_END_SOUTH);
	}
	if (!caseNorth && caseWest && !caseSouth && !caseEast)//13
	{
		tileMatrix[x][y].renderTextureID(ROAD_END_EAST);
	}
	if (!caseNorth && !caseWest && caseSouth && !caseEast)//14
	{
		tileMatrix[x][y].renderTextureID(ROAD_END_NORTH);
	}
	if (!caseNorth && !caseWest && !caseSouth && caseEast)//15
	{
		tileMatrix[x][y].renderTextureID(ROAD_END_WEST);
	}
	if (!caseNorth && !caseWest && !caseSouth && !caseEast)//16
	{
		tileMatrix[x][y].renderTextureID(blankTextureID);
	}
}

void RoadLayer::render()
{
	for (int i = MAP_SQR_X_DIMENSIONS - 1; i >= 0; i--)
	{
		for (int j = MAP_SQR_Y_DIMENSIONS - 1; j >= 0; j--)
		{
			tileMatrix[i][j].render();
		}
	}
}

void RoadLayer::exportToFile(std::wstring filename)
{
	std::wofstream ofs(filename);

	sDirection tmp;

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			ofs << roadInfo[i][j].get_in_number() << " ";
			ofs << roadInfo[i][j].get_out_number() << " ";

			tmp = roadInfo[i][j].getStructDirection(NORTH);
			ofs << tmp.isEnable << " " << tmp.isIn << " ";

			tmp = roadInfo[i][j].getStructDirection(WEST);
			ofs << tmp.isEnable << " " << tmp.isIn << " ";

			tmp = roadInfo[i][j].getStructDirection(SOUTH);
			ofs << tmp.isEnable << " " << tmp.isIn << " ";

			tmp = roadInfo[i][j].getStructDirection(EAST);
			ofs << tmp.isEnable << " " << tmp.isIn << " ";

			ofs << tileMatrix[i][j].getTextureID();

			ofs << std::endl;
		}
	}

	ofs.close();
}

void RoadLayer::importFromFile(std::wstring filename)
{
	std::wifstream ifs(filename);

	unsigned int tmp;

	clear();

	sDirection temp;

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			ifs >> tmp;
			roadInfo[i][j].set_in_number(tmp);
			ifs >> tmp;
			roadInfo[i][j].set_out_number(tmp);

			ifs >> tmp;
			temp.isEnable = tmp;
			ifs >> tmp;
			temp.isIn = tmp;
			roadInfo[i][j].setStructDirection(NORTH, temp);

			ifs >> tmp;
			temp.isEnable = tmp;
			ifs >> tmp;
			temp.isIn = tmp;
			roadInfo[i][j].setStructDirection(WEST, temp);

			ifs >> tmp;
			temp.isEnable = tmp;
			ifs >> tmp;
			temp.isIn = tmp;
			roadInfo[i][j].setStructDirection(SOUTH, temp);

			ifs >> tmp;
			temp.isEnable = tmp;
			ifs >> tmp;
			temp.isIn = tmp;
			roadInfo[i][j].setStructDirection(EAST, temp);

			ifs >> tmp;
			tileMatrix[i][j].renderTextureID(tmp);
		}
	}
}