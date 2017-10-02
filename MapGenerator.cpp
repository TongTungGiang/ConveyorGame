#include "MapGenerator.h"

bool MapGenerator::onEnter()
{
	isOnState = true;

	FrameWork::InputHandler::instance()->fwi_resetCallback();

	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_QUIT, fw_getFunctionAddress(MapGenerator::processQuitEvent));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_UP, fw_getFunctionAddress(MapGenerator::processLeftMouseButtonUpEvent));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_RIGHT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(MapGenerator::processRightMouseButtonDownEvent));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(MapGenerator::processLeftMouseButtonDownEvent));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(MapGenerator::processMouseMoveEvent));

	int cancelflag;
	std::ifstream ifs("tmp/load/cancelflag");
	ifs >> cancelflag;
	ifs.close();

	if (loadMapFlag == true) //Nếu quay về từ state load map thì thực hiện load map đã được chọn
	{
		if (!cancelflag)
		{
			terrainLayer->importFromFile(L"tmp/load/terrain");
			buildingLayer->importFromFile(L"tmp/load/building");
			roadLayer->importFromFile(L"tmp/load/road");
			switcherLayer->importFromFile(L"tmp/load/switcher");
		}
		loadMapFlag = false;
	}

	return true;
}

bool MapGenerator::onExit()
{
	FrameWork::Window::instance()->fww_setClearColor(0, 0, 0, 255);
	return true;
}

MapGenerator::MapGenerator() : GameState()
{
	/*	thiết lập giá trị khởi tạo cho các thuộc tính của đối tượng	*/
	isOnState = true;
	stateID = MAPGENERATOR_STATE;

	mouseIsPressed = false;
	xPointer = 0;
	yPointer = 0;
	textureButtonManager = new TextureButtonManager();

	FrameWork::Window::instance()->fww_setClearColor(255, 255, 255, 255);

	/*	Tạo các layer	*/
	terrainLayer = new TerrainLayer(GRID);
	buildingLayer = new BuildingLayer(BLANK);
	roadLayer = new RoadLayer(BLANK);
	switcherLayer = new SwitcherLayer(BLANK);

	/*	tạo các kết nối cần thiết giữa các layer với nhau	*/
	buildingLayer->setRoadLayerPointer(roadLayer);
	buildingLayer->setSwitcherLayerPointer(switcherLayer);
	roadLayer->setBuildingLayerPointer(buildingLayer);
	roadLayer->setSwitcherLayerPointer(switcherLayer);
	switcherLayer->setRoadLayerPointer(roadLayer);
	switcherLayer->setBuildingLayerPointer(buildingLayer);

	/*	load map từ thư mục autosave nếu có	*/
	if (exists_test(L"autosave/terrain") && exists_test(L"autosave/building")
		&& exists_test(L"autosave/road") && exists_test(L"autosave/switcher"))
	{
		terrainLayer->importFromFile(L"autosave/terrain");
		buildingLayer->importFromFile(L"autosave/building");
		roadLayer->importFromFile(L"autosave/road");
		switcherLayer->importFromFile(L"autosave/switcher");
	}

	/*	Tạo các texture button và command button	*/
	createTexturePackagesAndButtons();

	/*	Chọn texture vẽ mặc định là ROAD	*/
	textureButtonManager->setActiveButton(0, 0);
	selectedTextureID = ROAD;

	SoundManager::Instance()->playMusic("mapeditor", -1);

	loadMapFlag = false;
}

MapGenerator::~MapGenerator()
{

	delete terrainLayer;
	delete buildingLayer;
	delete roadLayer;
	delete switcherLayer;

	delete textureButtonManager;
}

void MapGenerator::createTexturePackagesAndButtons()
{
	/*	Tạo các nút bấm và nút con	*/
	unsigned int button1 = textureButtonManager->createButton(ROAD);
	textureButtonManager->createSubButton(button1, ROAD);

	unsigned int button2 = textureButtonManager->createButton(GRASS);
	textureButtonManager->createSubButton(button2, GRASS);
	textureButtonManager->createSubButton(button2, SEA);
	textureButtonManager->createSubButton(button2, CONCRETE);
	textureButtonManager->createSubButton(button2, MARBLE);
	textureButtonManager->createSubButton(button2, SAND);

	unsigned int button4 = textureButtonManager->createButton(RIVER_GRASS_SOUTH);
	textureButtonManager->createSubButton(button4, RIVER_GRASS_SOUTH);
	textureButtonManager->createSubButton(button4, RIVER_GRASS_NORTH);
	textureButtonManager->createSubButton(button4, RIVER_GRASS_EAST);
	textureButtonManager->createSubButton(button4, RIVER_GRASS_WEST);
	textureButtonManager->createSubButton(button4, RIVER_CORNER_NE);
	textureButtonManager->createSubButton(button4, RIVER_CORNER_NW);
	textureButtonManager->createSubButton(button4, RIVER_CORNER_ES);
	textureButtonManager->createSubButton(button4, RIVER_CORNER_WS);
	textureButtonManager->createSubButton(button4, GRASS_CORNER_WS);
	textureButtonManager->createSubButton(button4, GRASS_CORNER_NE);
	textureButtonManager->createSubButton(button4, GRASS_CORNER_ES);
	textureButtonManager->createSubButton(button4, GRASS_CORNER_NW);
	textureButtonManager->createSubButton(button4, SEA);
	textureButtonManager->createSubButton(button4, GRASS);

	unsigned int button5 = textureButtonManager->createButton(GRASS_SIDE_WS);
	textureButtonManager->createSubButton(button5, GRASS_SIDE_WS);
	textureButtonManager->createSubButton(button5, GRASS_SIDE_NE);
	textureButtonManager->createSubButton(button5, GRASS_SIDE_ES);
	textureButtonManager->createSubButton(button5, GRASS_SIDE_NW);
	textureButtonManager->createSubButton(button5, WATER_SIDE_WS);
	textureButtonManager->createSubButton(button5, WATER_SIDE_NE);
	textureButtonManager->createSubButton(button5, WATER_SIDE_ES);
	textureButtonManager->createSubButton(button5, WATER_SIDE_NW);

	unsigned int button6 = textureButtonManager->createButton(TREE_FOUR);
	textureButtonManager->createSubButton(button6, TREE_FOUR);
	textureButtonManager->createSubButton(button6, TREE_ROCK_LEFT);
	textureButtonManager->createSubButton(button6, TREE_ROCK_RIGHT);
	textureButtonManager->createSubButton(button6, TREE_BIG_SMALL);
	textureButtonManager->createSubButton(button6, TREE_LEAFLESS);
	textureButtonManager->createSubButton(button6, TREE_LEAFFULL);
	textureButtonManager->createSubButton(button6, TREE_LEAFFULL_ROCK_SMALL);
	textureButtonManager->createSubButton(button6, WOOD);
	textureButtonManager->createSubButton(button6, TREE_WOOD);
	textureButtonManager->createSubButton(button6, ROCK_BIG);
	textureButtonManager->createSubButton(button6, ROCK_BIG_TREE);

	unsigned int button7 = textureButtonManager->createButton(FENCE_DOUBLE_1);
	textureButtonManager->createSubButton(button7, FENCE_DOUBLE_1);
	textureButtonManager->createSubButton(button7, FENCE_DOUBLE_2);
	textureButtonManager->createSubButton(button7, FENCE_DOUBLE_3);
	textureButtonManager->createSubButton(button7, FENCE_DOUBLE_4);
	textureButtonManager->createSubButton(button7, FENCE_SINGLE_1);
	textureButtonManager->createSubButton(button7, FENCE_SINGLE_2);
	textureButtonManager->createSubButton(button7, FENCE_SINGLE_3);
	textureButtonManager->createSubButton(button7, FENCE_SINGLE_4);

	unsigned int button8 = textureButtonManager->createButton(TREE_COCO_LEFT);
	textureButtonManager->createSubButton(button8, TREE_COCO_LEFT);
	textureButtonManager->createSubButton(button8, TREE_COCO_RIGHT);
	textureButtonManager->createSubButton(button8, TREE_COCO_ROCK);
	textureButtonManager->createSubButton(button8, TREE_COCO_TWO_ROCK);
	textureButtonManager->createSubButton(button8, TREE_COCO_TWO);
	textureButtonManager->createSubButton(button8, TREE_COCO_THREE);
	textureButtonManager->createSubButton(button8, TREE_LEAF_RED);
	textureButtonManager->createSubButton(button8, TREE_LEAF_YELLOW);
	textureButtonManager->createSubButton(button8, TREE_LEAF_GREEN);
	textureButtonManager->createSubButton(button8, TREE_UNKNOWN_1);
	textureButtonManager->createSubButton(button8, TREE_UNKNOWN_2);

	unsigned int button9 = textureButtonManager->createButton(FLOWER_UNKNOWN_1);
	textureButtonManager->createSubButton(button9, FLOWER_UNKNOWN_1);
	textureButtonManager->createSubButton(button9, FLOWER_UNKNOWN_2);
	textureButtonManager->createSubButton(button9, FLOWER_UNKNOWN_3);
	textureButtonManager->createSubButton(button9, FLOWER_UNKNOWN_4);
	textureButtonManager->createSubButton(button9, FLOWER_SMALL_RED_1);
	textureButtonManager->createSubButton(button9, FLOWER_SMALL_RED_2);
	textureButtonManager->createSubButton(button9, FLOWER_SMALL_YELLOW_1);
	textureButtonManager->createSubButton(button9, FLOWER_SMALL_YELLOW_2);

	unsigned int button10 = textureButtonManager->createButton(SAND_GRASS);
	textureButtonManager->createSubButton(button10, SAND_GRASS);
	textureButtonManager->createSubButton(button10, GRASS_TALL);
	textureButtonManager->createSubButton(button10, GRASS_UNKNOWN);

	unsigned int button11 = textureButtonManager->createButton(BUILDING_MOTEL);
	textureButtonManager->createSubButton(button11, BUILDING_MOTEL);
	textureButtonManager->createSubButton(button11, BUILDING_KEBAB);
	textureButtonManager->createSubButton(button11, BUILDING_BANK_1);
	textureButtonManager->createSubButton(button11, BUILDING_BANK_2);
	textureButtonManager->createSubButton(button11, BUILDING_RESTAURANT);
	textureButtonManager->createSubButton(button11, BUILDING_PRISON);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_1);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_2);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_3);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_4);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_5);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_6);
	textureButtonManager->createSubButton(button11, BUILDING_NEW_HOME_7);

	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapGenerator::loadButtonClick), Vector2i(35, 580), Vector2i(80, 80), BUTTON_LOAD, BUTTON_LOAD_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapGenerator::saveButtonClick), Vector2i(115, 580), Vector2i(80, 80), BUTTON_SAVE, BUTTON_SAVE_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapGenerator::homeButtonClick), Vector2i(35, 660), Vector2i(80, 80), BUTTON_HOME, BUTTON_HOME_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapGenerator::newButtonClick), Vector2i(115, 660), Vector2i(80, 80), BUTTON_NEW, BUTTON_NEW_ACTIVE);
}

void MapGenerator::update()
{

}

void MapGenerator::render()
{
	/*	Vẽ địa hình, nhà cửa, đường xá	*/
	terrainLayer->render();
	roadLayer->render();
	switcherLayer->render();
	buildingLayer->render();

	/*	Vẽ bảng button */
	FrameWork::TextureManager::instance()->fwtm_renderTexture(RIGHT_BAR, 0, 0);
	FrameWork::TextureManager::instance()->fwtm_renderTexture(LEFT_BAR, 1136, 0);

	/*	Vẽ các button*/
	textureButtonManager->renderButtons();
	getCommandButtonManager()->renderButtons();

	/*	Vẽ con trỏ bản đồ	*/
	int xMouse, yMouse;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&xMouse, &yMouse);
	yMouse = FrameWork::Window::instance()->fww_getHeight() - yMouse;
	if (230 < xMouse && xMouse < 1136)
	{
		FrameWork::TextureManager::instance()->fwtm_renderTexture(POINTER, (xPointer - yPointer) * TEXTURE_WIDTH / 2 + MAP_HORIZONTAL_OFFSET,
			(xPointer + yPointer) * TEXTURE_HEIGHT / 2 + MAP_VERTICAL_OFFSET);

		FrameWork::TextureManager::instance()->fwtm_renderTexture(selectedTextureID, xMouse, yMouse, 0.6f);

	}
}


fw_Callback MapGenerator::newButtonClick()
{
	/*	Dòng này chỉ để làm mất hiệu ứng active của nút new */
	getCommandButtonManager()->setNonActiveButton(3);

	/*	Xóa từng layer	*/
	buildingLayer->clear();
	switcherLayer->clear();
	roadLayer->clear();
	terrainLayer->clear();
}

fw_Callback MapGenerator::loadButtonClick()
{
	/*	Dòng này chỉ để làm mất hiệu ứng active của nút load	*/
	getCommandButtonManager()->setNonActiveButton(0);

	/*	Chụp ảnh màn hình hiện tại để làm background cho load state	*/
	FrameWork::Window::instance()->fww_captureScreen("tmp/load/sshot");

	/*	đặt cờ hiệu này để khi quay lại từ load state sẽ thực hiện load map từ thư mục tạm	*/
	loadMapFlag = true;

	/*	False hóa biến duy trì state và chọn state tiếp theo	*/
	isOnState = false;
	setNextState(LOAD_STATE);
}

fw_Callback MapGenerator::saveButtonClick()
{
	/*	Dòng này chỉ để làm mất hiệu ứng active của nút save	*/
	getCommandButtonManager()->setNonActiveButton(1);

	/*	Chụp ảnh màn hình hiện tại để làm background cho load state	*/
	FrameWork::Window::instance()->fww_captureScreen("tmp/save/sshot");

	/*	Kiểm tra tính hợp lệ của map	*/

	bool errorSender_1 = false;//1 sender ra nhiều hướng
	bool errorSender_2 = false;//sender không có building
	bool errorSender_3 = false;//có nhiều hơn 1 sender
	bool errorReceiver_1 = false;// receiver không có building
	bool errorReceiver_2 = false;// có nhiều hơn 10 receiver

	int sender_count = 0;
	int receiver_count = 0;

	for (int j = 0; j < MAP_SQR_Y_DIMENSIONS; j++)
	{
		for (int i = 0; i < MAP_SQR_X_DIMENSIONS; i++)
		{
			unsigned int tsID = switcherLayer->getTextureID(Vector2i(i, j));
			unsigned int tbID = buildingLayer->getTextureID(Vector2i(i, j));
			bool checkBuildingEmpty = buildingLayer->checkBlank(i, j);

			if (tsID == STARTING_POINT_ERROR)
			{
				errorSender_1 = true;
				sender_count++;
				if (checkBuildingEmpty == true)
				{
					errorSender_2 = true;
				}
			}
			if (tsID == STARTING_POINT)
			{
				sender_count++;
				if (checkBuildingEmpty == true)
				{
					errorSender_2 = true;
				}
			}
			if (tsID == ENDING_POINT)
			{
				receiver_count++;
				if (checkBuildingEmpty == true)
				{
					errorReceiver_1 = true;
				}
			}
		}
	}

	if (sender_count != 1) errorSender_3 = true;
	if (receiver_count > 10) errorReceiver_2 = true;

	if (errorSender_1 || errorSender_2 || errorSender_3 || errorReceiver_1 || errorReceiver_2)
	{
		std::ofstream ofs("tmp/save/errorList");
		if (errorSender_1)
		{
			//std::cout << std::endl << "Co ton tai sender co nhieu huong";
			ofs << "There are senders with MORE than ONE direction." << std::endl;
		}
		if (errorSender_2)
		{
			//std::cout << std::endl << "Co ton tai sender khong co building";
			ofs << "There is a blank sender." << std::endl;
		}
		if (errorSender_3)
		{
			//std::cout << std::endl << "So sender khong hop le = " << sender_count;
			ofs << "The sender number must be ONE." << std::endl;
		}
		if (errorReceiver_1)
		{
			ofs << "There is a blank receiver." << std::endl;
		}
		if (errorReceiver_2)
		{
			//std::cout << std::endl << "Co nhieu hon 10 receiver";
			ofs << "There should not have more than TEN receivers." << std::endl;
		}
		isOnState = false;
		setNextState(ERROR_STATE);
		return;
	}
	/*	Xuất map hiện tại vào file tạm để phục vụ cho việc save map	*/
	terrainLayer->exportToFile(L"tmp/save/terrain");
	buildingLayer->exportToFile(L"tmp/save/building");
	roadLayer->exportToFile(L"tmp/save/road");
	switcherLayer->exportToFile(L"tmp/save/switcher");

	/*	False hóa biến duy trì state và chọn state tiếp theo	*/
	isOnState = false;
	setNextState(SAVE_STATE);
}


fw_Callback MapGenerator::homeButtonClick()
{
	/*	Dòng này chỉ để làm mất hiệu ứng active của nút save	*/
	getCommandButtonManager()->setNonActiveButton(2);

	/*	Autosave map hiện tại	*/
	terrainLayer->exportToFile(L"autosave/terrain");
	buildingLayer->exportToFile(L"autosave/building");
	roadLayer->exportToFile(L"autosave/road");
	switcherLayer->exportToFile(L"autosave/switcher");

	/*	False hóa biến duy trì state và chọn state tiếp theo	*/
	isOnState = false;
	setNextState(MENU_STATE);
}


fw_Callback MapGenerator::processQuitEvent()
{
	isOnState = false;
}

fw_Callback MapGenerator::processLeftMouseButtonDownEvent()
{
	int xMouse, yMouse;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&xMouse, &yMouse);
	yMouse = FrameWork::Window::instance()->fww_getHeight() - yMouse;
	mouseIsPressed = true;

	// trong phạm vi bản đồ
	if (230 < xMouse && xMouse < 1136)
	{

		//Nếu texture đang được chọn là ROAD và người chơi ấn vào 1 switcher => switcher đổi hướng
		if (selectedTextureID == ROAD)
		{
			if (!roadLayer->checkBlank(xPointer, yPointer))
			{
				switcherLayer->toNextDirection(Vector2i(xPointer, yPointer));
			}
		}

		//Nếu texture đang được chọn không phải ROAD => Vẽ building hoặc terrain
		else
		{
			//Vẽ building
			if (selectedTextureID >= 84)
			{
				buildingLayer->modifyTileMatrix(Vector2i(xPointer, yPointer), selectedTextureID);
			}

			//Vẽ terrain
			else if (48 <= selectedTextureID && selectedTextureID <= 83)
			{
				terrainLayer->modifyTileMatrix(Vector2i(xPointer, yPointer), selectedTextureID);
			}
		}
	}

	// trong phạm vi thanh bên trái
	else if (xMouse <= 230)
	{
		int tmp = textureButtonManager->browseArray_LeftClick_1();
		if (tmp != -1)
		{
			selectedTextureID = tmp;
		}
		getCommandButtonManager()->browseArray_LeftClick();
	}

	//trong phạm vi thanh bên phải
	else
	{
		int tmp = textureButtonManager->browseArray_LeftClick_2();
		if (tmp != -1)
		{
			selectedTextureID = tmp;
		}
	}
}

fw_Callback MapGenerator::processLeftMouseButtonUpEvent()
{
	mouseIsPressed = false;
}

fw_Callback MapGenerator::processRightMouseButtonDownEvent()
{
	// trong phạm vi bản đồ
	int xMouse;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&xMouse, NULL);
	if (230 < xMouse && xMouse < 1136)
	{
		Vector2i tmpVec;
		tmpVec(xPointer, yPointer);
		if (buildingLayer->checkBlank(xPointer, yPointer) == false)
		{
			buildingLayer->deleteTile(tmpVec);
		}
		else if (roadLayer->checkBlank(xPointer, yPointer) == false)
		{
			roadLayer->deleteTile(tmpVec);
		}
		else if (terrainLayer->checkBlank(xPointer, yPointer) == false)
		{
			terrainLayer->deleteTile(tmpVec);
		}
	}
}

fw_Callback MapGenerator::processMouseMoveEvent()
{
	int xMouse, yMouse;
	FrameWork::InputHandler::instance()->fwi_getMousePosition(&xMouse, &yMouse);
	yMouse = FrameWork::Window::instance()->fww_getHeight() - yMouse;

	Vector2f tmp = FrameWork::Converter::instance()->fwc_graphicCoordToLogicCoord(Vector2i(xMouse, yMouse));
	xPointer = tmp.getX();
	yPointer = tmp.getY();

	static int x_prev2 = xPointer, y_prev2 = yPointer, x_prev1 = xPointer, y_prev1 = yPointer;
	if (!mouseIsPressed)
	{
		x_prev2 = xPointer; y_prev2 = yPointer; x_prev1 = xPointer; y_prev1 = yPointer;
		if (xMouse < 230)
		{
			textureButtonManager->browseArray_Point_1();
			getCommandButtonManager()->browseArray_Point();
		}
		else if (1136 < xMouse)
		{
			textureButtonManager->browseArray_Point_2();
		}
	}
	else if (230 < xMouse && xMouse < 1136)
	{
		if (selectedTextureID == ROAD)
		{
			if (xPointer == x_prev1 && xPointer == x_prev2 && yPointer != y_prev1)
			{
				if (yPointer > y_prev1 && y_prev1 >= y_prev2)
				{
					for (int i = y_prev1 + 1; i < yPointer; i++)
					{
						roadLayer->addTileDirection(xPointer, i, EAST, true);
						roadLayer->addTileDirection(xPointer, i, WEST, false);
					}
					roadLayer->addTileDirection(xPointer, y_prev1, WEST, false);
					roadLayer->addTileDirection(xPointer, yPointer, EAST, true);

					y_prev2 = y_prev1;
					y_prev1 = yPointer;
				}
				else if (yPointer < y_prev1 && y_prev1 <= y_prev2)
				{
					for (int i = yPointer + 1; i < y_prev1; i++)
					{
						roadLayer->addTileDirection(xPointer, i, EAST, false);
						roadLayer->addTileDirection(xPointer, i, WEST, true);
					}
					roadLayer->addTileDirection(xPointer, y_prev1, EAST, false);
					roadLayer->addTileDirection(xPointer, yPointer, WEST, true);

					y_prev2 = y_prev1;
					y_prev1 = yPointer;
				}
			}
			else if (yPointer == y_prev1 && yPointer == y_prev2 && xPointer != x_prev1)
			{
				if (xPointer > x_prev1 && x_prev1 >= x_prev2)
				{
					for (int i = x_prev1 + 1; i < xPointer; i++)
					{
						roadLayer->addTileDirection(i, yPointer, SOUTH, true);
						roadLayer->addTileDirection(i, yPointer, NORTH, false);
					}
					roadLayer->addTileDirection(x_prev1, yPointer, NORTH, false);
					roadLayer->addTileDirection(xPointer, yPointer, SOUTH, true);

					x_prev2 = x_prev1;
					x_prev1 = xPointer;
				}
				else if (xPointer < x_prev1 && x_prev1 <= x_prev2)
				{
					for (int i = xPointer + 1; i < x_prev1; i++)
					{
						roadLayer->addTileDirection(i, yPointer, NORTH, true);
						roadLayer->addTileDirection(i, yPointer, SOUTH, false);
					}
					roadLayer->addTileDirection(x_prev1, yPointer, SOUTH, false);
					roadLayer->addTileDirection(xPointer, yPointer, NORTH, true);

					x_prev2 = x_prev1;
					x_prev1 = xPointer;
				}
			}
		}

		else if (xPointer != x_prev1 || yPointer != y_prev1)
		{
			if (selectedTextureID >= 84)
			{
				buildingLayer->modifyTileMatrix(Vector2i(xPointer, yPointer), selectedTextureID);
			}
			else if (48 <= selectedTextureID && selectedTextureID <= 83)
			{
				terrainLayer->modifyTileMatrix(Vector2i(xPointer, yPointer), selectedTextureID);
			}
			x_prev2 = x_prev1;
			y_prev2 = y_prev1;
			x_prev1 = xPointer;
			y_prev1 = yPointer;
		}
	}
}
