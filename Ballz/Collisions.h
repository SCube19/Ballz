#pragma once
#include"Ball.h"
#include <SFML/Audio.hpp>

//collision detection
bool areColliding(Ball& first, Ball& second);

//screen collision detection and resolution
void screenCollision(Ball& ball, RenderWindow& window);

//collision with mouse
bool mouseCollision(Ball& ball, Vector2i mousePos);

//static resolution of collision(unexpected behaviour when balls are not colliding)
void staticCollisionResolution(Ball& first, Ball& second);

//dynamic resolution / bouncing
void dynamicCollisionResolution(Ball& first, Ball& second);