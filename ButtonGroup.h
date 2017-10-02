#ifndef BUTTON_GROUP
#define BUTTON_GROUP

#include <vector>
#include "Button.h"
#include "ButtonManager.h"

class ButtonGroup
{
private:
	unsigned int groupID;
	int iterator;
	int currentButton;
	std::vector<unsigned int>* buttonArray;

public:
	ButtonGroup();
	void addButton(unsigned int buttonID);
	int getCurrentButton();
	int getNextButton();
};

#endif