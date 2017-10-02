#include "TextureButtonManager.h"


TextureButtonManager::TextureButtonManager()
{
	currentSelectedButton = 0;
	iterator_button = 0;
	buttonArray = new std::vector<TextureButton*>;

	ButtonPosition[0] = { 10, 10 };
	ButtonPosition[1] = { 120, 10 };
	ButtonPosition[2] = { 10, 120 };
	ButtonPosition[3] = { 120, 120 };
	ButtonPosition[4] = { 10, 230 };
	ButtonPosition[5] = { 120, 230 };
	ButtonPosition[6] = { 10, 340 };
	ButtonPosition[7] = { 120, 340 };
	ButtonPosition[8] = { 10, 450 };
	ButtonPosition[9] = { 120, 450 };
}

TextureButtonManager::~TextureButtonManager()
{
	for (std::vector<TextureButton*>::iterator _interator = buttonArray->begin(); _interator != buttonArray->end(); _interator++)
	{
		delete *_interator;
	}
	delete buttonArray;
}

unsigned int TextureButtonManager::createButton(unsigned int textureID)
{
	if (iterator_button < MAX_BUTTON)
	{
		TextureButton *temp = new TextureButton(iterator_button, textureID, ButtonPosition[iterator_button].getX(), ButtonPosition[iterator_button].getY());

		buttonArray->push_back(temp);
		iterator_button++;
		return iterator_button - 1;
	}
	return -1;
}

void TextureButtonManager::createSubButton(unsigned int buttonID, unsigned int textureID)
{
	buttonArray->at(buttonID)->createSubButton(textureID);
}

int TextureButtonManager::browseArray_LeftClick_1()
{
	if (buttonArray->size() > 0)
	{
		int tx, ty;
		FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);

		//for (std::vector<TextureButton*>::iterator _iterator = buttonArray->begin(); _iterator != buttonArray->end(); _iterator++)
		for (int i = 0; i < iterator_button; i++)
		{
			if (buttonArray->at(i)->checkIntrusion(tx, FrameWork::Window::instance()->fww_getHeight() - ty))
			{
				buttonArray->at(currentSelectedButton)->setState(NONACTIVE);
				buttonArray->at(i)->setState(ACTIVE);
				currentSelectedButton = i;
				return buttonArray->at(i)->getCurrentSubButtonTextureID();
			}
		}
	}
	return -1;
}

int TextureButtonManager::browseArray_LeftClick_2()
{
	if (currentSelectedButton >= 0)
	{
		return (buttonArray->at(currentSelectedButton)->browSubButtonArray_LeftClick());
	}
	return -1;
}

int TextureButtonManager::browseArray_RightClick()
{
	return -1;
}

void TextureButtonManager::browseArray_Point_1()
{
	if (buttonArray->size() > 0)
	{
		int tx, ty;
		FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);
		for (std::vector<TextureButton*>::iterator _iterator = buttonArray->begin(); _iterator != buttonArray->end(); _iterator++)
		{
			if ((*_iterator)->checkIntrusion(tx, FrameWork::Window::instance()->fww_getHeight() - ty))
			{
				if ((*_iterator)->getState() != ACTIVE)
				{
					(*_iterator)->setState(HOVER);
				}
			}
			else
			{
				if ((*_iterator)->getState() != ACTIVE)
				{
					(*_iterator)->setState(NONACTIVE);
				}
			}
		}
	}
}

void TextureButtonManager::browseArray_Point_2()
{
	if (currentSelectedButton >= 0)
	{
		buttonArray->at(currentSelectedButton)->browSubButtonArray_Point();
	}
}

void TextureButtonManager::renderButtons()
{ 
	for (std::vector<TextureButton*>::iterator _iterator = buttonArray->begin(); _iterator != buttonArray->end(); _iterator++)
	{
		(*_iterator)->render();
	}

}

unsigned int TextureButtonManager::getSelectedButtonIconTextureID()
{
	return buttonArray->at(currentSelectedButton)->getIconTextureID();
}

void TextureButtonManager::setActiveButton(unsigned int buttonID, unsigned int subButtonID)
{
	buttonArray->at(currentSelectedButton)->setState(NONACTIVE);

	buttonArray->at(buttonID)->setState(ACTIVE);

	buttonArray->at(buttonID)->setActiveSubButton(subButtonID);

	currentSelectedButton = buttonID;
}