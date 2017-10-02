#ifndef TEXTURE_BUTTONMANAGER_H
#define TEXTURE_BUTTONMANAGER_H

#include "TextureButton.h"
#include "FrameWork.h"
#include <vector>

//using namespace FrameWork;

class TextureButtonManager
{
	
private:

	unsigned int iterator_button; // số lượng button có trong button list

	int currentSelectedButton;

	 std::vector <TextureButton*> *buttonArray; // button list

	TextureButtonManager* singleton;

	Vector2i ButtonPosition[MAX_BUTTON];

public:
	TextureButtonManager();
	~TextureButtonManager();

	unsigned int createButton(unsigned int textureID);

	void createSubButton(unsigned int buttonID, unsigned int textureID);

	int browseArray_LeftClick_1();
	int browseArray_LeftClick_2();

	int browseArray_RightClick();

	void browseArray_Point_1();
	void browseArray_Point_2();

	void renderButtons();

	void setActiveButton(unsigned int buttonID, unsigned int subButtonID);

	unsigned int getSelectedButtonIconTextureID();

};

#endif