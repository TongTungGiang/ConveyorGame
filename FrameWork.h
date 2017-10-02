#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <iostream>
#include <functional>
#include <memory>
#include <SDL/SDL_syswm.h>
#include <Windows.h>
#include "Definition.h"
#include "SoundManager.h"

#include "Vector2.h"//Just for Converter functions, delete this after this project

#include "matrix.h"//Just for Converter functions, delete this after this projects
#include <map>

#define fw_Rectangle SDL_Rect
#define fw_Image SDL_Surface
#define fw_Texture SDL_Texture

#define fw_getFunctionAddress(f) std::bind(&f, this)

typedef void fw_Callback;

enum event_type
{
	FW_EVENT_QUIT,
	FW_EVENT_LEFT_MOUSE_BUTTON_UP,
	FW_EVENT_LEFT_MOUSE_BUTTON_DOWN,
	FW_EVENT_RIGHT_MOUSE_BUTTON_UP,
	FW_EVENT_RIGHT_MOUSE_BUTTON_DOWN,
	FW_EVENT_MIDDLE_MOUSE_BUTTON_UP,
	FW_EVENT_MIDDLE_MOUSE_BUTTON_DOWN,
	FW_EVENT_MOUSE_MOVE
};

namespace FrameWork
{

	class Window
	{
	private:

		static Window* singleton;

		static SDL_Window* p_window;
		static SDL_Renderer* p_renderer;

		static bool isCreated;

		static int windowWidth;
		static int windowHeight;

		Window() {};

	public:
		static Window* instance()
		{
			if (singleton == NULL)
			{
				singleton = new Window;
			}
			return singleton;
		}

		void fww_initialize();

		void fww_createWindow(const char* title, int xPosition, int yPosition, int width, int height);

		int fww_getWidth();
		int fww_getHeight();

		void fww_setClearColor(int red, int green, int blue, int alpha);

		void fww_clearScreen();
		void fww_drawScreen();

		void fww_captureScreen(char* savepath);

		HWND fww_getWindowHandle();

		unsigned int fww_displayMessageBox(wchar_t *title, wchar_t *content, unsigned int msgBoxType);

		SDL_Renderer* fww_getWindowRenderer();

		void fww_destroy();
	};

	class Timer
	{
	private:
		static Timer* singleton;
		Timer() {};

	public:
		static Timer* instance()
		{
			if (!singleton)
			{
				singleton = new Timer();
			}
			return singleton;
		}

		unsigned int fwt_getTime();
		void fwt_destroy();
	};

	class InputHandler
	{
	private:
		static  InputHandler* singleton;

		static int xMouse;
		static int yMouse;

		static bool isStringCapturing;
		static std::string receptedCharacters;
		static std::string* stringPointer;
		static unsigned int maxStringLength;

		static std::function<void()> quit_callback;
		static std::function<void()> leftMouseButtonsUp_callback;
		static std::function<void()> leftMouseButtonsDown_callback;
		static std::function<void()> rightMouseButtonsUp_callback;
		static std::function<void()> rightMouseButtonsDown_callback;
		static std::function<void()> middleMouseButtonsUp_callback;
		static std::function<void()> middleMouseButtonsDown_callback;
		static std::function<void()> mouseMove_callback;

		InputHandler() {};

	public:
		static InputHandler* instance()
		{
			if (!singleton)
			{
				singleton = new InputHandler();
			}
			return singleton;
		}

		void fwi_initialize();

		/*
		Lấy tọa độ con trỏ chuột trong cửa sổ chương trình.

		Các tham số:
		-	x: con trỏ tới vùng nhớ nhận giá trị tọa độ theo trục x
		-	y: con trỏ tới vùng nhớ nhận giá trị tọa độ theo trục y
		*/
		void fwi_getMousePosition(int* x, int* y);

		/*
		Thiết lập callback function ứng với các sự kiện chuột, bàn phím, ...
		phục vụ cho việc thực thi của hàm fwi_PollEvent().

		Các tham số
		-	event_type: loại sự kiện (được định nghĩa bởi các hằng có tiền tố FW_EVENT_)
		-	function_pointer: con trỏ tới hàm sẽ được thiết lập làm callback function.

		CHÚ Ý:
		-	Hàm được thiết lập làm callback function phải có kiểu là void,
		không được có bất kỳ tham số nào.
		-	Thiết lập lại callback function ứng với một sự kiện sẽ thay thế function
		được thiết lập trước lần đó.
		-	Để đơn giản, sử dụng macro fw_getFunctionAddress(f) cho đối số ứng với
		function_pointer, với f là tên của hàm được thiết lập làm callback function
		(hàm này phải là hàm thành viên của class chứa object gọi đến macro này).
		*/
		//void fwi_setCallbackFunction(unsigned int event_type, std::function<fw_Callback()>  const &function_pointer);
		void fwi_setCallbackFunction(unsigned int event_type, std::function<void()> function_pointer);

		/*
		Thực hiện duyệt toàn bộ hàng đợi sự kiện và gọi các callback function tương ứng
		đã được thiết lập bởi hàm fwi_setCallbackFunction.

		Hàng đợi sự kiện chứa tất cả các sự kiện xảy ra từ lần gọi hàm này trước đó.

		Các sự kiện bao gồm:
		-	phím chuột bị nhấn/nhả
		-	bàn phím bị nhấn/nhả
		-	cửa sổ chương trình bị đóng lại
		*/
		void fwi_PollEvent();

		void fwi_startStringCapture(std::string receptedCharacters);
		void fwi_setCapturedString(std::string* str, int maxStringLength);
		void fwi_stopStringCapture();
		void fwi_resetCallback();
		void fwi_destroy();
	};

	class TextureManager
	{
	private:
		static TextureManager* singleton;
		TextureManager() {};
		static unsigned int iterator_texture;
		static std::vector <fw_Texture*> *textureArray;

	public:
		static TextureManager* instance()
		{
			if (singleton == NULL)
			{
				singleton = new TextureManager;
			}
			return singleton;
		}

		void fwtm_initialize();
		unsigned int fwtm_createTextureFromFile(std::string filename);
		fw_Texture* fwtm_createTempTextureFromFile(std::wstring filename);

		void fwtm_renderTexture(unsigned int textureID, int x, int y);
		void fwtm_renderTexture(unsigned int textureID, int x, int y, float ratio);
		void fwtm_renderTexture(unsigned int textureID, fw_Rectangle source, fw_Rectangle dest);

		void fwtm_renderTexture(fw_Texture* texture, int x, int y);
		void fwtm_renderTexture(fw_Texture* texture, fw_Rectangle source, fw_Rectangle dest);
		void fwtm_destroy();

		~TextureManager() {};
	};

	class FontLibrary
	{

	private:

		static FontLibrary* sInstance;

		std::map < std::string, TTF_Font* > fonts;

		FontLibrary() {};

	public:

		static FontLibrary* instance(){
			if (sInstance == 0)
			{
				sInstance = new FontLibrary();
				return sInstance;
			}
			return sInstance;
		}

		void fwf_initialize();
		void fwf_destroy();
		bool fwf_loadFont(std::string fileName, std::string id, int size);
		void fwf_renderText(const char* renderingString, std::string fontID, SDL_Color textColor, int x, int y);

	};

	class Converter
	{
	private:
		static Matrix <float> *transformMatrix;
		static Converter* singleton;
		Converter() {};

	public:
		static Converter* instance()
		{
			if (!singleton)
			{
				singleton = new Converter;
			}
			return singleton;
		}

		void fwc_initialize();
		void fwc_destroy();
		Vector2i fwc_logicCoordToGraphicCoord(Vector2f lgcCoord);
		Vector2f fwc_graphicCoordToLogicCoord(Vector2i grpCoord);

	};

	static void fw_setRectDimension(fw_Rectangle* rect, int x, int y, int width, int height)
	{
		rect->x = x;
		rect->y = y;
		rect->w = width;
		rect->h = height;
	}


	static bool fw_frameworkInitialize()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		{
			Window::instance()->fww_initialize();
			InputHandler::instance()->fwi_initialize();
			Converter::instance()->fwc_initialize();
			TextureManager::instance()->fwtm_initialize();
			FontLibrary::instance()->fwf_initialize();
			return true;
		}
		return false;
	}

	static void fw_frameworkTerminate()
	{
		FontLibrary::instance()->fwf_destroy();
		InputHandler::instance()->fwi_destroy();
		Timer::instance()->fwt_destroy();
		Converter::instance()->fwc_destroy();
		TextureManager::instance()->fwtm_destroy();
		Window::instance()->fww_destroy();
		SDL_Quit();
	}
}

#endif