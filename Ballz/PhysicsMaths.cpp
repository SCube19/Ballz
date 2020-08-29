#include"Maths.h"
#include"Ball.h"
#include<iostream>


///////////////////DISTANCE////////////////////////////////////

float distance(Ball& first, Ball& second)
{
	//euklidean 2d distance
	float xdiff = first.getPosition().x - second.getPosition().x;
	float ydiff = first.getPosition().y - second.getPosition().y;

	return sqrt(xdiff * xdiff + ydiff * ydiff);
}

//////////////////////////VECTOR LENGTH///////////////////////////

float vectorLength(Vector2f& vec)
{
	//pitagorean theorem 
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

///////////////////////////NORMALIZE///////////////////////////////

Vector2f normalize(Vector2f& inputV)
{
	float l = vectorLength(inputV);
	if (l == 0)
		return Vector2f(0, 0);
	return Vector2f(inputV.x / l, inputV.y / l);
}

///////////////////////SGN//////////////////////////

int sgn(float x)
{
	return (0 < x) - (x < 0);
}

//////////////////////////////////////OVERLAP/////////////////////////////

float overlap(Ball& first, Ball& second)
{
	//r1 + r2 - d
	return first.getRadius() + second.getRadius() - distance(first, second);
}

//////////////////////////////DIRECTION VECTOR////////////////////////////

Vector2f directionVector(Ball& first, Ball& second)
{
	return second.getPosition() - first.getPosition();
}