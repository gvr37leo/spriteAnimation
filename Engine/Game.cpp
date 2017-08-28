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
#include "Surface.h"
#include "Rect.h"
#include "AnimatedSprite.h"
#include "AnimState.h"
#include <chrono>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
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
}


Surface img("scot.bmp");
std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
void Game::ComposeFrame()
{
	//std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	//std::chrono::duration<double> elapsed_seconds = now - start;
	//double seconds = elapsed_seconds.count();
	//Rect sz(V2i(0, 0), V2i(gfx.ScreenWidth, gfx.ScreenHeight));

	//AnimatedSprite anim(&img, V2i(108, 140), std::vector<V2i>{
	//		V2i(0,0), V2i(1, 0), V2i(2, 0), V2i(3, 0), V2i(4, 0), V2i(5, 0), V2i(6, 0), V2i(7, 0)
	//	});
	//108-140
	//wnd.mouse.GetPosX(), wnd.mouse.GetPosY()
	//anim.Draw(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), (int)(seconds * 10) % 8, sz, gfx);
	//gfx.DrawSprite(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(),Rect(V2i(64,96),V2i(32,48)), sz, img);

	Animator animator;
	AnimState running;
	AnimState jumping;

	Event jumpEvent;
	Transition run2jump(jumping, jumpEvent);

	Event fall;
	Transition jump2run(running, fall);

	running.transitions.push_back(run2jump);
	jumping.transitions.push_back(jump2run);
	animator.currentState = running;
	

}
