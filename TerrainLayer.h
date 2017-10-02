#ifndef TERRAIN_LAYER_H
#define TERRAIN_LAYER_H

#include "Layer.h"

class TerrainLayer : public Layer
{
public:



	TerrainLayer(unsigned int blankTextureID);

	void updateSwitcherInformation(Vector2i sq_Position) {};

	void disableSwitcherDirection(Vector2i sq_Position, int direction) {};

	int modifyTileMatrix(Vector2i sq_Position, unsigned int textureID);

	void deleteTile(Vector2i sq_Position);

	void render();

	void exportToFile(std::wstring filename);
	void importFromFile(std::wstring filename);
};

#endif