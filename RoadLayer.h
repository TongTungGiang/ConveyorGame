#ifndef ROAD_LAYER_H
#define ROAD_LAYER_H

#include "Layer.h"
#include "Road.h"


class RoadLayer : public Layer
{
private:
	Layer* buildingLayer;
	Layer* switcherLayer;
	/*
	Road** roadInfo;
	*/
	Road roadInfo[MAP_SQR_X_DIMENSIONS][MAP_SQR_Y_DIMENSIONS];

public:
	RoadLayer(unsigned int blankTextureID);
	int addTileDirection(int x, int y, unsigned int direction, bool isIn);
	void deleteTile(Vector2i sq_Position);
	void deleteTileDirection(Vector2i sq_Position, int direction);
	void render();
	void setBuildingLayerPointer(Layer* buildingLayer);
	void setSwitcherLayerPointer(Layer* switcherLayer);

	int modifyTileMatrix(Vector2i sq_Position, unsigned int textureID) { return 0; };

	void updateRoadState(Vector2i sq_Position);

	void updateSwitcherInformation(Vector2i sq_Position) {};

	void disableSwitcherDirection(Vector2i sq_Position, int direction) {};

	Road getRoadInfo(Vector2i position)
	{
		return roadInfo[position.getX()][position.getY()];
	}
	void exportToFile(std::wstring filename);
	void importFromFile(std::wstring filename);
};

#endif