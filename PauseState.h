#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "FrameWork.h"
#include "GameState.h"
#include "GameStateManager.h"

class PauseState : public GameState
{
private:
	//const int PauseStateID = CREDIT_STATE;
	int msPerUpdate = MS_PER_UPDATE;
public:

	PauseState() : GameState()
	{
		stateID = PAUSE_STATE;
		isOnState = true;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(PauseState::resume), Vector2i(550, 400), Vector2i(250, 50), RESUME, RESUME_ACTIVE);
	}
	~PauseState()
	{

	}
	void update()
	{
		//std::cout << "\nUpdate PauseState";
	}
	void render()
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(PAUSE_BACKGROUND, 0, 0);
		getCommandButtonManager()->renderButtons();
	}


	bool onExit()
	{
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(PauseState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(PauseState::moveEvent));
		return true;
	}


	fw_Callback resume()
	{
		isOnState = false;
		setNextState(BACK_STATE);
	}
	fw_Callback newGame()
	{
		isOnState = false;
		setNextState(PLAY_STATE);
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