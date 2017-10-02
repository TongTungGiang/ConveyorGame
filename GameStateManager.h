#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "MenuState.h"
#include "PlayState.h"

#include "MapGenerator.h"
#include "CreditState.h"
#include "SaveState.h"
#include "LoadState.h"
#include "InstructionState.h"
#include "PauseState.h"
#include "ModeSelectState.h"
#include "MapSelectState.h"
#include "GameOverState.h"
#include "ErrorState.h"

#include <vector>

class GameStateManager
{

private:
	std::vector < GameState* >* gameStates;

public:

	GameStateManager()
	{
		gameStates = new std::vector<GameState*>;
		pushState(new MenuState());
	}

	~GameStateManager()
	{
		delete gameStates;
	}

	void pushState(GameState* pState)
	{
		gameStates->push_back(pState);
		gameStates->back()->onEnter();
	}

	void changeState(GameState *pState)
	{
		if (!gameStates->empty())
		{
			popState();
		}

		pushState(pState);
	}

	void popState()
	{
		if (!gameStates->empty())
		{
			if (gameStates->back()->onExit())
			{
				delete gameStates->back();
				gameStates->pop_back();
			}
		}
	}
	
	void run()
	{
		while (gameStates->size() > 0)
		{
			getCurrentState()->mainLoop();
			FrameWork::InputHandler::instance()->fwi_resetCallback();
			switch (getCurrentState()->getNextState())
			{
			case MENU_STATE: changeState(new MenuState()); break;
			case PLAY_STATE: pushState(new PlayState()); break;
			case MAPGENERATOR_STATE: changeState(new MapGenerator()); break;
			case CREDIT_STATE: changeState(new CreditState()); break;
			case SAVE_STATE: pushState(new SaveState()); break;
			case BACK_STATE: popState(); break;
			case LOAD_STATE: pushState(new LoadState()); break;
			case QUIT_STATE: popState(); break;
			case PAUSE_STATE: pushState(new PauseState()); break;
			case INSTRUCTION_STATE: changeState(new InstructionState()); break;
			case MODESELECT_STATE: changeState(new ModeSelectState()); break;
			case MAPSELECT_STATE: pushState(new MapSelectState()); break;
			case GAMEOVER_STATE: changeState(new GameOverState()); break;
			case ERROR_STATE: pushState(new ErrorState()); break;
			}
		}
	}

	GameState* getCurrentState()
	{
		return gameStates->back();
	}

};



#endif
