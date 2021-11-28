#include"Ball.h"
#include "Maths.h"
#include<iostream>

////////////////DISTANCE////////////////////////
float Ballz::distance(const Ball& first, const Ball& second)
{
	float xdiff = first.getPosition().x - second.getPosition().x;
	float ydiff = first.getPosition().y - second.getPosition().y;

	return sqrt(xdiff * xdiff + ydiff * ydiff);
}

//////////////////////////VECTOR LENGTH//////////////////////////
float Ballz::vectorLength(const Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

///////////////////////////NORMALIZE//////////////////////////
Vector2f Ballz::normalize(const Vector2f& inputV)
{
	float l = vectorLength(inputV);
	if (l == 0)
		return Vector2f(0, 0);
	return Vector2f(inputV.x / l, inputV.y / l);
}

///////////////////SGN//////////////////////////////
int Ballz::sgn(float x)
{
	return (0 < x) - (x < 0);
}

/////////////////////////OVERLAP/////////////////////////
float Ballz::overlap(const Ball& first, const Ball& second)
{
	return first.getRadius() + second.getRadius() - distance(first, second);
}

////////////////////DIRECTION VECTOR/////////////////////////
Vector2f Ballz::directionVector(const Ball& first, const Ball& second)
{
	return second.getPosition() - first.getPosition();
}

///////////////////DOT PRODUCT//////////////////////////
float Ballz::dotProduct(const Vector2f& vec1, const Vector2f& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

/////////////////VECTOR LINE////////////////////////////
float Ballz::vectorLine(const Vector2f& vec)
{
	return vec.x == 0 ? 0 : vec.y / vec.x;
}