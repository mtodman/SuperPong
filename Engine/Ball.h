#pragma once
#include "Graphics.h"

class Ball
{
public:
	Ball(int _x, int _y);
	Ball(int _x, int _y, int _dia);
	Ball();
	void drawBall(Graphics& gr, float x, float y, int dia, bool filled);
	void drawCircle(Graphics & gr, int ox, int oy, int rad, int r, int g, int b);
	void resetBall(int _x, int _y, int _dia);
	void resetBall(int _x, int _y);
	float x;
	float y;
	float vx;
	float vy;
	int diameter;
	int radius;
	float speed;
	bool inMotion;
private:
};
