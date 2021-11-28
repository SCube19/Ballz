#include"Collisions.h"
#include"Ball.h"
#include"Maths.h"
#include <math.h>
#include <iostream>

namespace
{
	inline void resolveScreenCollision(Ball& ball, const Vector2f& newVelocity, float displacement)
	{
		ball.setVelocity(newVelocity);
		ball.move(Vector2f(displacement, Ballz::vectorLine(ball.getVelocity()) * displacement));
	}
}

///////////////////////////////////////SCREEN COLLISION/////////////////////////
void Ballz::screenCollisionResolution(Ball& ball, const RenderWindow& window)
{
	//left
	if (ball.getPosition().x - ball.getRadius() < 0)
		resolveScreenCollision(
			ball,
			Vector2f(-ball.getVelocity().x, ball.getVelocity().y),
			-ball.getPosition().x + ball.getRadius()
		);

	//right
	else if (ball.getPosition().x + ball.getRadius() > window.getSize().x)
		resolveScreenCollision(
			ball,
			Vector2f(-ball.getVelocity().x, ball.getVelocity().y),
			window.getSize().x - ball.getPosition().x - ball.getRadius()
		);
	
	//up
	if (ball.getPosition().y - ball.getRadius() < 0)
		resolveScreenCollision(
			ball,
			Vector2f(ball.getVelocity().x, -ball.getVelocity().y),
			-ball.getPosition().y + ball.getRadius()
			);

	//down
	else if (ball.getPosition().y + ball.getRadius() > window.getSize().y)
		resolveScreenCollision(
			ball,
			Vector2f(ball.getVelocity().x, -ball.getVelocity().y),
			window.getSize().y - ball.getPosition().y - ball.getRadius()
		);

	else
		ball.setScreenCollision(false);
}

/////////////////////STATIC COLLISION RESOLUTION///////////////////////////
void Ballz::staticCollisionResolution(Ball& first, Ball& second)
{
	//the actual vector we are using to push out the balls
	//it's vector along the overlap with length of half the overlap
	Vector2f moveVec = 0.5f * overlap(first, second) * normalize(directionVector(first, second));

	first.move(-moveVec);
	second.move(moveVec);
}

///////////////////DYNAMIC COLLISION RESOLUTION/////////////////////////
void Ballz::dynamicCollisionResolution(Ball& first, Ball& second)
{
	//EXPLAINATION:
	//During the collision we must consider the tangental collision line and the normal line being a line connecting centers
	//since the force is applied perpendicular to the surface of collision, velocity alongside the tangental will stay the same
	//so we can use dot product to determine that velocity, because normal response is where the forces come into play
	//that response must obey the conservation of momentum. The velocity at the end will be the sum of both responses
	

	Vector2f directionVec = directionVector(first, second);
	Vector2f normal = normalize(directionVec);
	Vector2f tangent(normal.y, -normal.x);

	float dotTan1 = dotProduct(first.getVelocity(), tangent);
	float dotTan2 = dotProduct(second.getVelocity(), tangent);

	float dotNorm1 = dotProduct(first.getVelocity(), normal);
	float dotNorm2 = dotProduct(second.getVelocity(), normal);

	float p1 = ((first.getMass() - second.getMass()) / (first.getMass() + second.getMass())) * dotNorm1 
		+ 2 * (second.getMass() / (first.getMass() + second.getMass()) ) * dotNorm2;
	float p2 = ((second.getMass() - first.getMass()) / (first.getMass() + second.getMass())) * dotNorm2 
		+ 2 * (first.getMass() / (first.getMass() + second.getMass())) * dotNorm1;

	first.setVelocity(Vector2f(tangent * dotTan1 + normal * p1));
	second.setVelocity(Vector2f(tangent * dotTan2 + normal * p2));
	first.play();
}