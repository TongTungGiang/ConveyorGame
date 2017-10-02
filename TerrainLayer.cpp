#include "TerrainLayer.h"

TerrainLayer::TerrainLayer(unsigned int blankTextureID) : Layer(blankTextureID)
{

}

int TerrainLayer::modifyTileMatrix(Vector2i sq_Position, unsigned int textureID)
{
	int x = sq_Position.getX(),
		y = sq_Position.getY();
	tileMatrix[x][y].renderTextureID(textureID);

	return 1;
}

void TerrainLayer::deleteTile(Vector2i sq_Position)
{
	int x = sq_Position.getX(),
		y = sq_Position.getY();

	tileMatrix[x][y].renderTextureID(blankTextureID);
}

void TerrainLayer::render()
{
	for (int i = MAP_SQR_Y_DIMENSIONS - 1; i >= 0; i--)
	{
		for (int j = MAP_SQR_X_DIMENSIONS - 1; j >= 0; j--)
		{
			tileMatrix[i][j].render();
		}
	}
}

void TerrainLayer::exportToFile(std::wstring filename)
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

void TerrainLayer::importFromFile(std::wstring filename)
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