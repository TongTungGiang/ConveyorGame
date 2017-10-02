#include "LoadState.h"
#include <string>

#define CUSTOM_MAP_INFO_FOLDER L"map/custommap/info/"
#define CUSTOM_MAP_PREVIEW_FOLDER L"map/custommap/preview/"
#define CUSTOM_MAP_TERRAIN_FOLDER L"map/custommap/terrain/"
#define CUSTOM_MAP_BUILDING_FOLDER L"map/custommap/building/"
#define CUSTOM_MAP_ROAD_FOLDER L"map/custommap/road/"
#define CUSTOM_MAP_SWITCHER_FOLDER L"map/custommap/switcher/"

LoadState::LoadState() : GameState()
{
	stateID = LOAD_STATE;

	/*	Tạo các button với các command function đã được định nghĩa tương ứng với chức năng của button	*/
	getCommandButtonManager()->createButton(fw_getFunctionAddress(LoadState::buttonMapLeft), Vector2i(296, 340), Vector2i(362, 307), NONE_ACTIVEBUTTON, ACTIVEBUTTON);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(LoadState::buttonMapRight), Vector2i(708, 340), Vector2i(362, 307), NONE_ACTIVEBUTTON, ACTIVEBUTTON);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(LoadState::buttonPrevClick), Vector2i(300, 75), Vector2i(150, 50), PREV, PREV_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(LoadState::buttonCancelClick), Vector2i(558, 50), Vector2i(250, 50), CANCEL, CANCEL_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(LoadState::buttonNextClick), Vector2i(916, 75), Vector2i(150, 50), NEXT, NEXT_ACTIVE);

	/*	Duyệt thư mục custommap/info và lấy danh sách các map	*/
	getMapList();

	previewImage1 = NULL;
	previewImage2 = NULL;

	mapLeftName = NULL;
	mapRightName = NULL;

	/*	Nếu trong thư mục custommap có nhiều hơn 1 map, vẽ preview của map đầu tiên vào nút preview bên trái	*/
	if (mapList.size() >= 1)
	{
		previewImage1 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(0));
		mapLeftName = wstringToCharArray(mapList.at(0));
		std::ifstream ifs(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(0));
		ifs >> mapLeftPackage >> mapLeftTime;
		ifs.close();
	}

	/*	Nếu trong thư mục custommap có nhiều hơn 2 map, vẽ preview của map thứ hai vào nút preview bên phải		*/
	if (mapList.size() >= 2)
	{
		previewImage2 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(1));
		mapRightName = wstringToCharArray(mapList.at(1));
		std::ifstream ifs(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(1));
		ifs >> mapRightPackage >> mapRightTime;
		ifs.close();
	}

	/*	Thiết lập trang hiện tại ban đầu là trang số 1	*/
	currentPage = 1;

	/*	Chọn background cho state từ ảnh tạm đã được chụp ngay trước đó từ MapGenerator state	*/
	background = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(L"tmp/load/sshot");
}

void LoadState::getMapList() //Nên gọi hàm này trong hàm tạo của state;
{
	/*	Tạo xâu để dùng cho quá trình duyệt thư mục	*/
	std::wstring tmp = CUSTOM_MAP_PREVIEW_FOLDER;
	tmp += L"*";

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

void LoadState::setMapPreviewInfo(int image1, int image2)
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

	
	previewImage1 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(image1));

	if (mapLeftName != NULL)
	{
		delete[] mapLeftName;
	}
	mapLeftName = wstringToCharArray(mapList.at(image1));

	std::ifstream ifs(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(image1));
	ifs >> mapLeftPackage >> mapLeftTime;
	ifs.close();

	previewImage2 = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(std::wstring(CUSTOM_MAP_PREVIEW_FOLDER) + mapList.at(image2));

	if (mapRightName != NULL)
	{
		delete[] mapRightName;
	}
	mapRightName = wstringToCharArray(mapList.at(image2));

	ifs.open(std::wstring(CUSTOM_MAP_INFO_FOLDER) + mapList.at(image2));
	ifs >> mapRightPackage >> mapRightTime;
	ifs.close();
}

void LoadState::render()
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
}

LoadState::~LoadState()
{
	SDL_DestroyTexture(previewImage1);
	SDL_DestroyTexture(previewImage2);
	SDL_DestroyTexture(background);
}
bool LoadState::onExit()
{
	delete[] mapLeftName;
	delete[] mapRightName;

	return true;
}

bool LoadState::onEnter()
{
	FrameWork::InputHandler::instance()->fwi_resetCallback();
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(LoadState::handleLeftMouseClick));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(LoadState::moveEvent));

	return true;
}


void LoadState::update()
{
	
}

fw_Callback LoadState::buttonMapLeft()
{ 
	getCommandButtonManager()->setNonActiveButton(0);

	int imageNO = (currentPage - 1) * 2;

	if (previewImage1 != NULL)
	{
		//Đoạn check exist nếu có thời gian thì viết sau

		char* buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)) );
		copyFile(buffer, "tmp/load/info");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)) );
		copyFile(buffer, "tmp/load/terrain");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)) );
		copyFile(buffer, "tmp/load/building");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)) );
		copyFile(buffer, "tmp/load/road");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)) );
		copyFile(buffer, "tmp/load/switcher");
		delete[] buffer;
		
		std::ofstream ofs("tmp/load/cancelflag");
		ofs << 0;
		ofs.close();

		isOnState = false;
		setNextState(BACK_STATE);
	}
}

fw_Callback LoadState::buttonMapRight()
{
	getCommandButtonManager()->setNonActiveButton(1);

	int imageNO;
	int mapNum = mapList.size();
	if (mapNum % 2 == 1 && currentPage == (mapNum / 2 + 1)) //so map le va den trang cuoi
	{
		imageNO = 0;
	}
	else
	{
		imageNO = (currentPage - 1) * 2 + 1;
	}
	if (previewImage2 != NULL)
	{
		//Đoạn check exist nếu có thời gian thì viết sau

		char* buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_INFO_FOLDER) + std::wstring(mapList.at(imageNO)));
		copyFile(buffer, "tmp/load/info");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_TERRAIN_FOLDER) + std::wstring(mapList.at(imageNO)));
		copyFile(buffer, "tmp/load/terrain");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_BUILDING_FOLDER) + std::wstring(mapList.at(imageNO)));
		copyFile(buffer, "tmp/load/building");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_ROAD_FOLDER) + std::wstring(mapList.at(imageNO)));
		copyFile(buffer, "tmp/load/road");
		delete[] buffer;

		buffer = wstringToCharArray(std::wstring(CUSTOM_MAP_SWITCHER_FOLDER) + std::wstring(mapList.at(imageNO)));
		copyFile(buffer, "tmp/load/switcher");
		delete[] buffer;

		std::ofstream ofs("tmp/load/cancelflag");
		ofs << 0;
		ofs.close();

		isOnState = false;
		setNextState(BACK_STATE);
	}
}

fw_Callback LoadState::buttonPrevClick()
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

		currentPage = (currentPage + 1) % pagesNumber;
		if (currentPage == 0)
			currentPage = pagesNumber;

		setMapPreviewInfo((currentPage - 1) * 2, (currentPage - 1) * 2 + 1);
	}
}

fw_Callback LoadState::buttonCancelClick()
{
	getCommandButtonManager()->setNonActiveButton(3);

	std::ofstream ofs("tmp/load/cancelflag");
	ofs << 1;
	ofs.close();

	isOnState = false;
	setNextState(BACK_STATE);
}

fw_Callback LoadState::buttonNextClick()
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


fw_Callback LoadState::moveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}
fw_Callback LoadState::handleLeftMouseClick()
{
	getCommandButtonManager()->browseArray_LeftClick();
}