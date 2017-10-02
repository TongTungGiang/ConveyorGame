#ifndef LAYER_H
#define LAYER_H



#include "FrameWork.h"
#include "GraphicObject.h"
#include "Vector2.h"
#include "Definition.h"
#include <fstream>

class Layer
{
protected:
	unsigned int blankTextureID; //ID của texture được thiết lập làm texture rỗng trên layer này
	/*
	GraphicObject** tileMatrix; //ma trận tile của layer
	*/
	GraphicObject tileMatrix[MAP_SQR_X_DIMENSIONS][MAP_SQR_Y_DIMENSIONS];
public:
	Layer() {};
	Layer(unsigned int blankTextureID);
	bool checkBlank(int sq_x, int sq_y);
	virtual void exportToFile(std::wstring filename) = 0;
	virtual void importFromFile(std::wstring filename) = 0;
	virtual int modifyTileMatrix(Vector2i sq_Position, unsigned int textureID) = 0;
	virtual void updateSwitcherInformation(Vector2i sq_Position) = 0;
	virtual void deleteTile(Vector2i sq_Position) = 0;
	virtual void render() = 0;
	virtual void disableSwitcherDirection(Vector2i sq_Position, int direction) = 0;
	void clear();
	unsigned int getTextureID(Vector2i sq_position)
	{
		return tileMatrix[sq_position.getX()][sq_position.getY()].getTextureID();
	}
	unsigned int getTileType(Vector2i sq_position);
};

#endif