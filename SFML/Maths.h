#pragma once
#include"Ball.h"

//Euklidean distance
float distance(const Ball& first, const Ball& second);

//Standard vector length
float vectorLength(const Vector2f& vec);

//Vector normalization
Vector2f normalize(const Vector2f& inputV);

//Signum funtion (<0 = -1, 0 = 0, >0 = 1)
int sgn(float x);

//Length of overlap
float overlap(const Ball& first, const Ball& second);

//
Vector2f directionVector(const Ball& first, const Ball& second);

//Standard dot product of two vectors
float dotProduct(const Vector2f& vec1, const Vector2f& vec2);