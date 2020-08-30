#include"Collisions.h"
#include"Ball.h"
#include"Maths.h"
#include <math.h>
#include <iostream>

/////////////////////////////////ARE COLLIDING////////////////////////////////

bool areColliding(Ball& first, Ball& second)
{
	//|(x1 - x2)^2 + (y1 - y2)^2| <= (r1 + r2)^2 to avoid sqrt()
	return fabs((first.getPosition().x - second.getPosition().x) * (first.getPosition().x - second.getPosition().x)
		+ (first.getPosition().y - second.getPosition().y) * (first.getPosition().y - second.getPosition().y)) 
		<= (first.getRadius() + second.getRadius()) * (first.getRadius() + second.getRadius());
}

///////////////////////////////////////SCREEN COLLISION/////////////////////////
//propably can be shortened

void screenCollision(Ball& ball, RenderWindow& window)
{
	//left
	if (ball.getPosition().x - ball.getRadius() < 0)
	{
		ball.setVelocity(Vector2f(-ball.getVelocity().x, ball.getVelocity().y));

		float a = 0;
		if (ball.getVelocity().x != 0)
			a = ball.getVelocity().y / ball.getVelocity().x;

		float displacement = -ball.getPosition().x + ball.getRadius();

		ball.move(Vector2f(displacement, a * displacement));
		std::cout << "Collision\n";
		
	}
	//right
	else if (ball.getPosition().x + ball.getRadius() > window.getSize().x)
	{
		ball.setVelocity(Vector2f(-ball.getVelocity().x, ball.getVelocity().y));

		float a = 0;
		if (ball.getVelocity().x != 0)
			a = ball.getVelocity().y / ball.getVelocity().x;

		float displacement = 1920 - ball.getPosition().x - ball.getRadius();

		ball.move(Vector2f(displacement, a * displacement));
		std::cout << "Coll\n";
	}
	//up
	if (ball.getPosition().y - ball.getRadius() < 0)
	{
		ball.setVelocity(Vector2f(ball.getVelocity().x, -ball.getVelocity().y));

		float a = 0;
		if (ball.getVelocity().y != 0)
			a = ball.getVelocity().x / ball.getVelocity().y;

		float displacement = -ball.getPosition().y + ball.getRadius();

		ball.move(Vector2f(displacement * a, displacement));
		
		std::cout << "Coll\n";
	}
	//down
	else if (ball.getPosition().y + ball.getRadius() > window.getSize().y)
	{
		ball.setVelocity(Vector2f(ball.getVelocity().x, -ball.getVelocity().y));

		float a = 0;
		if (ball.getVelocity().y != 0)
			a = ball.getVelocity().x / ball.getVelocity().y;

		float displacement = 1080 - ball.getPosition().y - ball.getRadius();

		ball.move(Vector2f(displacement * a, displacement));
		
		std::cout << "Coll\n";
	}
	else
		ball.setScreenCollision(false);
}

//////////////////////////MOUSE COLLISION//////////////////

bool mouseCollision(Ball& ball, Vector2i mouse)
{
	return fabs((ball.getPosition().x - (float)mouse.x) * (ball.getPosition().x - (float)mouse.x)
		+ (ball.getPosition().y - (float)mouse.y) * (ball.getPosition().y - (float)mouse.y))
		<= ball.getRadius() * ball.getRadius();
}

/////////////////////STATIC COLLISION RESOLUTION///////////////////////////

void staticCollisionResolution(Ball& first, Ball& second)
{
	float displacement = 0.5f * overlap(first, second);
	
	//vector giving the line we are backing the balls
	Vector2f directionVec = directionVector(first, second);

	//the actual vector we are using to back the balls
	Vector2f moveVec = displacement * normalize(directionVec);

	first.move(-moveVec);
	second.move(moveVec);
}

///////////////////DYNAMIC COLLISION RESOLUTION/////////////////////////

void dynamicCollisionResolution(Ball& first, Ball& second)
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

	float p1 = ((first.getMass() - second.getMass()) / (first.getMass() + second.getMass())) * dotNorm1 + 2 * (second.getMass() / (first.getMass() + second.getMass()) ) * dotNorm2;
	float p2 = ((second.getMass() - first.getMass()) / (first.getMass() + second.getMass())) * dotNorm2 + 2 * (first.getMass() / (first.getMass() + second.getMass())) * dotNorm1;

	first.setVelocity(Vector2f(tangent * dotTan1 + normal * p1));
	second.setVelocity(Vector2f(tangent * dotTan2 + normal * p2));
	first.play();
	
}