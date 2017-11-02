#include "Drawer.h"

Drawer::Drawer()
{

}

Drawer::~Drawer()
{

}

void Drawer::repaint(HDC hdc)
{
	Shape curr = shape();
	for(std::vector<Object>::iterator it = objects.begin(); it != objects.end();it++)
	{
		shape() = it->shape;
		draw(hdc, *it, true);
	}
	shape() = curr;
}

void Drawer::setAction(Shape shape, PaintFunction funct)
{
	actions[shape] = funct;
}

void Drawer::draw(HDC hdc, Object params, bool isRepaint)
{
	std::map<Shape, PaintFunction>::iterator func = actions.find(shape());
	if (func != actions.end())
	{
		func->second(hdc, params);
		if (!isRepaint)
		{
			params.shape = shape();
			objects.push_back(params);
		}
	}
}

void Drawer::undo(HDC hdc)
{
	if (objects.size() > 0)
	{
		Object params = objects.back();
		objects.pop_back();
		params.color = 0xffffffff;
		std::map<Shape, PaintFunction>::iterator func = actions.find(shape());
		if (func != actions.end())
		{
			func->second(hdc, params);
			repaint(hdc);
		}
	}
}

Shape& Drawer::shape()
{
	return currentShape;
}

ULONG& Drawer::color()
{
	return currentColor;
}
float& Drawer::width()
{
	return currentWidth;
}
