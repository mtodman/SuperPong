#include "Obstacle.h"

Obstacle::Obstacle()
{

};

void Obstacle::drawObstacle(Graphics& gr, int _x, int _y)
{
	for (int x = _x; x <= _x + x_size; x++)
	{
		for (int y = _y; y < _y + y_size; y++)
		{
			gr.PutPixel(x, y, 0, 255, 0);
		}
	}
}

void Obstacle::drawObstacle(Graphics & gr, int _x, int _y, int y_size)
{
	for (int x = _x; x <= _x + x_size; x++)
	{
		for (int y = _y; y < _y + y_size; y++)
		{
			gr.PutPixel(x, y, 0, 255, 0);
		}
	}

}
