#pragma once
#include "Ball.h"

namespace Ballz
{
	//Moves ballz according to Newton's law of gravity
	void gravity(Ball& first, Ball& second);
	
	//Aplies all available physics laws 
	void applyPhysics(std::vector<Ball>& ballz, RenderWindow& window, const int timeStep);
}