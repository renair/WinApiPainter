#include "drawing_utils.h"

using namespace Gdiplus;

//this file contains functions which
//going to precess different shapes

void drawLine(HDC hdc, Drawer::Object obj)
{
	Graphics graphics(hdc);
	graphics.DrawLine(&Pen(Color(obj.color), obj.width), obj.point1.x, obj.point1.y, obj.point2.x, obj.point2.y);
}

void drawEllipse(HDC hdc, Drawer::Object obj)
{
	Graphics graphics(hdc);
	graphics.DrawEllipse(&Pen(Color(obj.color), obj.width), obj.point1.x, obj.point1.y, obj.point2.x - obj.point1.x, obj.point2.y - obj.point1.y);
}

void drawRectagle(HDC hdc, Drawer::Object obj)
{
	Graphics graphics(hdc);
	graphics.DrawRectangle(&Pen(Color(obj.color), obj.width), obj.point1.x, obj.point1.y, obj.point2.x - obj.point1.x, obj.point2.y - obj.point1.y);
}