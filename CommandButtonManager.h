#ifndef COMMAND_BUTTON_MANAGER
#define COMMAND_BUTTON_MANAGER

#include "Vector2.h"
#include "CommandButton.h"
#include "FrameWork.h"

//using FrameWork::InputHandler;

class CommandButtonManager
{
private:

	unsigned int iterator_button;

	std::vector <CommandButton*> *buttonArray;

public:
	CommandButtonManager()
	{
		iterator_button = 0;
		buttonArray = new std::vector<CommandButton*>;
	}
	
	~CommandButtonManager()
	{
		for (int i = 0; i < iterator_button; i++)
		{
			delete buttonArray->at(i);
		}

		iterator_button = 0;
	}

	unsigned int createButton(std::function<void()> command, Vector2i coord, Vector2i dimensions,
		unsigned int iconTextureID_nonActive, unsigned int iconTextureID_active)
	{
		CommandButton *temp = new CommandButton(coord, dimensions, command, iconTextureID_nonActive, iconTextureID_active);

		buttonArray->push_back(temp);
		iterator_button++;
		return iterator_button - 1;
	}

	void browseArray_LeftClick()
	{
		if (buttonArray->size() > 0)
		{
			int tx, ty;
			FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);

			for (unsigned int i = 0; i < iterator_button; i++)
			{
				buttonArray->at(i)->setState(NONACTIVE);

				if ( buttonArray->at(i)->checkIntrusion(Vector2i(tx, FrameWork::Window::instance()->fww_getHeight() - ty)) )
				{
					buttonArray->at(i)->setState(ACTIVE);
					buttonArray->at(i)->doCommand();
				}
			}
		}
	}

	void browseArray_Point()
	{
		if (buttonArray->size() > 0)
		{
			int tx, ty;
			FrameWork::InputHandler::instance()->fwi_getMousePosition(&tx, &ty);
			for (unsigned int i = 0; i < iterator_button; i++)
			{
				if (buttonArray->at(i)->getState() == HOVER)
				{
					buttonArray->at(i)->setState(NONACTIVE);
				}
				if (buttonArray->at(i)->checkIntrusion(Vector2i(tx, FrameWork::Window::instance()->fww_getHeight() - ty)))
				{
					if (buttonArray->at(i)->getState() != ACTIVE)
					{
						buttonArray->at(i)->setState(HOVER);
					}
				}
			}
		}
	}

	void renderButtons()
	{
		for (unsigned int i = 0; i < iterator_button; i++)
		{
			buttonArray->at(i)->render();
		}
	}

	void setActiveButton(unsigned int buttonID)
	{
		for (int i = 0; i < iterator_button; i++)
		{
			buttonArray->at(i)->setState(NONACTIVE);
		}
		buttonArray->at(buttonID)->setState(ACTIVE);
	}
	void setNonActiveButton(unsigned int buttonID)
	{
		buttonArray->at(buttonID)->setState(NONACTIVE);
	}

	Vector2i getButtonOriginCoordinates(unsigned int buttonID)
	{
		return buttonArray->at(buttonID)->getOriginCoordinates();
	}
};

#endif