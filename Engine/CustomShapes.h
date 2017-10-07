#pragma once
#include "Graphics.h"

static class CustomShapes
{
public:
	//CustomShapes();
	//~CustomShapes();
	static void drawLine(Graphics& gr, int x1, int y1, int x2, int y2, int r, int g, int b);

	void drawCircle(Graphics & gr, int ox, int oy, int rad, int r, int g, int b);

private:
};

//CustomShapes::CustomShapes()
//{
//}
//
//CustomShapes::~CustomShapes()
//{
//}