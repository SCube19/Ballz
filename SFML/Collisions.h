#pragma once
#include"Ball.h"
#include <SFML/Audio.hpp>

namespace Ballz
{
	//collision detection
	//true if [first] and [second] intersect
	//false otherwise
	inline bool areColliding(const Ball& first, const Ball& second)
	{
		//|(x1 - x2)^2 + (y1 - y2)^2| <= (r1 + r2)^2 because its more accurate than sqrt() formula
		return std::abs((first.getPosition().x - second.getPosition().x) * (first.getPosition().x - second.getPosition().x)
			+ (first.getPosition().y - second.getPosition().y) * (first.getPosition().y - second.getPosition().y))
			<= (first.getRadius() + second.getRadius()) * (first.getRadius() + second.getRadius());
	}

	//collision with mouse
	//true if mouse cursor is inside [ball]
	//false otherwise
	inline bool mouseCollision(const Ball& ball, const Vector2i& mouse)
	{
		return std::abs((ball.getPosition().x - (float)mouse.x) * (ball.getPosition().x - (float)mouse.x)
			+ (ball.getPosition().y - (float)mouse.y) * (ball.getPosition().y - (float)mouse.y))
			<= ball.getRadius() * ball.getRadius();
	}

	//screen collision detection and resolution
	//pushes [ball] so it fits boundaries of [window]
	void screenCollisionResolution(Ball& ball, const RenderWindow& window);

	//static resolution of collision 
	//unexpected behaviour when balls are not colliding
	//pushes out [first] and [second] half the amount of their overlap
	void staticCollisionResolution(Ball& first, Ball& second);

	//dynamic resolution / bouncing
	//applies force to [first] and [second] based on preservation of momentum
	void dynamicCollisionResolution(Ball& first, Ball& second);
}