#pragma once
#include "Graphics.h"

class Paddle
{
public:
	void drawPaddle(Graphics& gr, int y, int size);
	int x = 750;
	int y;
	int vx;
	static constexpr int vy = 1;
	int size;
	float speed;
private:

};

