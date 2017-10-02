#ifndef BUILDING_LAYER_H
#define BUILDING_LAYER_H

#include "Layer.h"

class BuildingLayer : public Layer
{
private:
	Layer* roadLayer; //link tới road layer
	Layer* switcherLayer; //link tới switcher layer

public:
	BuildingLayer(unsigned int blankTextureID);
	int modifyTileMatrix(Vector2i sq_Position, unsigned int textureID);
	void render();
	void deleteTile(Vector2i sq_Position);
	void setRoadLayerPointer(Layer* roadLayer);
	void setSwitcherLayerPointer(Layer* switcherLayer);

	void updateSwitcherInformation(Vector2i sq_Position) {};
	void disableSwitcherDirection(Vector2i sq_Position, int direction) {};
	void exportToFile(std::wstring filename);
	void importFromFile(std::wstring filename);
};

#endif