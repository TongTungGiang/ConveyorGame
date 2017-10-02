#ifndef GRAPHIC_OBJECT
#define GRAPHIC_OBJECT

#include "Vector2.h"
#include "FrameWork.h"

#define SQUARE_WIDTH 82
#define SQUARE_HEIGHT 40

class GraphicObject
{

protected:

	Vector2i graphicCoordinate;
	unsigned int textureID;
	//int xOffset;
	//int yOffset;

public:

	GraphicObject() {}

	GraphicObject(Vector2i _gCoord, unsigned int textureID) : graphicCoordinate(_gCoord), textureID(textureID)
	{
	}

	void setGraphicCoordinate(int x, int y)
	{
		graphicCoordinate(x, y);
	}

	void setGraphicCoordinate(Vector2i gCoord)
	{
		graphicCoordinate = gCoord;
	}

	void renderTextureID(unsigned int textureID)
	{
		this->textureID = textureID;
	}

	unsigned int getTextureID()
	{
		return textureID;
	}

	int getGraphicX()
	{
		return graphicCoordinate.getX();
	}

	int getGraphicY()
	{
		return graphicCoordinate.getY();
	}

	void render(int xOffset = 0, int yOffset = 0)
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(textureID, graphicCoordinate.getX() + xOffset, graphicCoordinate.getY() + yOffset);
	}

	void convertLogicalToGraphical(float x, float y)
	{
		graphicCoordinate((int)((x - y) * SQUARE_WIDTH / 2), (int)((x + y) * SQUARE_HEIGHT / 2));
	}

	void operator () (const Vector2i &gCoord, const unsigned int &textureID)
	{
		this->graphicCoordinate = gCoord;
		this->textureID = textureID;
	}
};

#endif