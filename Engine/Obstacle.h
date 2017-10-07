#pragma once
#include "Graphics.h"

class Obstacle
{
public:
	void drawObstacle(Graphics& gr, int x, int y);
	void drawObstacle(Graphics& gr, int x, int y, int y_size);
	Obstacle();
	int x = 400;
	int y;
	int vy = 1;
	int x_size;
	int y_size;
	float speed;
private:

};