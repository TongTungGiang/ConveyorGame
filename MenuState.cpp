#include "MenuState.h"
#include "CommandButtonManager.h"

MenuState::MenuState() : GameState()
{
	stateID = MENU_STATE;

	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::menuToPlay), Vector2i(400, 490), Vector2i(400, 70), PLAYGAME, PLAYGAME_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::menuToMapGenerator), Vector2i(400, 400), Vector2i(400, 70), MAP_GENERATOR, MAP_GENERATOR_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::menuToInstruction), Vector2i(400, 310), Vector2i(400, 70), INSTRUCTION, INSTRUCTION_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::menuToCredit), Vector2i(400, 220), Vector2i(400, 70), CREDIT, CREDIT_ACTIVE);
	getCommandButtonManager()->createButton(fw_getFunctionAddress(MenuState::menuToQuit), Vector2i(400, 130), Vector2i(400, 70), QUIT, QUIT_ACTIVE);

	SoundManager::Instance()->playMusic("menu", -1);
}

MenuState::~MenuState()
{

}

void MenuState::update()
{

}

void MenuState::render()
{
	FrameWork::TextureManager::instance()->fwtm_renderTexture(MENU_BACKGROUND, 0, 0);
	getCommandButtonManager()->renderButtons();
}

bool MenuState::onEnter()
{
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_LEFT_MOUSE_BUTTON_DOWN, fw_getFunctionAddress(MenuState::handleLeftMouseClick));
	FrameWork::InputHandler::instance()->fwi_setCallbackFunction(FW_EVENT_MOUSE_MOVE, fw_getFunctionAddress(MenuState::moveEvent));
	//isOnMenuState = true;
	return true;

};

bool MenuState::onExit()
{

	return true;
};


fw_Callback MenuState::menuToPlay()
{
	isOnState = false;
	setNextState(MODESELECT_STATE);
}

fw_Callback MenuState::menuToQuit()
{
	isOnState = false;
	setNextState(QUIT_STATE);
}

fw_Callback MenuState::menuToMapGenerator()
{
	isOnState = false;
	setNextState(MAPGENERATOR_STATE);

}
fw_Callback MenuState::menuToInstruction()
{
	isOnState = false;
	setNextState(INSTRUCTION_STATE);
}
fw_Callback MenuState::menuToCredit()
{
	isOnState = false;
	setNextState(CREDIT_STATE);
}

fw_Callback MenuState::moveEvent()
{
	getCommandButtonManager()->browseArray_Point();
}

fw_Callback MenuState::handleLeftMouseClick()
{
	getCommandButtonManager()->browseArray_LeftClick();
}