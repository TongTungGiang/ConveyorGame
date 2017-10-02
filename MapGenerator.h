#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "FrameWork.h"
#include "Definition.h"
#include "TextureButtonManager.h"
#include "TerrainLayer.h"
#include "BuildingLayer.h"
#include "RoadLayer.h"
#include "SwitcherLayer.h"
#include "Vector2.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "matrix.h"
#include <string>
#include <Windows.h>
#include <Commdlg.h>
#include "GameState.h"

//using namespace FrameWork;

class MapGenerator : public GameState
{

private:
	int xPointer;
	int yPointer;

	TerrainLayer* terrainLayer;
	BuildingLayer* buildingLayer;
	RoadLayer* roadLayer;
	SwitcherLayer* switcherLayer;

	unsigned int selectedTextureID;
	TextureButtonManager* textureButtonManager;
	bool mouseIsPressed;

	bool loadMapFlag;

public:
	MapGenerator();
	~MapGenerator();

	void renderEverything();
	void createTexturePackagesAndButtons();

	virtual bool onEnter();
	virtual bool onExit();

	//virtual void mainLoop();

	//std::wstring showOpenFileDialog();
	//std::wstring showSaveFileDialog();
	
	virtual void update();
	virtual void render();

	fw_Callback processQuitEvent();
	fw_Callback processLeftMouseButtonUpEvent();
	fw_Callback processRightMouseButtonDownEvent();
	fw_Callback processLeftMouseButtonDownEvent();
	fw_Callback processMouseMoveEvent();

	fw_Callback newButtonClick();
	fw_Callback loadButtonClick();
	fw_Callback saveButtonClick();
	fw_Callback homeButtonClick();
};

#endif