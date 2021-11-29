#include "Physics.h"
#include "Maths.h"
#include "Collisions.h"
#include <math.h>
#include <iostream>
#include <algorithm>

//////////////////GRAVITY////////////////////////////////////
void Ballz::gravity(Ball& first, Ball& second)
{
	const float G = 6.67;

	Vector2f force = normalize(directionVector(first, second)) * 
		(G * first.getMass() * second.getMass() / std::powf(distance(first, second), 2));

	//std::cout << "force: " << (force).x << " " << (force).y << std::endl;
	//std::cout << "first acc: " << (force/first.getMass()).x << " " << (force / first.getMass()).y << std::endl;
	//std::cout << "second acc: " << (-force / second.getMass()).x << " " << (-force / second.getMass()).y << std::endl;
	first.accelerate(force / first.getMass());
	second.accelerate(-force / second.getMass());
}


/////////////////////////APPLY PHYSICS//////////////////////////
void Ballz::applyPhysics(std::vector<Ball>& ballz, RenderWindow& window, const int timeStep)
{

	//physics
	for (int i = 0; i < ballz.size(); i++)
	{
		for (int j = i + 1; j < ballz.size(); j++)
		{
			gravity(ballz[i], ballz[j]);
		}
	}

	//position update
	for (auto& x : ballz)
	{
		x.move(timeStep);
	}

	std::for_each(ballz.begin(), ballz.end(), [](Ball& ball) {ball.deaccelerate(); });

	//screen collisions detection and resolution
	for (auto& x : ballz)
	{
		screenCollisionResolution(x, window);
	}

	//vector of pairs of collided balls
	std::vector<std::pair<Ball&, Ball&>> collidedBallz;

	//static collisions
	for (auto i = 0; i < ballz.size(); i++)
	{
		for (auto j = 0; j < ballz.size(); j++)
		{
			if (i != j && Ballz::areColliding(ballz[i], ballz[j]))
			{
				staticCollisionResolution(ballz[i], ballz[j]);
				std::pair<Ball&, Ball&> collisionPair(ballz[i], ballz[j]);
				collidedBallz.push_back(collisionPair);
			}
		}
	}

	//dynamic collision resolution
	for (auto& x : collidedBallz)
		dynamicCollisionResolution(x.first, x.second);
}