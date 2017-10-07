#include "Paddle.h"

void Paddle::drawPaddle(Graphics& gr, int y, int size)
{
	for (int a = x - 3; a <= x; a++)
	{
		for (int b = y - (size / 2); b < y+(size/2); b++)
		{
			gr.PutPixel(a, b, 255, 0, 0);
		}
	}
}
