#include "Physics.h"
#include "Maths.h"

/*void gravity(Ball& first, Ball& second)
{
	const float G = 10000;

	Vector2f direction = directionVector(first, second);
	Vector2f force = normalize(direction) * (G * first.getMass() * second.getMass() / (distance(first, second) * distance(first, second)));

	first.move(force);
	second.move(-force);
}*/

void Ballz::gravity(Ball& first, Ball& second)
{
	const float G = 10000;

	Vector2f direction = directionVector(first, second);
	Vector2f force = normalize(direction) * (G * first.getMass() * second.getMass() / (distance(first, second) * distance(first, second)));

	first.move(force);
	second.move(-force);
}