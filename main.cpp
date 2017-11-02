#include "WindowController.h"
#include "AppController.h"
#include "Drawer.h"
#include "drawing_utils.h"

//create drawer instance
Drawer drawer;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//main application function
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	//set drawerdefault values
	drawer.shape() = LINE;
	drawer.color() = 0xff000000;
	drawer.width() = 5;
	//set function to process shapes
	drawer.setAction(LINE, &drawLine);
	drawer.setAction(ELLIPSE, &drawEllipse);
	drawer.setAction(RECTANGLE, &drawRectagle);
	//init app
	AppController app(iCmdShow);
	//create new window called "MyPaint"
	app.createWindow(hInstance, &WndProc, TEXT("MyPaint"));
	return app.StartProcessingMessages();
}  // WinMain


//temporary storage for clicked place
POINT p;
//temporary storage for previous object (do delete it whem mouse moved)
Drawer::Object prev;
//determine if rbutton is pressed
bool isPressed = false;
//function which receive app messages
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		drawer.repaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_RBUTTONDOWN:
	{
		//create, show and get users click on menu
		HMENU hPopupMenu = CreatePopupMenu();
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 1, L"Line");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 2, L"Ellipse");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 3, L"Rectangle");
		SetForegroundWindow(hWnd);
		switch (TrackPopupMenu(hPopupMenu, TPM_LEFTBUTTON | TPM_RETURNCMD | TPM_LEFTALIGN, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, hWnd, NULL))
		{
		case 1: drawer.shape() = LINE; break;
		case 2: drawer.shape() = ELLIPSE; break;
		case 3: drawer.shape() = RECTANGLE; break;
		}
		return 0;
	}
	case WM_MOUSEWHEEL:
		//process this action to increase/decrease width
		if (wParam & MK_CONTROL)
		{
			short direction = GET_WHEEL_DELTA_WPARAM(wParam);
			if (direction > 0) //scroll away from user
			{
				drawer.width()++;
			}
			else if (drawer.width() - 1 > 0) //scroll toward user
			{
				drawer.width()--;
			}
		}
		return 0;
	case WM_CHAR:
		//if pressed char == 'c' - show color pallete
		if (wParam == 'c')
		{
			CHOOSECOLOR cc;
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hWnd;
			cc.rgbResult = drawer.color();
			COLORREF acrCustClr[16];
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.Flags = CC_ELLIPSES;
			if (ChooseColor(&cc) == TRUE)
			{
				drawer.color() = 0xff000000 | (((cc.rgbResult & 0x0000ff) << 16) | (cc.rgbResult & 0xff0000) >> 16) | (cc.rgbResult & 0x00ff00);
			}
		}
		if (wParam == 'z')
		{
			HDC hdc = GetDC(hWnd);
			drawer.undo(hdc);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONDOWN:
		p.x = GET_X_LPARAM(lParam);
		p.y = GET_Y_LPARAM(lParam);
		isPressed = true;
		return 0;
	case WM_MOUSEMOVE:
		if (isPressed)
		{
			hdc = GetDC(hWnd);
			//set white color
			prev.color = 0xffffffff;
			//clear previos object
			drawer.draw(hdc, prev, true);
			//create structure of new object
			prev = Drawer::Object(drawer.color(), drawer.width(), p.x, p.y, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			//draw it
			drawer.draw(hdc, prev, true);
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		drawer.draw(hdc, Drawer::Object(drawer.color(), drawer.width(), p.x, p.y, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
		drawer.repaint(hdc);
		ReleaseDC(hWnd, hdc);
		prev = Drawer::Object(0xffffffff);
		isPressed = false;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc