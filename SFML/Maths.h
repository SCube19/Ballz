#pragma once
#include"Ball.h"

namespace Ballz
{
	//Euklidean distance
	float distance(const Ball& first, const Ball& second);

	//Standard vector length
	float vectorLength(const Vector2f& vec);

	//Vector normalization
	Vector2f normalize(const Vector2f& vec);

	//Signum funtion (<0 = -1, 0 = 0, >0 = 1)
	int sgn(float x);

	//Length of overlap
	float overlap(const Ball& first, const Ball& second);

	//
	Vector2f directionVector(const Ball& first, const Ball& second);

	//Standard dot product of two vectors
	float dotProduct(const Vector2f& vec1, const Vector2f& vec2);

	//return 'a' from ax + b that is parallel to the given [vec]
	float vectorLine(const Vector2f& vec);
}