#include "Ball.h"

Ball::Ball(int _x, int _y)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = 20;
	radius = diameter / 2;
	inMotion = false;
}

Ball::Ball(int _x, int _y, int _dia)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = _dia;
	radius = diameter / 2;
	inMotion = false;
}

Ball::Ball()   //Default Constructor
{
}


void Ball::drawBall(Graphics& gr, float x, float y, int dia, bool filled)
{
	for (int a = (int)x - (dia / 2); a < (int)x + (dia / 2); a++)
	{
		for (int b = (int)y - (dia / 2); b < (int) y + (dia / 2); b++)
		{
		gr.PutPixel(a, b, 0, 0, 255);
		}
	}
}

void Ball::drawCircle(Graphics& gr, int ox, int oy, int rad, int r, int g, int b)
{
	for (int x = -rad; x < rad; x++)
	{
		int height = (int)sqrt(rad * rad - x * x);


		for (int y = -height; y < height; y++)
			gr.PutPixel(x + ox, y + oy, r, g, b);
	}
}

void Ball::resetBall(int _x, int _y, int _dia)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	diameter = _dia;
	radius = diameter / 2;
	inMotion = false;
}

void Ball::resetBall(int _x, int _y)
{
	x = _x;
	y = _y;
	vx = 0;
	vy = 0;
	inMotion = false;
}
