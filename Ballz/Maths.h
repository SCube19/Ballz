#pragma once
#include"Ball.h"

float distance(Ball& first, Ball& second);
float vectorLength(Vector2f& vec);
Vector2f normalize(Vector2f& inputV);
int sgn(float x);
float overlap(Ball& first, Ball& second);
Vector2f directionVector(Ball& first, Ball& second);