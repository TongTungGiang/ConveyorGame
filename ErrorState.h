#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include "FrameWork.h"
#include "GameState.h"
//#include "GameStateManager.h"
#include "SoundManager.h"
#include <string>


class ErrorState : public GameState
{
private:
	//const int PauseStateID = CREDIT_STATE;
	int msPerUpdate = MS_PER_UPDATE;
	int errorLineNum;
	std::string errorLine[5];
	fw_Texture* background;

public:

	ErrorState() : GameState()
	{
		stateID = ERROR_STATE;
		isOnState = true;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(ErrorState::backButtonClick), Vector2i(560, 150), Vector2i(250, 50), BACK, BACK_ACTIVE);

		background = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(L"tmp/save/sshot");

		//Doc thong bao loi

		std::ifstream ifs("tmp/save/errorList");

		errorLine[0] = "";
		errorLine[1] = "";
		errorLine[2] = "";
		errorLine[3] = "";
		errorLine[4] = "";

		errorLineNum = 0;

		while (std::getline(ifs, errorLine[errorLineNum]))
		{
			errorLineNum++;
			if (errorLineNum > 4) break;
		}		
	}
	~ErrorState()
	{
		SDL_DestroyTexture(background);
	}
	void update()
	{
		
	}
	void render()
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(background, 0, 0);
		FrameWork::TextureManager::instance()->fwtm_renderTexture(ERROR_BACKGROUND, 260, 90);
		getCommandButtonManager()->renderButtons();

		if (errorLine[0] != "")
		{
			FrameWork::FontLibrary::instance()->fwf_renderText(errorLine[0].c_str(), "solid", { 255, 255, 255, 255 }, 270, 450);
		}
		else return;

		if (errorLine[1] != "")
		{
			FrameWork::FontLibrary::instance()->fwf_renderText(errorLine[1].c_str(), "solid", { 255, 255, 255, 255 }, 270, 400);
		}
		else return;

		if (errorLine[2] != "")
		{
			FrameWork::FontLibrary::instance()->fwf_renderText(errorLine[2].c_str(), "solid", { 255, 255, 255, 255 }, 270, 350);
		}
		else return;

		if (errorLine[3] != "")
		{
			FrameWork::FontLibrary::instance()->fwf_renderText(errorLine[3].c_str(), "solid", { 255, 255, 255, 255 }, 270, 300);
		}
		else return;

		if (errorLine[4] != "")
		{
			FrameWork::FontLibrary::instance()->fwf_renderText(errorLine[4].c_str(), "solid", { 255, 255, 255, 255 }, 270, 250);
		}
	}


	bool onExit()
	{
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(ErrorState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(ErrorState::moveEvent));
		return true;
	}


	fw_Callback backButtonClick()
	{
		SoundManager::Instance()->playSound("click", 0);
		isOnState = false;
		setNextState(BACK_STATE);
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