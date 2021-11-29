#include "Physics.h"
#include "Maths.h"
#include "Collisions.h"

//////////////////GRAVITY////////////////////////////////////
void Ballz::gravity(Ball& first, Ball& second)
{
	const float G = 10000;

	Vector2f direction = directionVector(first, second);
	Vector2f force = normalize(direction) * (G * first.getMass() * second.getMass() / (distance(first, second) * distance(first, second)));

	first.move(force);
	second.move(-force);
}


/////////////////////////APPLY PHYSICS//////////////////////////
void Ballz::applyPhysics(std::vector<Ball>& ballz, RenderWindow& window, const int timeStep)
{
	//physics
	//for (int i = 0; i < ballz.size(); i++)
		//for (int j = i + 1; j < ballz.size(); j++)
			//gravity(ballz[i], ballz[j]);

	//position update
	for (auto& x : ballz)
	{
		x.move(timeStep);
	}

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