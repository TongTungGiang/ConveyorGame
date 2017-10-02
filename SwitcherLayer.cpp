#include "SwitcherLayer.h"

SwitcherLayer::SwitcherLayer(unsigned int blankTextureID) : Layer(blankTextureID)
{
	/*
	switcherInfo = new Switcher*[MAP_SQR_X_DIMENSIONS];
	*/
	for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
	{
		/*
		switcherInfo[i] = new Switcher[MAP_SQR_Y_DIMENSIONS];
		*/
		for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
		{
			switcherInfo[i][j].setPossibleDirections(false, false, false, false);
		}
	}
}

void SwitcherLayer::updateSwitcherInformation(Vector2i sq_Position)
{
	Road tmp = roadLayer->getRoadInfo(sq_Position);
	int sq_x_pos = sq_Position.getX(),
		sq_y_pos = sq_Position.getY();

	for (int i = 0; i < 4; i++)
	{
		sDirection _tmp = tmp.getStructDirection(i);
		if (_tmp.isEnable && _tmp.isIn == false)
		{
			switcherInfo[sq_x_pos][sq_y_pos].setPossibleDirections(i, true);
		}
	}

	if (tmp.get_out_number() == 0) //trường hợp ô không có lối ra -> ô là endpoint hoặc ko đc hiển thị
	{
		if (tmp.get_in_number() == 0)
		{
			tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(blankTextureID);
		}
		else
		{
			tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(ENDING_POINT);
		}
	}
	else if (tmp.get_out_number() == 1) //trường hợp ô chỉ có 1 lối ra 
	{
		if (tmp.get_in_number() == 0) // ô chỉ có 1 lối ra và không có lối vào -> ô là starting point
		{
			tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(STARTING_POINT);
		}
		else // các trường hợp ô chỉ có 1 lối ra và có lối vào -> ô là switcher
		{
			for (int i = 0; i < 4; i++)
			{
				sDirection _tmp = tmp.getStructDirection(i);
				if (_tmp.isEnable == true && _tmp.isIn == false) // nếu hướng i có một lối ra nào đó, set hướng Switcher theo hướng i
				{
					//gán textureID cho ô tùy theo hướng ra của ô
					switch (i)
					{
					case 0:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(ARROW_NORTH);
						break;
					case 1:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(ARROW_WEST);
						break;
					case 2:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(ARROW_SOUTH);
						break;
					case 3:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(ARROW_EAST);
						break;
					}
					switcherInfo[sq_x_pos][sq_y_pos].setDir(i);
					break;
				}
			}
		}
	}
	else  // trường hợp có 2 hoặc 3 hoặc 4 lối ra
	{
		if (tmp.get_in_number() == 0) // ô có nhiều hơn 1 lối ra nhưng không có lối vào thì ô đó bị lỗi
		{
			tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(STARTING_POINT_ERROR);
		}
		else // các trường hợp còn lại gồm: 1 vào + 2 ra, 1 vào + 3 ra, 2 vào + 2 ra -> ô là switcher
		{
			sDirection _tmp;
			for (int i = 0; i < 4; i++)
			{
				_tmp = tmp.getStructDirection(i);
				if (_tmp.isEnable == true && _tmp.isIn == false) // nếu hướng i là một lối ra, thêm nó vào hướng khả chuyển cho switcher
				{
					switch (i)
					{
					case 0:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(SWITCHER_NORTH);
						break;
					case 1:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(SWITCHER_WEST);
						break;
					case 2:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(SWITCHER_SOUTH);
						break;
					case 3:
						tileMatrix[sq_x_pos][sq_y_pos].renderTextureID(SWITCHER_EAST);
						break;
					}
					switcherInfo[sq_x_pos][sq_y_pos].setDir(i);
				}
			}
		}
	}
}

void SwitcherLayer::setRoadLayerPointer(RoadLayer* roadLayer)
{
	this->roadLayer = roadLayer;
}

void SwitcherLayer::setBuildingLayerPointer(BuildingLayer* buildingLayer)
{
	this->buildingLayer = buildingLayer;
}

void SwitcherLayer::render()
{
	for (int j = MAP_SQR_Y_DIMENSIONS - 1; j >= 0; j--)
	{
		for (int i = MAP_SQR_X_DIMENSIONS - 1; i >= 0; i--)
		{
			tileMatrix[i][j].render();
		}
	}
}

void SwitcherLayer::toNextDirection(Vector2i sq_Position)
{
	int x = sq_Position.getX(),
		y = sq_Position.getY();

	int temp = getTextureID(Vector2i(x, y));

	if (temp == STARTING_POINT || temp == STARTING_POINT_ERROR || temp == ENDING_POINT ||
		switcherInfo[x][y].getPossibleDirectionNumber() == 1)
	{
		return;
	}

	int tmp = switcherInfo[sq_Position.getX()][sq_Position.getY()].changeToNextPossibleDirection();

	switch (tmp)
	{
	case NORTH:
		tileMatrix[x][y].renderTextureID(SWITCHER_NORTH);
		break;
	case WEST:
		tileMatrix[x][y].renderTextureID(SWITCHER_WEST);
		break;
	case SOUTH:
		tileMatrix[x][y].renderTextureID(SWITCHER_SOUTH);
		break;
	case EAST:
		tileMatrix[x][y].renderTextureID(SWITCHER_EAST);
		break;
	}
}

void SwitcherLayer::deleteTile(Vector2i sq_Position)
{
	int x, y;
	x = sq_Position.getX();
	y = sq_Position.getY();
	for (int i = 0; i < 4; i++)
	{
		switcherInfo[x][y].setPossibleDirections(i, false);
	}
	updateSwitcherInformation(sq_Position);
}

void SwitcherLayer::disableSwitcherDirection(Vector2i sq_Position, int direction)
{
	switcherInfo[sq_Position.getX()][sq_Position.getY()].setPossibleDirections(direction, false);
	updateSwitcherInformation(sq_Position);
}
void SwitcherLayer::exportToFile(std::wstring filename)
{
	std::wofstream ofs(filename);

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			/*	Ghi trường square type	*/
			if (tileMatrix[i][j].getTextureID() == STARTING_POINT)
			{
				ofs << TYPE_SENDER << " ";
			}
			else if (tileMatrix[i][j].getTextureID() == STARTING_POINT_ERROR)
			{
				ofs << TYPE_SENDER_ERROR << " ";
			}
			else if (tileMatrix[i][j].getTextureID() == ENDING_POINT)
			{
				ofs << TYPE_RECEIVER << " ";
			}
			else if (tileMatrix[i][j].getTextureID() != blankTextureID)
			{
				ofs << TYPE_SWITCHER << " ";
			}
			else
			{
				ofs << TYPE_OTHER << " ";
			}

			/*	Toạ độ logic của square	*/
			ofs << i << " " << j << " ";

			/*	Ghi các trường north, west, south, east (nếu square không có switcher hay starting point thì ko cần quan tâm)	*/
			int tmpN, tmpW, tmpS, tmpE;
			switcherInfo[i][j].getPossibleDirection(&tmpN, &tmpW, &tmpS, &tmpE);
			ofs << tmpN << " " << tmpW << " " << tmpS << " " << tmpE << " ";

			/*	Ghi textureID của ending point	(nếu square không phải ending point thì ko cần quan tâm) */
			unsigned int temp = buildingLayer->getTextureID(Vector2i(i, j));
			ofs << temp << " ";

			/*	Ghi hướng hiện tại của mũi tên (nếu square là switcher nhiều hướng thì cần quan tâm trường này)	*/
			int tmp = switcherInfo[i][j].getDir();
			ofs << tmp << " ";

			ofs << std::endl;
		}
	}
	ofs.close();
}

void SwitcherLayer::importFromFile(std::wstring filename)
{
	std::wifstream ifs(filename);

	clear();

	int tmpN, tmpW, tmpS, tmpE, temp, type;

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			/*	Doc truong square type	(de ve starting point va ending point) */
			ifs >> type;
			switch (type)
			{
			case TYPE_SENDER:
				tileMatrix[i][j].renderTextureID(STARTING_POINT);
				break;

			case TYPE_SENDER_ERROR:
				tileMatrix[i][j].renderTextureID(STARTING_POINT_ERROR);
				break;

			case TYPE_RECEIVER:
				tileMatrix[i][j].renderTextureID(ENDING_POINT);
				break;
			}

			/* bo qua cac truong i, j	*/
			ifs >> temp >> temp;

			/*	Doc cac truong north, west, south, east	*/
			ifs >> tmpN >> tmpW >> tmpS >> tmpE;
			switcherInfo[i][j].setPossibleDirections(tmpN, tmpW, tmpS, tmpE);

			/*	Bo qua truong textureID	*/
			ifs >> temp;

			/*	Doc huong hien tai cua mui ten, ve mui ten tuong ung	*/
			ifs >> temp;

			if (roadLayer->checkBlank(i, j) || type != TYPE_SWITCHER)
			{
				continue;
			}

			switcherInfo[i][j].setDir(temp);

			switch (temp)
			{
			case NORTH:
				if (switcherInfo[i][j].getPossibleDirectionNumber() == 1)
				{
					tileMatrix[i][j].renderTextureID(ARROW_NORTH);
				}
				else if (switcherInfo[i][j].getPossibleDirectionNumber() > 1)
				{
					tileMatrix[i][j].renderTextureID(SWITCHER_NORTH);
				}
				break;

			case WEST:
				if (switcherInfo[i][j].getPossibleDirectionNumber() == 1)
				{
					tileMatrix[i][j].renderTextureID(ARROW_WEST);
				}
				else if (switcherInfo[i][j].getPossibleDirectionNumber() > 1)
				{
					tileMatrix[i][j].renderTextureID(SWITCHER_WEST);
				}
				break;

			case SOUTH:
				if (switcherInfo[i][j].getPossibleDirectionNumber() == 1)
				{
					tileMatrix[i][j].renderTextureID(ARROW_SOUTH);
				}
				else if (switcherInfo[i][j].getPossibleDirectionNumber() > 1)
				{
					tileMatrix[i][j].renderTextureID(SWITCHER_SOUTH);
				}
				break;

			case EAST:
				if (switcherInfo[i][j].getPossibleDirectionNumber() == 1)
				{
					tileMatrix[i][j].renderTextureID(ARROW_EAST);
				}
				else if (switcherInfo[i][j].getPossibleDirectionNumber() > 1)
				{
					tileMatrix[i][j].renderTextureID(SWITCHER_EAST);
				}
				break;
			}
		}
	}

	ifs.close();
}

