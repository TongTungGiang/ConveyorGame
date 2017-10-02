#include "CommandButtonManager.h"
#include <functional>

#ifndef GAME_STATE_H
#define GAME_STATE_H

#define MENU_STATE 0
#define PLAY_STATE 1
#define GAMEOVER_STATE 2
#define MAPGENERATOR_STATE 3
#define CREDIT_STATE 4
#define SAVE_STATE 5
#define BACK_STATE 6
#define LOAD_STATE 7
#define QUIT_STATE 8
#define RESUME_STATE 9
#define PAUSE_STATE 10
#define INSTRUCTION_STATE 11
#define MODESELECT_STATE 12
#define MAPSELECT_STATE 13
#define ERROR_STATE 14

class GameState
{
private:
	CommandButtonManager* buttonManager;
	int nextState;

protected:
	bool isOnState;
	int stateID;

public:

	GameState()
	{
		nextState = MENU_STATE;
		buttonManager = new CommandButtonManager();
	}

	virtual ~GameState()/// virtual nhé :))
	{
		delete buttonManager;
	}

	virtual void update() = 0;
	virtual void render() = 0;

	void mainLoop()
	{
		int lastTime, lag, newTime, elapsed;

		lastTime = FrameWork::Timer::instance()->fwt_getTime();
		lag = 0;

		isOnState = true;

		while (isOnState)
		{
			onEnter();
			newTime = FrameWork::Timer::instance()->fwt_getTime();
			elapsed = newTime - lastTime;
			lastTime = newTime;
			lag += elapsed;
			
			FrameWork::InputHandler::instance()->fwi_PollEvent();

			while (lag >= MS_PER_UPDATE)
			{
				/*  Update game state here  */
				update();
				lag -= MS_PER_UPDATE;
			}

			/*  Render Here */
			FrameWork::Window::instance()->fww_clearScreen();
			render();
			FrameWork::Window::instance()->fww_drawScreen();
		}
	}

	virtual bool onEnter() = 0;

	virtual bool onExit() = 0;

	void setNextState(int _nextState)
	{
		nextState = _nextState;
	}

	int getNextState()
	{
		return nextState;
	}

	int getStateID()
	{
		return stateID;
	}

	CommandButtonManager* getCommandButtonManager()
	{
		return buttonManager;
	}

};

#endif