#include"Ball.h"
#include "Maths.h"
#include<iostream>

////////////////DISTANCE////////////////////////

float distance(Ball& first, Ball& second)
{
	float xdiff = first.getPosition().x - second.getPosition().x;
	float ydiff = first.getPosition().y - second.getPosition().y;

	return sqrt(xdiff * xdiff + ydiff * ydiff);
}

//////////////////////////VECTOR LENGTH//////////////////////////

float vectorLength(Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

///////////////////////////NORMALIZE//////////////////////////

Vector2f normalize(Vector2f& inputV)
{
	float l = vectorLength(inputV);
	if (l == 0)
		return Vector2f(0, 0);
	return Vector2f(inputV.x / l, inputV.y / l);
}

///////////////////SGN//////////////////////////////

int sgn(float x)
{
	return (0 < x) - (x < 0);
}

/////////////////////////OVERLAP/////////////////////////

float overlap(Ball& first, Ball& second)
{
	return first.getRadius() + second.getRadius() - distance(first, second);
}

////////////////////DIRECTION VECTOR/////////////////////////

Vector2f directionVector(Ball& first, Ball& second)
{
	return second.getPosition() - first.getPosition();
}

///////////////////DOT PRODUCT//////////////////////////

float dotProduct(Vector2f vec1, Vector2f vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}