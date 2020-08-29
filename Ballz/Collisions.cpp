#include"Collisions.h"
#include"Ball.h"
#include"Maths.h"
#include <math.h>

/////////////////////////////////ARE COLLIDING////////////////////////////////

bool areColliding(Ball& first, Ball& second)
{
	//|(x1 - x2)^2 + (y1 - y2)^2| <= (r1 + r2)^2 to avoid sqrt()
	return fabs((first.getPosition().x - second.getPosition().x) * (first.getPosition().x - second.getPosition().x)
		+ (first.getPosition().y - second.getPosition().y) * (first.getPosition().y - second.getPosition().y)) 
		<= (first.getRadius() + second.getRadius()) * (first.getRadius() + second.getRadius());
}

///////////////////////////////////////SCREEN COLLISION/////////////////////////

void screenCollision(Ball& ball)
{
	//left
	if (ball.getPosition().x - ball.getRadius() < 0)
	{
		ball.setVelocity(Vector2f(-ball.getVelocity().x, ball.getVelocity().y));

		float a = ball.getVelocity().y / ball.getVelocity().x;
		float displacement = -ball.getPosition().x + ball.getRadius();

		ball.move(Vector2f(displacement, a * displacement));
	}
	//right
	else if (ball.getPosition().x + ball.getRadius() > 1920)
	{
		ball.setVelocity(Vector2f(-ball.getVelocity().x, ball.getVelocity().y));

		float a = ball.getVelocity().y / ball.getVelocity().x;
		float displacement = 1920 - ball.getPosition().x - ball.getRadius();

		ball.move(Vector2f(displacement, a * displacement));
	}
	//up
	if (ball.getPosition().y - ball.getRadius() < 0)
	{
		ball.setVelocity(Vector2f(ball.getVelocity().x, -ball.getVelocity().y));

		float a = ball.getVelocity().y / ball.getVelocity().x;
		float displacement = -ball.getPosition().y + ball.getRadius();

		ball.move(Vector2f(a * displacement, displacement));
	}
	//down
	else if (ball.getPosition().y + ball.getRadius() > 1080)
	{
		ball.setVelocity(Vector2f(ball.getVelocity().x, -ball.getVelocity().y));

		float a = ball.getVelocity().y / ball.getVelocity().x;
		float displacement = 1080 - ball.getPosition().y - ball.getRadius();

		ball.move(Vector2f(a * displacement, displacement));
	}
	
}

/////////////////////STATIC COLLISION RESOLUTION///////////////////////////

void staticCollisionResolution(Ball& first, Ball& second)
{
	//length we should back the balls
	float displacement = 0.5f * overlap(first, second);

	//vector giving the line we are backing the balls
	Vector2f directionVec = directionVector(first, second);

	//the actual vector we are using to back the balls
	Vector2f moveVec = displacement * normalize(directionVec);

	first.move(-moveVec);
	second.move(moveVec);
}