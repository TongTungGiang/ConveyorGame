#include <iostream>
#include <fstream>
#include "PlayState.h"
#include <string>
#include <fstream>

//---------------------------------------------------------------------------------------------
//   return true if play state is created
//
bool PlayState::onEnter()
{
	FrameWork::InputHandler::instance()->fwi_resetCallback();

	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
		fw_getFunctionAddress(PlayState::handleMouseLeftClickEvent));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE,
		fw_getFunctionAddress(PlayState::processMouseMoveEvent));
	return true;
}

//---------------------------------------------------------------------------------------------
//   return true if play state is removed
//
bool PlayState::onExit()
{
	return true;
}



//---------------------------------------------------------------------------------------------
//   class constructor
//
PlayState::PlayState(): GameState()
{
	stateID = PLAY_STATE;

	/*  Tạo các button điều khiển  */
	switcherArray = new std::vector < Switcher* >;
	receiverArray = new std::vector < Receiver* >;
	packageArray = new std::vector < Package* >;
	buildingArray = new std::vector < GameObject* >;
	renderArray = new std::vector < GameObject* >;
	
	sender = new Sender();

	/*	Tạo các layer	*/
	terrainLayer = new TerrainLayer(GRID);
	buildingLayer = new BuildingLayer(BLANK);
	roadLayer = new RoadLayer(BLANK);
	switcherLayer = new SwitcherLayer(BLANK);

	/*	tạo các kết nối cần thiết giữa các layer với nhau	*/
	buildingLayer->setRoadLayerPointer(roadLayer);
	roadLayer->setBuildingLayerPointer(buildingLayer);
	roadLayer->setSwitcherLayerPointer(switcherLayer);
	switcherLayer->setRoadLayerPointer(roadLayer);
	switcherLayer->setBuildingLayerPointer(buildingLayer);

	terrainLayer->importFromFile(L"tmp/play/terrain");
	buildingLayer->importFromFile(L"tmp/play/building");
	roadLayer->importFromFile(L"tmp/play/road");
	switcherLayer->importFromFile(L"tmp/play/switcher");

	loadSRS("tmp/play/switcher");

	/*	Tạo building array	*/
	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			if (buildingLayer->getTileType(Vector2i(i, j)) == TYPE_BUILDING_HOME || buildingLayer->getTileType(Vector2i(i, j)) == TYPE_BUILDING_NOT_HOME)
			{
				GameObject* newBuilding = new GameObject(Vector2f(i, j), buildingLayer->getTextureID(Vector2i(i, j)), 0);
				buildingArray->push_back(newBuilding);
			}
		}
	}

	// init another variables
	score = 0;
	std::ifstream ifs("tmp/play/info");
	ifs >> winningScore >> playTime;
	ifs.close();

	currentTime = startPlaying = FrameWork::Timer::instance()->fwt_getTime();
	clock = 0;

	isOnState = true;

	SoundManager::Instance()->playMusic("play", -1);

	getCommandButtonManager()->createButton(fw_getFunctionAddress(PlayState::buttonPauseClick), Vector2i(1140, 680), Vector2i(220, 50), PAUSE, PAUSE_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(PlayState::buttonBackClick), Vector2i(1140, 620), Vector2i(220, 50), BACK_FROM_PLAY_TO_MENU, BACK_FROM_PLAY_TO_MENU_ACTIVE);
}

PlayState::~PlayState()
{
	for (std::vector<Switcher*>::iterator _iterator = switcherArray->begin(); _iterator != switcherArray->end(); _iterator++)
	{
		delete (*_iterator);
	}

	for (std::vector<Receiver*>::iterator _iterator = receiverArray->begin(); _iterator != receiverArray->end(); _iterator++)
	{
		delete (*_iterator);
	}

	for (std::vector<GameObject*>::iterator _iterator = renderArray->begin(); _iterator != renderArray->end(); _iterator++)
	{
		delete (*_iterator);
	}

	for (std::vector<GameObject*>::iterator _iterator = buildingArray->begin(); _iterator != buildingArray->end(); _iterator++)
	{
		delete (*_iterator);
	}

	for (std::vector<Package*>::iterator _iterator = packageArray->begin(); _iterator != packageArray->end(); _iterator++)
	{
		delete (*_iterator);
	}

	delete switcherArray;
	delete receiverArray;
	delete packageArray;
	delete buildingArray;
	delete renderArray;

	delete sender;
	delete terrainLayer;
	delete buildingLayer;
	delete roadLayer;
	delete switcherLayer;
}

fw_Callback PlayState::buttonBackClick()
{
	isOnState = false;
	setNextState(BACK_STATE);
}

fw_Callback PlayState::buttonPauseClick()
{
	isOnState = false;
	setNextState(PAUSE_STATE);
}

fw_Callback PlayState::processMouseMoveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}
//---------------------------------------------------------------------------------------------
//   callback function: handle mouse left click event
//
fw_Callback PlayState::handleMouseLeftClickEvent()
{
	int mouseX, mouseY;

	FrameWork::InputHandler::instance()->fwi_getMousePosition(&mouseX, &mouseY);
	mouseY = FrameWork::Window::instance()->fww_getHeight() - mouseY;

	Vector2f tmp;
	tmp = FrameWork::Converter::instance()->fwc_graphicCoordToLogicCoord(Vector2i(mouseX, mouseY));
	for (int i = 0; i < switcherArray->size(); i++)
	{
		float switcherX = switcherArray->at(i)->getLogicalX(),
			switcherY = switcherArray->at(i)->getLogicalY();
		if (tmp.getX() > switcherX && tmp.getX() < switcherX + 1.0f &&
			tmp.getY() > switcherY && tmp.getY() < switcherY + 1.0f)
		{
			switcherArray->at(i)->changeToNextPossibleDirection();
			SoundManager::Instance()->playSound("click", 0);
			switcherLayer->toNextDirection( Vector2i((int)tmp.getX(), (int)tmp.getY()) );
			break;
		}
	}
	getCommandButtonManager()->browseArray_LeftClick();
}

//---------------------------------------------------------------------------------------------
//   load sender, receiver and switcher from file
//
void PlayState::loadSRS(char *fileName)
{
	int type;
	float xLCoord, yLCoord;
	bool dirN, dirW, dirS, dirE;

	//int senderDirection;
	int receiverTextureID;
	int switcherDefaultDirection;

	int receiverNumber = 0;

	std::ifstream ifs(fileName);

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			//--------------------------------------------------------------------------------------------------
			// READ FIELDS FROM MAP FILE
			// type: type of square (sender, switcher or receiver)
			// xLCoord, yLCoord: logical coordinate of square
			// dirX: = true if direction X is movable (only if the square is a switcher)
			// senderDirection, receiverTextureID, switcherDefaultDirection: square's property according to its type
			ifs >> type >> xLCoord >> yLCoord >>	
				dirN >> dirW >> dirS >> dirE >>
				receiverTextureID >> switcherDefaultDirection;

			// if square is a sender
			if (type == TYPE_SENDER)
			{
				if (dirN)
				{
					sender->setLogicalCoordinate(xLCoord + 1, yLCoord);
					sender->setDir(NORTH);
				}
				else if (dirW)
				{
					sender->setLogicalCoordinate(xLCoord, yLCoord + 1);
					sender->setDir(WEST);
				}
				else if (dirS)
				{
					sender->setLogicalCoordinate(xLCoord - 1, yLCoord);
					sender->setDir(SOUTH);
				}
				else if (dirE)
				{
					sender->setLogicalCoordinate(xLCoord, yLCoord - 1);
					sender->setDir(EAST);
				}
			}

			// if square is a receiver
			else if (type == TYPE_RECEIVER)
			{
				receiverNumber++;
				Receiver* tmp = new Receiver(Vector2f(xLCoord, yLCoord));
				tmp->setReceiverTextureID(receiverTextureID);
				receiverArray->push_back(tmp);
			}

			// if square is a switcher
			else if (type == TYPE_SWITCHER)
			{
				Switcher* tmp = new Switcher(Vector2f(xLCoord, yLCoord), switcherDefaultDirection);
				tmp->setPossibleDirections(dirN, dirW, dirS, dirE);
				tmp->setDir(switcherDefaultDirection);
				switcherArray->push_back(tmp);
			}
		} // end for i
	} // end for j

	sender->setMaxPackageNumber(receiverNumber);
}

void PlayState::sortPackages()
{
	std::sort(renderArray->begin(), renderArray->end(), GameObject::PerspectiveSort());
}

//---------------------------------------------------------------------------------------------
//   process game logic
//
void PlayState::update()
{
	// update clock here
	int _currentTime = FrameWork::Timer::instance()->fwt_getTime();
	if (_currentTime / 1000 > currentTime / 1000)
		clock++;
	currentTime = _currentTime;
	
	// send new package here
	if (clock - sender->getSendTime() > FREEZE_TIME)
	{
		int playerTexture = rand() % 3 + PLAYER1;
		int currentPackageNumber = sender->getCurrentNumberOfPackageSent();
		if (currentPackageNumber < sender->getMaxPackageNumber())
		{
			sender->setSendTime(clock);
			int target = rand() % receiverArray->size();
			Package* temp = sender->sendNewPackage(playerTexture, receiverArray->at(target)->getReceiverTextureID());
			packageArray->push_back(temp);
		}
	}

	// move current packages and check their collision
	for (int i = 0; i < packageArray->size(); i++)
	{
		bool canMove = true;
		for (int j = i + 1; j < packageArray->size(); j++)
		{
			if (abs(packageArray->at(i)->getLogicalX() - packageArray->at(j)->getLogicalX()) <= 0.5f &&
				abs(packageArray->at(i)->getLogicalY() - packageArray->at(j)->getLogicalY()) <= 0.5f)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
			packageArray->at(i)->move();

		// check collision with switcher
		for (int j = 0; j < switcherArray->size(); j++)
		{
			if (packageArray->at(i)->checkCollision(*switcherArray->at(j)))
				packageArray->at(i)->setDir(switcherArray->at(j)->getDir());
		}

		// check collision with receiver
		for (int j = 0; j < receiverArray->size(); j++)
		if (packageArray->at(i)->checkCollision(*receiverArray->at(j))) // collided with a receiver
		{
			Package *temp = packageArray->at(i);
			packageArray->erase(packageArray->begin() + i);


			if (receiverArray->at(j)->receivedRightPackage(*temp))
			{
				SoundManager::Instance()->playSound("right", 0);
				score++;
			}
			else
			{
				SoundManager::Instance()->playSound("wrong", 0);
				if (score > 0)
					score--;
			}

			delete temp;

			sender->reduceCurrentNumberOfPackageSent();

			break;
		}
	}
}

//---------------------------------------------------------------------------------------------
//   render objects
//

void PlayState::render()
{
	// Draw background and layers
	terrainLayer->render();
	roadLayer->render();
	switcherLayer->render();

	//sort package for rendering
	for (int i = 0; i < packageArray->size(); i++)
	{
		renderArray->push_back(packageArray->at(i));
	}

	for (int i = 0; i < buildingArray->size(); i++)
	{
		renderArray->push_back(buildingArray->at(i));
	}
	sortPackages();
	
	//render buildings and packages 
	for (int i = 0; i < renderArray->size(); i++)
	{
		renderArray->at(i)->render();
	}

	// reset render array
	renderArray->clear();

	// draw add or substract score effect
	for (int i = 0; i < receiverArray->size(); i++)
	{
		int currentTime = FrameWork::Timer::instance()->fwt_getTime();
		int receivedTime = receiverArray->at(i)->getTimeReceived();
		if (currentTime - receivedTime <= 1000)
		{
			Vector2i coord = FrameWork::Converter::instance()->fwc_logicCoordToGraphicCoord(receiverArray->at(i)->getLogicalCoord());
			if (receiverArray->at(i)->receivedRightPackage())
				FrameWork::TextureManager::instance()->fwtm_renderTexture(MONEY_PLUS, coord.getX(), coord.getY() + (int)(60 * (currentTime - receivedTime)/1000.0), 0.6);
			else
				FrameWork::TextureManager::instance()->fwtm_renderTexture(MONEY_MINUS, coord.getX(), coord.getY(), 0.6);
		}
	}

	// draw side bars
	FrameWork::TextureManager::instance()->fwtm_renderTexture(RIGHT_BAR, 0, 0);
	FrameWork::TextureManager::instance()->fwtm_renderTexture(LEFT_BAR, 1136, 0);
	getCommandButtonManager()->renderButtons();

	// render score
	FrameWork::FontLibrary::instance()->fwf_renderText("Score:", "solid", { 0, 0, 0, 255 }, 40, 390);
	std::string scoreText = std::to_string(score);
	FrameWork::FontLibrary::instance()->fwf_renderText(scoreText.c_str(), "sketchy large", { 0, 0, 0, 255 }, 60, 300);

	// render winning score
	FrameWork::FontLibrary::instance()->fwf_renderText("Score to win:", "solid", { 0, 0, 0, 255 }, 1176, 390);
	std::string winningScoreText = std::to_string(winningScore);
	FrameWork::FontLibrary::instance()->fwf_renderText(winningScoreText.c_str(), "solid large", { 0, 0, 0, 255 }, 1196, 300);
	if (score >= winningScore)
		FrameWork::TextureManager::instance()->fwtm_renderTexture(CUP, 1176, 300);

	// render count down time
	int second = (playTime - clock) % 60;
	int minute = (playTime - clock) / 60;

	FrameWork::FontLibrary::instance()->fwf_renderText("Time remaining:", "solid", { 0, 0, 0, 255 }, 10, 670);
	std::string time = std::to_string(minute) + ":" + std::to_string(second);
	FrameWork::FontLibrary::instance()->fwf_renderText(time.c_str(), "sketchy large", { 0, 0, 0, 255 }, 10, 580);
	if (playTime - clock == 0)
	{
		isOnState = false;

		std::ofstream f("tmp/play/result");
		int win =(int) (score >= winningScore);
		f << win << " " << score;
		f.close();

		SoundManager::Instance()->playSound("timesup", 0);

		setNextState(GAMEOVER_STATE);
	}
}