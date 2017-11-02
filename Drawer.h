#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <vector>
#include <map>

#ifndef _DRAWER_H_
#define _DRAWER_H_

//Enumeration which represent basic shapes
enum Shape { LINE, RECTANGLE, ELLIPSE };

//class for storing and drawing elements
class Drawer
{
public:
	//forwarding declaration of structure where object will be stored
	struct Object;
	//function definition to draw shapes
	typedef void (*PaintFunction)(HDC, Object);
	Drawer();
	~Drawer();
	//repaint all stored shapes
	void repaint(HDC);
	//draw object
	//if isRepaint == true do not store object otherwise draw and save it
	void draw(HDC, Object, bool isRepaint = false);
	//this method remove last object
	void undo(HDC);
	//this method assign which function will process some shape
	void setAction(Shape, PaintFunction);
	//getter-setter of current shape
	Shape& shape();
	//getter-setter of current color
	ULONG& color();
	//getter-setter of current with
	float& width();
private:
	//hear objects will be stored
	std::vector<Object> objects;
	//map shape to function
	std::map<Shape, PaintFunction> actions;
	//parameters for drawing
	Shape currentShape;
	unsigned long currentColor;
	float currentWidth;
};

struct Drawer::Object
{
	POINT point1;
	POINT point2;
	Shape shape;
	unsigned long color;
	float width;

	//create object
	//default - black point with width 1 on (0;0)
	Object(unsigned long clr = 0xff000000, float wdth = 1, unsigned short x = 0, unsigned short y = 0, unsigned short x1 = 0, unsigned short y1 = 0):
		point1{x,y}, point2{x1,y1}, color(clr), width(wdth)
	{}
};

#endif