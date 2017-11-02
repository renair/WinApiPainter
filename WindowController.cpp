#include "WindowController.h"

WindowController::WindowController(HINSTANCE instance, WNDPROC callback, LPCWSTR WindowName):
	appInstance(instance), eventCallback(callback)
{
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	appConfiguretion.style = CS_HREDRAW | CS_VREDRAW;
	appConfiguretion.lpfnWndProc = eventCallback;
	appConfiguretion.cbClsExtra = 0;
	appConfiguretion.cbWndExtra = 0;
	appConfiguretion.hInstance = appInstance;
	appConfiguretion.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	appConfiguretion.hCursor = LoadCursor(NULL, IDC_ARROW);
	appConfiguretion.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	appConfiguretion.lpszMenuName = NULL;
	appConfiguretion.lpszClassName = WindowName;

	RegisterClass(&appConfiguretion);

	windowDescriptor = CreateWindow(
		WindowName,			 // window class name
		WindowName,			 // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT,		 // initial x position
		CW_USEDEFAULT,       // initial y position
		CW_USEDEFAULT,       // initial x size
		CW_USEDEFAULT,       // initial y size
		NULL,                // parent window handle
		NULL,                // window menu handle
		appInstance,         // program instance handle
		NULL);               // creation parameters
}

WindowController::~WindowController()
{
	GdiplusShutdown(gdiplusToken);
}

void WindowController::ShowWindow(INT iCmdShow)
{
	::ShowWindow(windowDescriptor, iCmdShow);
	UpdateWindow(windowDescriptor);
}

int WindowController::StartProcessingMessage()
{
	while (GetMessage(&msg, windowDescriptor, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}