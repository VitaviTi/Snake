#pragma once
#include <iostream>

#include "Window.h"
#include <gl/GL.h> 

namespace snake {

class Game
{
	float coords_snake[8] = { 0.0f, 0.0f,  0.0f, 0.1f,  0.1f, 0.1f,  0.1f, 0.0f };
	window::Window* window_game;
private:
	bool death();
	void playbutton();
	bool press_button(float mincoordx, float maxcoordx, float mincoordy, float maxcoordy);
	void testsnake();
public:
	bool game;

	Game(window::Window* window_0);
	void home_screen();
	void game_screen();
};

} /* namespace snake */
