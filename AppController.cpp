#include "AppController.h"

AppController::AppController(INT cmd):
	cmdShow(cmd)
{

}

AppController::~AppController()
{
	for(std::vector<WindowController*>::iterator it = windows.begin(); it != windows.end(); ++it)
	{
		delete *it;
	}
}

void AppController::createWindow(HINSTANCE instance, WNDPROC callback, LPCWSTR WindowName)
{
	windows.push_back(new WindowController(instance, callback, WindowName));
	windows.back()->ShowWindow(cmdShow);
}

WindowController* AppController::getWindow(unsigned int i)
{
	if(windows.size() < i)
	{
		return windows[i];
	}
	return NULL;
}

int AppController::StartProcessingMessages()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}