#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "FrameWork.h"
#include "GameState.h"

class SaveState : public GameState
{
private:
	unsigned int selectedButton;

	std::string textbox1String;
	std::string textbox2String;
	std::string textbox3String;
	
	bool copyFile(const char *SRC, const char* DEST) {
		std::ifstream src(SRC, std::ios::binary);
		std::ofstream dest(DEST, std::ios::binary);
		dest << src.rdbuf();
		return src && dest;
	}

	SDL_Texture* background;

public:
	bool onEnter();
	bool onExit();
	virtual void update();
	virtual void render();

	SaveState();
	~SaveState();

	void nameTextboxClick();
	void receivingNumberTextboxClick();
	void timeLimitTextboxClick();
	void buttonOkClick();
	void buttonCancelClick();
	
	fw_Callback mouseMoveHandle();
	fw_Callback leftMouseClickHandle();
	fw_Callback keyPressHandle();

};

#endif