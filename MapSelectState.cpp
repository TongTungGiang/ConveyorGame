#include "MapSelectState.h"
#include "FrameWork.h"
#include <string>

#define CUSTOM_MAP_INFO_FOLDER L"map/custommap/info/"
#define CUSTOM_MAP_PREVIEW_FOLDER L"map/custommap/preview/"
#define CUSTOM_MAP_TERRAIN_FOLDER L"map/custommap/terrain/"
#define CUSTOM_MAP_BUILDING_FOLDER L"map/custommap/building/"
#define CUSTOM_MAP_ROAD_FOLDER L"map/custommap/road/"
#define CUSTOM_MAP_SWITCHER_FOLDER L"map/custommap/switcher/"

#define CAMPAIGN_MAP_INFO_FOLDER L"map/campaign/info/"
#define CAMPAIGN_MAP_PREVIEW_FOLDER L"map/campaign/preview/"
#define CAMPAIGN_MAP_TERRAIN_FOLDER L"map/campaign/terrain/"
#define CAMPAIGN_MAP_BUILDING_FOLDER L"map/campaign/building/"
#define CAMPAIGN_MAP_ROAD_FOLDER L"map/campaign/road/"
#define CAMPAIGN_MAP_SWITCHER_FOLDER L"map/campaign/switcher/"

MapSelectState::MapSelectState() : GameState()
{
	stateID = MAPSELECT_STATE;

	/*	Tạo các button với các command function đã được định nghĩa tương ứng với chức năng của button	*/
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapSelectState::buttonMapLeft), Vector2i(296, 340), Vector2i(362, 307), NONE_ACTIVEBUTTON, ACTIVEBUTTON);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapSelectState::buttonMapRight), Vector2i(708, 340), Vector2i(362, 307), NONE_ACTIVEBUTTON, ACTIVEBUTTON);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapSelectState::buttonPrevClick), Vector2i(300, 75), Vector2i(150, 50), PREV, PREV_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapSelectState::buttonCancelClick), Vector2i(558, 50), Vector2i(250, 50), CANCEL, CANCEL_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MapSelectState::buttonNextClick), Vector2i(916, 75), Vector2i(150, 50), NEXT, NEXT_ACTIVE);

	/*	Đọc thông tin về chế độ chơi (campaign hay custom)	*/
	std::ifstream ifs("tmp/play/mode");
	ifs >> gamemode;
	ifs.close();

	/*	Duyệt thư mục custommap/info và lấy danh sách các map	*/
	getMapList();

	previewImage1 = NULL;
	previewImage2 = NULL;

	mapLeftName = NULL;
	mapRightName = NULL;

	checkUnlockLeft = 0;
	checkUnlockRight = 0;

	/*	Nếu trong thư mục custommap có nhiều hơn 1 map, vẽ preview của map đầu tiên vào nút preview bên trái	*/
	if (mapList.size() >= 1)
	{
		previewImage1 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(0));
		mapLeftName = wstringToCharArray(mapList.at(0));
		std::ifstream ifs(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(0));
		ifs >> mapLeftPackage >> mapLeftTime;
		ifs.close();
	}
	/*	Nếu trong thư mục custommap có nhiều hơn 1 map, vẽ preview của map đầu tiên vào nút preview bên trái	*/
	if (mapList.size() == 1)
	{
		setMapPreviewInfo(0, 0);
	}

	/*	Nếu trong thư mục custommap có nhiều hơn 2 map, vẽ preview của map thứ hai vào nút preview bên phải		*/
	else if (mapList.size() >= 2)
	{
		setMapPreviewInfo(0, 1);
	}

//	/*	Nếu trong thư mục custommap có nhiều hơn 2 map, vẽ preview của map thứ hai vào nút preview bên phải		*/
//	if (mapList.size() >= 2)
//	{
//		previewImage2 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(1));
//		mapRightName = wstringToCharArray(mapList.at(1));
//		std::ifstream ifs(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(1));
//		ifs >> mapRightPackage >> mapRightTime;
//		ifs.close();	
//}

	/*	Thiết lập trang hiện tại ban đầu là trang số 1	*/
	currentPage = 1;

	/*	Chọn background cho state từ ảnh tạm đã được chụp ngay trước đó từ MapGenerator state	*/
	background = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(L"tmp/play/sshot");
}

void MapSelectState::getMapList() //Nên gọi hàm này trong hàm tạo của state;
{
	/*	Tạo xâu để dùng cho quá trình duyệt thư mục	*/
	std::wstring tmp; 
	if (gamemode == 0) //chế độ campaign
	{
		tmp = CAMPAIGN_MAP_PREVIEW_FOLDER;
		tmp += L"*";
		std::cout << "ben nay";
	}
	else //chế độ custom
	{
		tmp = CUSTOM_MAP_PREVIEW_FOLDER;
		tmp += L"*";
	}
	/*	Đoạn duyệt thư mục này tham khảo 100%	*/
	/*	http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c	*/
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(tmp.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				mapList.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

void MapSelectState::setMapPreviewInfo(int image1, int image2)
{
	/*	Nếu các con trỏ ảnh đang trỏ tới những texture nào đó, cần destroy nó trước	*/
	if (previewImage1 != NULL)
	{
		SDL_DestroyTexture(previewImage1);
	}
	if (previewImage2 != NULL)
	{
		SDL_DestroyTexture(previewImage2);
	}


	if (mapLeftName != NULL)
	{
		delete[] mapLeftName;
	}

	if (mapRightName != NULL)
	{
		delete[] mapRightName;
	}

	mapLeftName = wstringToCharArray(mapList.at(image1));
	mapRightName = wstringToCharArray(mapList.at(image2));
	std::ifstream ifs;

	if (gamemode == 0) //chế độ campaign
	{
		previewImage1 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CAMPAIGN_MAP_PREVIEW_FOLDER) + mapList.at(image1));
		previewImage2 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CAMPAIGN_MAP_PREVIEW_FOLDER) + mapList.at(image2));
		ifs.open(std::wstring(CAMPAIGN_MAP_INFO_FOLDER) + mapList.at(image1));
		ifs >> mapLeftPackage >> mapLeftTime;
		ifs.close();
		ifs.open(std::wstring(CAMPAIGN_MAP_INFO_FOLDER) + mapList.at(image2));
		ifs >> mapRightPackage >> mapRightTime;
		ifs.close();

		char* tMapName = wstringToCharArray(mapList.at(image1));
		std::ifstream ifs(std::string("map/campaign/unlock/") + tMapName);
		delete tMapName;
		ifs >> checkUnlockLeft;
		ifs.close();
		
		tMapName = wstringToCharArray(mapList.at(image2));
		ifs.open(std::string("map/campaign/unlock/") + tMapName);
		delete tMapName;
		ifs >> checkUnlockRight;
		ifs.close();
	}

	else //chế độ custom
	{
		previewImage1 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(image1));
		previewImage2 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(image2));
		ifs.open(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(image1));
		ifs >> mapLeftPackage >> mapLeftTime;
		ifs.close();
		ifs.open(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(image2));
		ifs >> mapRightPackage >> mapRightTime;
		ifs.close();
	}
}

void MapSelectState::render()
{
	/*	Vẽ nền đằng sau	*/
	FrameWork::TextureManager::instance()->fwtm_renderTexture(background, 0, 0);

	/*	Vẽ khung dialog	*/
	FrameWork::TextureManager::instance()->fwtm_renderTexture(LOAD_BACKGROUND, 246, 20);

	/*	Vẽ các ảnh preview 	*/
	fw_Rectangle tmp_s, tmp_d1, tmp_d2;

	FrameWork::fw_setRectDimension(&tmp_s, 230, 0, 906, 768);

	if (previewImage1 != NULL)
	{
		FrameWork::fw_setRectDimension(&tmp_d1, 296, 340, 362, 307);
		FrameWork::TextureManager::instance()->fwtm_renderTexture(previewImage1, tmp_s, tmp_d1);
	}

	if (previewImage2 != NULL)
	{
		FrameWork::fw_setRectDimension(&tmp_d2, 708, 340, 362, 307);
		FrameWork::TextureManager::instance()->fwtm_renderTexture(previewImage2, tmp_s, tmp_d2);
	}

	/*	Vẽ các button	*/
	getCommandButtonManager()->renderButtons();

	/*	Vẽ map info	*/
	int leftNO = (currentPage - 1) * 2;
	int rightNO = (leftNO + 1) % mapList.size();
	if (mapList.size() >= 1)
	{
		FrameWork::FontLibrary::instance()->fwf_renderText("Name:", "solid", { 0, 0, 0, 255 }, 300, 280);
		FrameWork::FontLibrary::instance()->fwf_renderText(mapLeftName, "solid", { 0, 0, 0, 255 }, 400, 280);//tên map

		FrameWork::FontLibrary::instance()->fwf_renderText("Winning Score:", "solid", { 0, 0, 0, 255 }, 300, 230);
		FrameWork::FontLibrary::instance()->fwf_renderText(std::to_string(mapLeftPackage).c_str(), "solid", { 0, 0, 0, 255 }, 500, 230);//số hàng yêu cầu

		FrameWork::FontLibrary::instance()->fwf_renderText("Time:", "solid", { 0, 0, 0, 255 }, 300, 180);
		FrameWork::FontLibrary::instance()->fwf_renderText(std::to_string(mapLeftTime).c_str(), "solid", { 0, 0, 0, 255 }, 400, 180); //thời gian cho phép chơi
	}
	if (mapList.size() >= 2)
	{
		FrameWork::FontLibrary::instance()->fwf_renderText("Name:", "solid", { 0, 0, 0, 255 }, 712, 280);
		FrameWork::FontLibrary::instance()->fwf_renderText(mapRightName, "solid", { 0, 0, 0, 255 }, 812, 280);//tên map

		FrameWork::FontLibrary::instance()->fwf_renderText("Winning Score:", "solid", { 0, 0, 0, 255 }, 712, 230);
		FrameWork::FontLibrary::instance()->fwf_renderText(std::to_string(mapRightPackage).c_str(), "solid", { 0, 0, 0, 255 }, 912, 230);//số hàng yêu cầu

		FrameWork::FontLibrary::instance()->fwf_renderText("Time:", "solid", { 0, 0, 0, 255 }, 712, 180);
		FrameWork::FontLibrary::instance()->fwf_renderText(std::to_string(mapRightTime).c_str(), "solid", { 0, 0, 0, 255 }, 812, 180); //thời gian cho phép chơi
	}

	if (gamemode == 0)//neu o che do campaign, co the can ve cup
	{
		if (checkUnlockLeft)
		{
			/*	Ve cup trai	*/
			FrameWork::TextureManager::instance()->fwtm_renderTexture(STAR, 250, 350);
		}
		if (checkUnlockRight)
		{
			/*	Ve cup trai	*/
			FrameWork::TextureManager::instance()->fwtm_renderTexture(STAR, 662, 350);
		}
	}
}

MapSelectState::~MapSelectState()
{
	SDL_DestroyTexture(previewImage1);
	SDL_DestroyTexture(previewImage2);
	SDL_DestroyTexture(background);
}

bool MapSelectState::onExit()
{
	delete[] mapLeftName;
	delete[] mapRightName;

	return true;
}

bool MapSelectState::onEnter()
{
	FrameWork::InputHandler::instance()->fwi_resetCallback();
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(MapSelectState::handleLeftMouseClick));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(MapSelectState::moveEvent));

	return true;
}



void MapSelectState::update()
{

}

fw_Callback MapSelectState::buttonMapLeft()
{
	getCommandButtonManager()->setNonActiveButton(0);

	int imageNO = (currentPage - 1) * 2;
	
	if (gamemode == 0)
	{
		char* lMapName = wstringToCharArray(mapList.at(imageNO));
		std::ifstream ifs(std::string("map/campaign/unlock/") + lMapName);
		delete lMapName;
		int checkUnlock;
		ifs >> checkUnlock;
		ifs.close();
		if (checkUnlock == 0) return;
	}

	if (previewImage1 != NULL)
	{
		//Đoạn check exist nếu có thời gian thì viết sau

		char* buffer;

		if (gamemode == 0)//chế độ campaign
		{
			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/info");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/terrain");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/building");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/road");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/switcher");
			delete[] buffer;

			std::wofstream ofs("tmp/play/nextlv");
			ofs << mapList.at((imageNO + 1) % mapList.size());
			ofs.close();
		}

		else //chế độ custom
		{
			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/info");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/terrain");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/building");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/road");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/switcher");
			delete[] buffer;
		}

		isOnState = false;
		setNextState(PLAY_STATE);
	}
}

fw_Callback MapSelectState::buttonMapRight()
{
	getCommandButtonManager()->setNonActiveButton(1);

	int imageNO = ((currentPage - 1) * 2  + 1) % mapList.size();
	
	if (gamemode == 0)
	{
		char* lMapName = wstringToCharArray(mapList.at(imageNO));
		std::ifstream ifs(std::string("map/campaign/unlock/") + lMapName);
		delete lMapName;
		int checkUnlock;
		ifs >> checkUnlock;
		ifs.close();
		if (checkUnlock == 0) return;
	}

	if (previewImage2 != NULL)
	{
		//Đoạn check exist nếu có thời gian thì viết sau

		char* buffer;

		if (gamemode == 0)//chế độ campaign
		{
			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/info");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/terrain");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/building");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/road");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CAMPAIGN_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/switcher");
			delete[] buffer;

			std::wofstream ofs("tmp/play/nextlv");
			ofs << mapList.at((imageNO + 1) % mapList.size());
			ofs.close();
		}

		else //chế độ custom
		{
			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/info");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/terrain");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/building");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/road");
			delete[] buffer;

			buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)));
			copyFile(buffer, "tmp/play/switcher");
			delete[] buffer;
		}

		isOnState = false;
		setNextState(PLAY_STATE);
	}
}

fw_Callback MapSelectState::buttonPrevClick()
{
	getCommandButtonManager()->setNonActiveButton(2);

	int mapSize = mapList.size();

	/*	Nếu số map ít hơn 3 thì không cho ấn prev	*/
	if (mapSize < 3) return;

	if (mapSize % 2 == 1) // so map le
	{
		int pagesNumber = mapSize / 2 + 1;
		currentPage--;
		if (currentPage == 0)
			currentPage = pagesNumber;

		if (currentPage == pagesNumber) // la trang cuoi
		{
			setMapPreviewInfo((currentPage - 1) * 2, 0);
		}
		else
		{
			// 2 anh
			setMapPreviewInfo((currentPage - 1) * 2, (currentPage - 1) * 2 + 1);
		}
	}
	else // so map chan
	{
		int pagesNumber = mapSize / 2;

		currentPage = (currentPage - 1) % pagesNumber;
		if (currentPage == 0)
			currentPage = pagesNumber;

		setMapPreviewInfo((currentPage - 1) * 2, (currentPage - 1) * 2 + 1);
	}
}

fw_Callback MapSelectState::buttonCancelClick()
{
	getCommandButtonManager()->setNonActiveButton(3);

	isOnState = false;
	setNextState(BACK_STATE);
}

fw_Callback MapSelectState::buttonNextClick()
{
	getCommandButtonManager()->setNonActiveButton(4);

	int mapSize = mapList.size();

	/*	Nếu số map ít hơn 3 thì không cho ấn next	*/
	if (mapSize < 3) return;

	if (mapSize % 2 == 1)//so map la le
	{
		int pagesNumber = mapSize / 2 + 1;

		currentPage = (currentPage + 1) % pagesNumber;
		if (currentPage == 0)
			currentPage = pagesNumber;

		if (currentPage == pagesNumber) // la trang cuoi
		{
			// 1 anh
			setMapPreviewInfo((currentPage - 1) * 2, 0);
		}
		else
		{
			// 2 anh
			setMapPreviewInfo((currentPage - 1) * 2, (currentPage - 1) * 2 + 1);
		}
	}
	else //so map la chan
	{
		int pagesNumber = mapSize / 2;

		currentPage = (currentPage + 1) % pagesNumber;
		if (currentPage == 0)
			currentPage = pagesNumber;
		// 2 anh
		setMapPreviewInfo((currentPage - 1) * 2, (currentPage - 1) * 2 + 1);
	}
}


fw_Callback MapSelectState::moveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}

fw_Callback MapSelectState::handleLeftMouseClick()
{
	getCommandButtonManager()->browseArray_LeftClick();
}