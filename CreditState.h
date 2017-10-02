#ifndef CREDITSTATE_H
#define CREDITSTATE_H

#include "FrameWork.h"
#include "GameState.h"


class CreditState: public GameState
{
public:

	CreditState() : GameState()
	{
		stateID = CREDIT_STATE;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(CreditState::back), Vector2i(30, 30), Vector2i(250, 50), BACK, BACK_ACTIVE);
	}

	~CreditState()
	{
		
	}

	virtual void update()
	{

	}

	virtual void render()
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(CREDIT_BACKGROUND, 0, 0);
		getCommandButtonManager()->renderButtons();
	}

	bool onExit()
	{	
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(CreditState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(CreditState::moveEvent));
		return true;
	}
	
	fw_Callback back()
	{
		isOnState = false;
		setNextState(MENU_STATE);
	}

	fw_Callback moveEvent()
	{
		getCommandButtonManager()->browseArray_Point();
	}
	fw_Callback handleLeftMouseClick()
	{
		getCommandButtonManager()->browseArray_LeftClick();
	}
};

#endif