#pragma once
#include"Ball.h"

//calculate distance between centers
float distance(Ball& first, Ball& second);

//get length of a vector
float vectorLength(Vector2f& vec);

//get normalized vector
Vector2f normalize(Vector2f& inputV);

//signum func
int sgn(float x);

//get overlap's length of two balls
float overlap(Ball& first, Ball& second);

//get vector from center of the first ball to the center of the second ball
Vector2f directionVector(Ball& first, Ball& second);