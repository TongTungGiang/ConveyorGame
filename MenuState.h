#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "FrameWork.h"
#include "GameState.h"

class MenuState : public GameState
{


public:
	bool onEnter();
	bool onExit();
	MenuState();
	~MenuState();

	virtual void update();
	virtual void render();

	fw_Callback menuToPlay();
	fw_Callback menuToQuit();
	fw_Callback menuToMapGenerator();
	fw_Callback menuToInstruction();
	fw_Callback menuToCredit();
	
	fw_Callback moveEvent();
	fw_Callback handleLeftMouseClick();
};



#endif




