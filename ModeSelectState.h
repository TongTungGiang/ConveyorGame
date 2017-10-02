#ifndef MODE_SELECT_STATE_H
#define MODE_SELECT_STATE_H

#include "FrameWork.h"
#include "GameState.h"
#include "GameStateManager.h"

class ModeSelectState : public GameState
{
public:

	ModeSelectState() : GameState()
	{
		stateID = MODESELECT_STATE;
		isOnState = true;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(ModeSelectState::buttonCampaignClick), Vector2i(400, 490), Vector2i(400, 70), CAMPAIGN, CAMPAIGN_ACTIVE);
		getCommandButtonManager()->createButton(fw_getFunctionAddress(ModeSelectState::buttonCustomModeClick), Vector2i(400, 400), Vector2i(400, 70), CUSTOM_MODE, CUSTOM_MODE_ACTIVE);
		getCommandButtonManager()->createButton(fw_getFunctionAddress(ModeSelectState::buttonMainMenuClick), Vector2i(400, 310), Vector2i(400, 70), BACK_TO_MENU, BACK_TO_MENU_ACTIVE);
	}
	~ModeSelectState()
	{

	}

	void update()
	{
		//std::cout << "\nUpdate ModeSelectState";
	}
	void render()
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(MENU_BACKGROUND, 0, 0);
		getCommandButtonManager()->renderButtons();
	}


	bool onExit()
	{
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(ModeSelectState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(ModeSelectState::moveEvent));
		return true;
	}

	fw_Callback buttonCampaignClick()
	{
		getCommandButtonManager()->setNonActiveButton(0);
		std::ofstream ofs("tmp/play/mode");
		ofs << 0;
		ofs.close();

		/*	Chụp ảnh màn hình hiện tại để làm background cho select map state	*/
		FrameWork::Window::instance()->fww_captureScreen("tmp/play/sshot");
		
		isOnState = false;
		setNextState(MAPSELECT_STATE);
	}

	fw_Callback buttonCustomModeClick()
	{
		getCommandButtonManager()->setNonActiveButton(1);
		std::ofstream ofs("tmp/play/mode");
		ofs << 1;
		ofs.close();

		/*	Chụp ảnh màn hình hiện tại để làm background cho select map state	*/
		FrameWork::Window::instance()->fww_captureScreen("tmp/play/sshot");

		isOnState = false;
		setNextState(MAPSELECT_STATE);
	}

	fw_Callback buttonMainMenuClick()
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