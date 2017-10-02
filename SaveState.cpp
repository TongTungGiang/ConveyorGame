#include "SaveState.h"
#include <ctype.h>

SaveState::SaveState()
{
	stateID = SAVE_STATE;

	getCommandButtonManager()->createButton(fw_getFunctionAddress(SaveState::nameTextboxClick), Vector2i(600, 460), Vector2i(400, 50), TEXTBOX, TEXTBOX_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(SaveState::receivingNumberTextboxClick), Vector2i(600, 355), Vector2i(400, 50), TEXTBOX, TEXTBOX_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(SaveState::timeLimitTextboxClick), Vector2i(600, 250), Vector2i(400, 50), TEXTBOX, TEXTBOX_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(SaveState::buttonOkClick), Vector2i(400, 120), Vector2i(250, 50), SAVE, SAVE_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(SaveState::buttonCancelClick), Vector2i(730, 120), Vector2i(250, 50), CANCEL, CANCEL_ACTIVE);

	textbox1String = "";
	textbox2String = "";
	textbox3String = "";

	/*
	SDL_Surface* tmp = SDL_LoadBMP("tmp/save/sshot");
	background = SDL_CreateTextureFromSurface(FrameWork::Window::instance()->fww_getWindowRenderer(), tmp);
	SDL_FreeSurface(tmp);
	*/
	background = FrameWork::TextureManager::instance()->fwtm_createTempTextureFromFile(L"tmp/save/sshot");

}

SaveState::~SaveState()
{
	SDL_DestroyTexture(background);
}

bool SaveState::onExit()
{
	return true;
}

bool SaveState::onEnter()
{
	FrameWork::InputHandler::instance()->fwi_resetCallback();

	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(SaveState::leftMouseClickHandle));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(SaveState::mouseMoveHandle));
	isOnState = true;
	return true;
}

void SaveState::update()
{

}

void SaveState::render()
{
	//SDL_RenderCopy(FrameWork::Window::instance()->fww_getWindowRenderer(), background, NULL, NULL);

	/*	Vẽ nền đằng sau	*/
	FrameWork::TextureManager::instance()->fwtm_renderTexture(background, 0, 0);

	/*	Vẽ khung dialog	*/
	FrameWork::TextureManager::instance()->fwtm_renderTexture(SAVEDIALOG, 300, 100);

	/*	Vẽ các button bao gồm 2 button preview, 1 button prev, 1 button cancel, 1 button next	*/
	getCommandButtonManager()->renderButtons();

	/*	Viết nhãn cho các button prev, cancel, next	*/
	int x0, y0, x1, y1, x2, y2;
	x0 = getCommandButtonManager()->getButtonOriginCoordinates(0).getX();
	y0 = getCommandButtonManager()->getButtonOriginCoordinates(0).getY();
	x1 = getCommandButtonManager()->getButtonOriginCoordinates(1).getX();
	y1 = getCommandButtonManager()->getButtonOriginCoordinates(1).getY();
	x2 = getCommandButtonManager()->getButtonOriginCoordinates(2).getX();
	y2 = getCommandButtonManager()->getButtonOriginCoordinates(2).getY();

	FrameWork::FontLibrary::instance()->fwf_renderText(textbox1String.c_str(),
		"solid", { 0, 0, 0, 255 }, x0 + 20, y0 + 10);
	FrameWork::FontLibrary::instance()->fwf_renderText(textbox2String.c_str(),
		"solid", { 0, 0, 0, 255 }, x1 + 20, y1 + 10);
	FrameWork::FontLibrary::instance()->fwf_renderText(textbox3String.c_str(),
		"solid", { 0, 0, 0, 255 }, x2 + 20, y2 + 10);
}

void SaveState::nameTextboxClick()
{
	selectedButton = 1;
	FrameWork::InputHandler::instance()->fwi_startStringCapture("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_");
	FrameWork::InputHandler::instance()->fwi_setCapturedString(&textbox1String, 16);
}

void SaveState::receivingNumberTextboxClick()
{
	selectedButton = 2;
	FrameWork::InputHandler::instance()->fwi_startStringCapture("0123456789");
	FrameWork::InputHandler::instance()->fwi_setCapturedString(&textbox2String, 4);
}

void SaveState::timeLimitTextboxClick()
{
	selectedButton = 3;
	FrameWork::InputHandler::instance()->fwi_startStringCapture("0123456789");
	FrameWork::InputHandler::instance()->fwi_setCapturedString(&textbox3String, 4);
}

void SaveState::buttonOkClick()
{
	getCommandButtonManager()->setNonActiveButton(3);

	if (textbox1String == "" || textbox2String == "" || textbox3String == "") return;

	int tmp1, tmp2;
	tmp1 = atoi(textbox2String.c_str());
	tmp2 = atoi(textbox3String.c_str());
	std::ofstream ofs("map/custommap/info/" + textbox1String);
	ofs << tmp1 << " " << tmp2;
	ofs.close();

	std::string tmp = "map/custommap/preview/" + textbox1String;
	copyFile("tmp/save/sshot", tmp.c_str());

	tmp = "map/custommap/terrain/" + textbox1String;
	copyFile("tmp/save/terrain", tmp.c_str());

	tmp = "map/custommap/building/" + textbox1String;
	copyFile("tmp/save/building", tmp.c_str());

	tmp = "map/custommap/road/" + textbox1String;
	copyFile("tmp/save/road", tmp.c_str());

	tmp = "map/custommap/switcher/" + textbox1String;
	copyFile("tmp/save/switcher", tmp.c_str());

	isOnState = false;
	setNextState(BACK_STATE);
	
}

void SaveState::buttonCancelClick()
{
	getCommandButtonManager()->setNonActiveButton(4);

	isOnState = false;
	setNextState(BACK_STATE);
}

fw_Callback SaveState::mouseMoveHandle()
{
	getCommandButtonManager()->browseArray_Point();
}

fw_Callback SaveState::leftMouseClickHandle()
{
	selectedButton = 0;
	getCommandButtonManager()->browseArray_LeftClick();
}


	
