#include"Ball.h"
#include<iostream>

float distance(Ball& first, Ball& second)
{
	float xdiff = first.getPosition().x - second.getPosition().x;
	float ydiff = first.getPosition().y - second.getPosition().y;

	return sqrt(xdiff * xdiff + ydiff * ydiff);
}

float vectorLength(Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vector2f normalize(Vector2f& inputV)
{
	float l = vectorLength(inputV);
	if (l == 0)
		return Vector2f(0, 0);
	return Vector2f(inputV.x / l, inputV.y / l);
}

int sgn(float x)
{
	return (0 < x) - (x < 0);
}

float overlap(Ball& first, Ball& second)
{
	return first.getRadius() + second.getRadius() - distance(first, second);
}

Vector2f directionVector(Ball& first, Ball& second)
{
	return second.getPosition() - first.getPosition();
}