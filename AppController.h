#include<Windows.h>
#include<vector>
#include "WindowController.h"

#ifndef _APP_CONTROLLER_
#define _APP_CONTROLLER_

//Base app controller
//This class represent container for windows
class AppController
{
private:
	//hear will be stored messages for dispatching
	MSG msg;
	//how we will show window (see WindowController::ShowWindow)
	INT cmdShow;
	//storage for windows
	std::vector<WindowController*> windows;
public:
	//init controller
	AppController(INT cmd);
	//delete all created windows on destruction
	~AppController();
	//create new window with app instance,
	//function to dispatch messages and window title
	void AppController::createWindow(HINSTANCE instance, WNDPROC callback, LPCWSTR WindowName);
	//return pointer to dynamically created WindowController instance
	WindowController* getWindow(unsigned int i);
	//begin dispath message for current thread
	int StartProcessingMessages();
};

#endif