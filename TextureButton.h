#ifndef TEXTURE_BUTTON_H
#define TEXTURE_BUTTON_H

#include "FrameWork.h"
#include "Definition.h"

#include <iostream>

struct SubButton
{
	int x_coord, y_coord;
	unsigned int buttonID;
	unsigned int textureID;
	unsigned int state;
};

class TextureButton
{

private:
	unsigned int buttonID;
	unsigned int textureID;
	int x_coord, y_coord;
	int width, height;
	int currentSubButton; // sub button đang được chọn
	unsigned int iterator_sbutton; //số lượng sub button hiện có trong sub button list của button
	unsigned int state;
	std::vector<SubButton*> *subButtonArray; // sub button list của button
	Vector2i SubButtonPosition[MAX_SUB_BUTTON];

public:

	TextureButton(unsigned int buttonID, unsigned int textureID, int x_coord, int y_coord);
	~TextureButton();

	unsigned int getCurrentSubButtonTextureID();

	void setState(unsigned int state);

	unsigned int getState();

	bool checkIntrusion(int x, int y);

	unsigned int getButtonID();

	void getTextureSize(int* xSize, int* ySize);

	void render();

	void createSubButton(unsigned int textureID);

	bool checkSubButtonIntrusion(unsigned int sButtonID, int x, int y);

	unsigned int browSubButtonArray_LeftClick();

	void browSubButtonArray_Point();

	unsigned int getIconTextureID();

	void setActiveSubButton(unsigned int subButtonID);
};

#endif