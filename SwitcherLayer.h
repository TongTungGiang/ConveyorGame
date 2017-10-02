#ifndef SWITCHER_LAYER_H
#define SWITCHER_LAYER_H

#include "Layer.h"
#include "RoadLayer.h"
#include "BuildingLayer.h"
#include "Switcher.h"

class SwitcherLayer : public Layer
{ 
private:
	RoadLayer* roadLayer;
	BuildingLayer* buildingLayer;
	Switcher switcherInfo[MAP_SQR_X_DIMENSIONS][MAP_SQR_Y_DIMENSIONS];

public:
	SwitcherLayer(unsigned int blankTextureID);
	void setRoadLayerPointer(RoadLayer* roadLayer);
	void setBuildingLayerPointer(BuildingLayer* buildingLayer);
	int modifyTileMatrix(Vector2i sq_Position, unsigned int textureID) { return 0; };
	void updateSwitcherInformation(Vector2i sq_Position);
	void toNextDirection(Vector2i sq_Position);
	void deleteTile(Vector2i sq_Position);
	void render();
	void disableSwitcherDirection(Vector2i sq_Position, int direction);
	void exportToFile(std::wstring filename);
	void importFromFile(std::wstring filename);
};

#endif