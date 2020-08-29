#pragma once
#include"Ball.h"

//collision detection
bool areColliding(Ball& first, Ball& second);

//screen collision detection and resolution
void screenCollision(Ball& ball);

//static resolution of collision(unexpected behaviour when balls are not colliding)
void staticCollisionResolution(Ball& first, Ball& second);