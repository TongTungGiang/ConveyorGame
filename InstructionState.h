#ifndef INSTRUCTION_STATE_H
#define INSTRUCTION_STATE_H

#include "FrameWork.h"
#include "GameState.h"


class InstructionState : public GameState
{
private:
	//const int instructionStateID = INSTRUCTION_STATE;
	int msPerUpdate = MS_PER_UPDATE;
public:

	InstructionState() : GameState()
	{
		stateID = INSTRUCTION_STATE;
		isOnState = true;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(InstructionState::back), Vector2i(558, 10), Vector2i(250, 50), BACK, BACK_ACTIVE);
	}
	
	~InstructionState()
	{
		
	}

	void update()
	{
		//std::cout << "\nUpdate InstructionState";
	}
	void render()
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(INSTRUCTIONBACKGROUND, 0, 0);
		getCommandButtonManager()->renderButtons();
	}


	bool onExit()
	{
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(InstructionState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(InstructionState::moveEvent));
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