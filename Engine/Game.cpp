/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Obstacle.h"
#include "CustomShapes.h"
//#include <time.h>
#include <random>


Ball b;
Ball b2(400, 400, 10);
Paddle p;
const int num_obstacles = 8;
Obstacle *o = new Obstacle[num_obstacles];

std::random_device rd;
std::mt19937 rng(rd());

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
	
{
	p.y = gfx.ScreenHeight / 2;
	p.speed = 3;
	p.size = 50;

	// Code used to set the randomise seeds
	std::uniform_int_distribution<int> _y(10, gfx.ScreenHeight - 10 - maxObjectHeight);
	std::uniform_int_distribution<int> _vy(-3, 3);
	std::uniform_int_distribution<int> _ysize(30, maxObjectHeight - 30);


	for (int i = 0; i < num_obstacles; i++)
	{
		o[i].x = (i + 1) * obstacle_x_spacing;
		o[i].y = _y(rng);
		o[i].vy = _vy(rng);
		while (o[i].vy == 0)
		{
			o[i].vy = _vy(rng);
		}
		o[i].x_size = obstacle_x_size;
		o[i].y_size = _ysize(rng);
		
	}

	b.resetBall(gfx.ScreenWidth - 100, gfx.ScreenHeight / 2, 20);
	b2.resetBall(b2.x, b2.y);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		p.y-=p.speed;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		p.y+=p.speed;
	}

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!b.inMotion)
		{
			b.vx = -3;
			b.vy = 1.5;
			b.inMotion = true;
		}
	}


	if (b.y > (gfx.ScreenHeight-10) - (b.diameter/2) - abs(b.vy))
	{
		b.vy = -b.vy;
	}

	if (b.y < 10 + (b.diameter / 2) + abs(b.vy))
	{
		b.vy = -b.vy;
	}

	if (b.x > (gfx.ScreenWidth-10) - (b.diameter / 2) - abs(b.vx))
	{
		b.resetBall(gfx.ScreenWidth - 100, gfx.ScreenHeight / 2);
	}

	if (b.x < 10 + (b.diameter / 2) + abs(b.vx))
	{
		b.vx = -b.vx;
	}

	if (p.y < 10 + (p.size/2))
	{
		p.y = 10 + (p.size/2);
	}

	if (p.y > gfx.ScreenHeight - 10 - (p.size / 2))
	{
		p.y = gfx.ScreenHeight - 10 - (p.size / 2);
	}

	for (int i = 0; i < num_obstacles; i++)
	{
		if (o[i].y > gfx.ScreenHeight - 10 - o[i].y_size)
		{
			o[i].vy = -o[i].vy;
		}

		if (o[i].y < 10)
		{
			o[i].vy = -o[i].vy;
		}
	}


	if (Game::paddleHit())
	{
		b.vx = -b.vx;
		if (p.size > 20)
		{
			p.size = p.size - 1;
		}
		if (b.diameter > 10)
		{
			b.diameter = b.diameter - 1;
		}
	}

	for (int i = 0; i < num_obstacles; i++)
	{
		if (Game::obstacleHitx(i))
		{
			b.vx = -b.vx;
		}

		if (Game::obstacleHity(i))
		{
			b.vy = -b.vy;
		}

	}
	b.x += b.vx;
	b.y += b.vy;



	for (int i = 0; i < num_obstacles; i++)
	{
		o[i].y += o[i].vy;
	}

}

void Game::drawCourt()
{
	CustomShapes::drawLine(gfx, 10, 10, gfx.ScreenWidth - 10, 10, 255, 255, 255);
	CustomShapes::drawLine(gfx, 10, 10, 10, gfx.ScreenHeight - 10, 255, 255, 255);
	CustomShapes::drawLine(gfx, 10, gfx.ScreenHeight - 10, gfx.ScreenWidth - 10, gfx.ScreenHeight - 10, 255, 255, 255);
}

// Checks to see if the ball has hit the paddle
bool Game::paddleHit()
{
	return (b.vx > 0 &&
		b.x > (p.x) - (b.diameter / 2) &&
		b.x + b.diameter / 2 > p.x + 3 &&
		b.y - b.diameter / 2 < p.y + p.size / 2 &&
		b.y + b.diameter / 2 > p.y - p.size / 2);
}

bool Game::obstacleHitx(int i)
{

		if (b.vx > 0)
		{
			return (b.x >= (o[i].x) - (b.diameter / 2) &&
				b.x <= o[i].x - (b.diameter / 2) + b.vx &&
				b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
				b.y + b.diameter / 2 >= o[i].y);
		}
		else if (b.vx < 0)
		{
			return (b.x - b.diameter / 2 <= (o[i].x) + o[i].x_size &&
				b.x - b.diameter / 2 >= o[i].x + o[i].x_size + b.vx &&
				b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
				b.y + b.diameter / 2 >= o[i].y);
		}
		else
		{
			return false;
		}
}

bool Game::obstacleHity(int i)
{

		if (b.vy > 0)
		{
			return (b.y + b.diameter / 2 >= o[i].y &&
				b.y + b.diameter / 2 <= o[i].y + b.vy &&
				b.x + b.diameter / 2 >= o[i].x &&
				b.x - b.diameter / 2 <= o[i].x + o[i].x_size
				);
		}
		else if (b.vy < 0)
		{
			return (b.y - b.diameter / 2 <= o[i].y + o[i].y_size &&
				b.y - b.diameter / 2 >= o[i].y + o[i].y_size + b.vy &&
				b.x + b.diameter / 2 >= o[i].x &&
				b.x - b.diameter / 2 <= o[i].x + o[i].x_size
				);
		}
		else
		{
			return false;
		}
}

void Game::ComposeFrame()
{
	Game::drawCourt();
	b.drawCircle(gfx, b.x, b.y, b.diameter/2, 0,0,200);
	p.drawPaddle(gfx, p.y, p.size);
	for (int i = 0; i < num_obstacles; i++)
	{
		o[i].drawObstacle(gfx, o[i].x, o[i].y);
	}
}
