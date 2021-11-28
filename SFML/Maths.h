#pragma once
#include"Ball.h"

namespace Ballz
{
	//Euklidean distance
	//Returns distance between [first] and [second]
	inline float distance(const Ball& first, const Ball& second)
	{
		float xdiff = first.getPosition().x - second.getPosition().x;
		float ydiff = first.getPosition().y - second.getPosition().y;

		return std::sqrt(xdiff * xdiff + ydiff * ydiff);
	}

	//Euklidian vector length
	//Returns length of [vec]
	inline float vectorLength(const Vector2f& vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	//Vector normalization
	//Returns vector of length one with same direction as [vec]
	inline Vector2f normalize(const Vector2f& inputV)
	{
		return vectorLength(inputV) == 0 ? Vector2f(0, 0) : (inputV / vectorLength(inputV));
	}

	//Signum funtion (<0 = -1, 0 = 0, >0 = 1)
	//If [x] < 0 returns -1 
	//If [x] > 0 returns 1
	//0 otherwise
	inline int sgn(float x)
	{
		return (0 < x) - (x < 0);
	}

	//Length of overlap
	//Returns overlap measured along the line connecting [first] and [second] centers
	inline float overlap(const Ball& first, const Ball& second)
	{
		return first.getRadius() + second.getRadius() - distance(first, second);
	}

	//Vector from center to center
	//Returns vector from center of [first] to the center of [second]
	inline Vector2f directionVector(const Ball& first, const Ball& second)
	{
		return second.getPosition() - first.getPosition();
	}

	//Dot product of two vectors
	//Returns [vec1]^T[vec2]
	inline float dotProduct(const Vector2f& vec1, const Vector2f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	//Angle of a vector
	//Returns 'a' from ax + b that is parallel to the given [vec]
	inline float vectorLine(const Vector2f& vec)
	{
		return vec.x == 0 ? 0 : vec.y / vec.x;
	}
}