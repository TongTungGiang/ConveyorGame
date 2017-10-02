#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "FrameWork.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

class GameOverState : public GameState
{
private:

	int win;
	int score;

public:

	GameOverState() : GameState()
	{
		stateID = GAMEOVER_STATE;
		getCommandButtonManager()->createButton(fw_getFunctionAddress(GameOverState::back), Vector2i(30, 30), Vector2i(250, 50), BACK, BACK_ACTIVE);

		std::ifstream f;
		f.open("tmp/play/result");
		f >> win >> score;
		f.close();
	}

	~GameOverState()
	{

	}

	virtual void update()
	{

	}

	virtual void render()
	{
		if (win)
		{
			FrameWork::FontLibrary::instance()->fwf_renderText("YOU WIN!!!", "sketchy large", { 255, 255, 255, 255 }, 500, 500);
		}
		else
		{
			FrameWork::FontLibrary::instance()->fwf_renderText("YOU LOSE!!!", "sketchy large", { 255, 255, 255, 255 }, 500, 500);
		}

		FrameWork::FontLibrary::instance()->fwf_renderText("Your score:", "solid", { 255, 255, 255, 255 }, 500, 400);
		std::string _score = std::to_string(score);
		FrameWork::FontLibrary::instance()->fwf_renderText(_score.c_str(), "sketchy large", { 255, 255, 255, 255 }, 650, 370);

		getCommandButtonManager()->renderButtons();
	}

	bool onExit()
	{
		int mode;

		std::ifstream ifs("tmp/play/mode");
		ifs >> mode;
		ifs.close();

		if (win && mode == 0)
		{
			std::string nextlv;

			std::ifstream ifs("tmp/play/nextlv");
			std::getline(ifs, nextlv);
			ifs.close();

			std::ofstream ofs(std::string("map/campaign/unlock/") + std::string(nextlv));
			ofs << 1;
			ofs.close();
		}
		return true;
	}

	bool onEnter()
	{
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(GameOverState::handleLeftMouseClick));
		FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(GameOverState::moveEvent));
		return true;
	}

	fw_Callback back()
	{
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