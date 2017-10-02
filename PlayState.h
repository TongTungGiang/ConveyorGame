#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#define FREEZE_TIME 5

#include <vector>
#include <algorithm>

#include "GameState.h"
#include "FrameWork.h"

#include "Package.h"
#include "Receiver.h"
#include "Sender.h"

#include "TerrainLayer.h"
#include "BuildingLayer.h"
#include "RoadLayer.h"
#include "SwitcherLayer.h"

class PlayState : public GameState
{

private:

	int score;
	int winningScore;
	unsigned int playTime;
	unsigned int startPlaying;
	unsigned int clock;
	unsigned int currentTime;

	std::vector<Switcher*> *switcherArray;

	std::vector<Package*> *packageArray;

	std::vector<Receiver*> *receiverArray;

	std::vector<GameObject*> *buildingArray;

	std::vector<GameObject*> *renderArray;

	Sender *sender;

	TerrainLayer* terrainLayer;
	BuildingLayer* buildingLayer;
	RoadLayer* roadLayer;
	SwitcherLayer* switcherLayer;

public:

	PlayState();
	~PlayState();

	virtual bool onEnter();
	virtual bool onExit();

	virtual void update();
	virtual void render();

	void sortPackages();
	fw_Callback processMouseMoveEvent();
	fw_Callback handleMouseLeftClickEvent();
	fw_Callback buttonPauseClick();
	fw_Callback buttonBackClick();
	void loadSRS(char *fileName);

};

#endif