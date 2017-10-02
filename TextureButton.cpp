#include "TextureButton.h"

TextureButton::TextureButton(unsigned int buttonID, unsigned int textureID, int x_coord, int y_coord) :
buttonID(buttonID), textureID(textureID), x_coord(x_coord), y_coord(y_coord)
{
	subButtonArray = new std::vector<SubButton*>;
	width = BUTTON_WIDTH;
	height = BUTTON_HEIGHT;
	state = NONACTIVE;
	currentSubButton = 0;
	iterator_sbutton = 0;

	SubButtonPosition[0] = { 1146, 10 };
	SubButtonPosition[1] = { 1256, 10 };
	SubButtonPosition[2] = { 1146, 120 };
	SubButtonPosition[3] = { 1256, 120 };
	SubButtonPosition[4] = { 1146, 230 };
	SubButtonPosition[5] = { 1256, 230 };
	SubButtonPosition[6] = { 1146, 340 };
	SubButtonPosition[7] = { 1256, 340 };
	SubButtonPosition[8] = { 1146, 450 };
	SubButtonPosition[9] = { 1256, 450 };
	SubButtonPosition[10] = { 1146, 560 };
	SubButtonPosition[11] = { 1256, 560 };
	SubButtonPosition[12] = { 1146, 670 };
	SubButtonPosition[13] = { 1256, 670 };
}

TextureButton::~TextureButton()
{
	for (int i = 0; i < iterator_sbutton; i++)
	{
		delete subButtonArray->at(i);
	}
	delete subButtonArray;
}

void TextureButton::render()
{
	if (state == NONACTIVE)
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_NONACTIVE, x_coord, y_coord);

	}
	else if (state == ACTIVE)
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_ACTIVE, x_coord, y_coord);
		for (unsigned int i = 0; i < iterator_sbutton; i++)
		{
			if (subButtonArray->at(i)->state == NONACTIVE)
			{
				FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_NONACTIVE, subButtonArray->at(i)->x_coord, subButtonArray->at(i)->y_coord);
			}
			else if (subButtonArray->at(i)->state == ACTIVE)
			{
				FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_ACTIVE, subButtonArray->at(i)->x_coord, subButtonArray->at(i)->y_coord);

			}
			else if (subButtonArray->at(i)->state == HOVER)
			{
				FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_HOVERED, subButtonArray->at(i)->x_coord, subButtonArray->at(i)->y_coord);
			}
			
			FrameWork::TextureManager::instance()->fwtm_renderTexture(subButtonArray->at(i)->textureID, subButtonArray->at(i)->x_coord + 9, 
				subButtonArray->at(i)->y_coord + 25);
		}
	}
	else if (state == HOVER)
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(BUTTON_HOVERED, x_coord, y_coord);
	}

	FrameWork::TextureManager::instance()->fwtm_renderTexture(textureID, x_coord + 9, y_coord + 25);
}

unsigned int TextureButton::getCurrentSubButtonTextureID()
{
	return textureID;
}

void TextureButton::setState(unsigned int state)
{
	this->state = state;
}

unsigned int TextureButton::getState()
{
	return state;
}

bool TextureButton::checkIntrusion(int x, int y)
{
	int bx = x_coord, by = y_coord;
	return (bx <= x && x <= bx + width
		&&	by <= y && y <= by + height);
}

unsigned int TextureButton::getButtonID()
{
	return buttonID;
}

void TextureButton::createSubButton(unsigned int textureID)
{
	if (iterator_sbutton < MAX_SUB_BUTTON)
	{
		SubButton* newSubButton = new SubButton;
		newSubButton->buttonID = iterator_sbutton;
		newSubButton->x_coord = SubButtonPosition[iterator_sbutton].getX();
		newSubButton->y_coord = SubButtonPosition[iterator_sbutton].getY();
		newSubButton->textureID = textureID;
		newSubButton->state = NONACTIVE;

		subButtonArray->push_back(newSubButton);

		if (iterator_sbutton == 0)
		{
			subButtonArray->at(0)->state = ACTIVE;
			currentSubButton = 0;
			this->textureID = subButtonArray->at(0)->textureID;
		}

		iterator_sbutton++;
	}
}

bool TextureButton::checkSubButtonIntrusion(unsigned int sButtonID, int x, int y)
{
	int bx = subButtonArray->at(sButtonID)->x_coord, 
		by = subButtonArray->at(sButtonID)->y_coord;
	return (bx <= x && x <= bx + width
		&&	by <= y && y <= by + height);
}

unsigned int TextureButton::browSubButtonArray_LeftClick()
{ 
	int tx, ty;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);
	ty = FrameWork::Window::instance()->fww_getHeight() - ty;

	for (unsigned int i = 0; i < iterator_sbutton; i++)
	{
		if (checkSubButtonIntrusion(i, tx, ty))
		{
			subButtonArray->at(currentSubButton)->state = NONACTIVE;
			subButtonArray->at(i)->state = ACTIVE;
			currentSubButton = i;
			textureID = subButtonArray->at(i)->textureID;
			return subButtonArray->at(currentSubButton)->textureID;
		}
	}

	return -1;
}

void TextureButton::browSubButtonArray_Point()
{ 
	int tx, ty;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);
	ty = FrameWork::Window::instance()->fww_getHeight() - ty;
	for (unsigned int i = 0; i < iterator_sbutton; i++)
	{
		if (checkSubButtonIntrusion(i, tx, ty))
		{
			if (subButtonArray->at(i)->state != ACTIVE)
			{
				subButtonArray->at(i)->state = HOVER;
			}
		}
		else
		{
			if (subButtonArray->at(i)->state != ACTIVE)
			{
				subButtonArray->at(i)->state = NONACTIVE;
			}
		}
	}
}

unsigned int TextureButton::getIconTextureID()
{
	return textureID;
}

void TextureButton::setActiveSubButton(unsigned int subButtonID)
{
	subButtonArray->at(currentSubButton)->state = NONACTIVE;

	subButtonArray->at(subButtonID)->state = ACTIVE;

	currentSubButton = subButtonID;
}