#include "FrameWork.h"
using FrameWork::Window;

Window* Window::singleton = NULL;

SDL_Window* Window::p_window = NULL;

SDL_Renderer* Window::p_renderer = NULL;

bool Window::isCreated = false;

int Window::windowWidth = 0;

int Window::windowHeight = 0;

void Window::fww_initialize()
{
	singleton = NULL;
	isCreated = false;
}

void Window::fww_createWindow(const char* title, int xPosition, int yPosition, int width, int height)
{
	if (isCreated == true) return;
	p_window = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
	p_renderer = SDL_CreateRenderer(p_window, -1, 0);
	windowWidth = width;
	windowHeight = height;
	isCreated = true;
}

int Window::fww_getWidth()
{
	return windowWidth;
}

int Window::fww_getHeight()
{
	return windowHeight;
}

void Window::fww_setClearColor(int red, int green, int blue, int alpha)
{
	SDL_SetRenderDrawColor(p_renderer, red, green, blue, alpha);
}

void Window::fww_clearScreen()
{
	SDL_RenderClear(p_renderer);
}

void Window::fww_drawScreen()
{
	SDL_RenderPresent(p_renderer);
}

void Window::fww_captureScreen(char* savepath)
{
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_RenderReadPixels(p_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

	SDL_SaveBMP(sshot, savepath);

	SDL_FreeSurface(sshot);
}

HWND Window::fww_getWindowHandle()
{
	SDL_SysWMinfo sysInfo;
	SDL_VERSION(&sysInfo.version);

	SDL_GetWindowWMInfo(p_window, &sysInfo);

	return sysInfo.info.win.window;
}

SDL_Renderer* Window::fww_getWindowRenderer()
{
	return p_renderer;
}

void Window::fww_destroy()
{
	/*	Delete the created window	*/
	SDL_DestroyRenderer(p_renderer);
	SDL_DestroyWindow(p_window);

	/*	Free all pointers	*/

	isCreated = false;
	//p_renderer = NULL;
	//p_window = NULL;

	delete singleton;
	//singleton = NULL;
}

unsigned int Window::fww_displayMessageBox(wchar_t *title, wchar_t *content, unsigned int msgBoxType)
{

	int msgboxID = MessageBox(
		fww_getWindowHandle(),
		(LPCWSTR)content,
		(LPCWSTR)title,
		msgBoxType);

	return msgboxID;
}