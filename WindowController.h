#include <windows.h>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#include <wingdi.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#ifndef _WINDOW_CONTROLLER_
#define _WINDOW_CONTROLLER_

//This class is a convinient window container
//Which provides methos for creating window, showing and destruction
class WindowController
{
public:
	//constructow which create window
	WindowController(HINSTANCE instance, WNDPROC callback, LPCWSTR WindowName);
	//destructow which deinitialize window
	~WindowController();
	//show window with special parameters
	void ShowWindow(INT iCmdShow);
	//begin dispatching messages only for this window
	int StartProcessingMessage();
private:
	//close operations which not allowed for window
	WindowController& operator=(const WindowController&) {};
	WindowController(const WindowController&) {};
	//private system variables
	WNDCLASS appConfiguretion;
	HINSTANCE appInstance;
	HWND windowDescriptor;
	MSG msg;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	WNDPROC eventCallback;
};
#endif // !_WINDOW_CONTROLLER_
