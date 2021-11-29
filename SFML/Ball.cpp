#include "Ball.h"
#include "Maths.h"

namespace 
{
	//blueprint shapes for every object
	BallTexture texture;
}

///////////////////////CONSTRUCTORS//////////////////////////////////
Ball::Ball(const SoundBuffer& sound) : 
	mass(1.0f), radius(50.0f), 
	velocity(Vector2f((float)(sqrt(2) / (float)4), (float)(-sqrt(2) / (float)4))),
	position(Vector2f(500, 500)), 
	color(Color::Transparent), hit(sound), screenCollision(false)
{
}

Ball::Ball(float radius, float mass, const Vector2f& initVelocity, const Vector2f& initPosition, const SoundBuffer& sound):
	radius(radius), mass(mass), velocity(initVelocity), position(initPosition), hit(sound), screenCollision(false)
{
}


///////////////////////////DRAW///////////////////////////////////////
void Ball::draw(RenderWindow& window) const
{
	//change blueprint shape to match this object
	texture.shape.setRadius(radius);
	texture.shape.setOrigin(radius, radius);
	texture.shape.setPosition(position);
	texture.shape.setFillColor(color);
	if (screenCollision)
		texture.shape.setFillColor(Color::Red);

	window.draw(texture.shape);

	texture.line[0].position = texture.shape.getPosition();
	texture.line[1].position = texture.line[0].position + Ballz::normalize(velocity) * radius;
	window.draw(texture.line);
}

///////////////////////////////////////MOVE/////////////////////////////////////////
void Ball::move(const int miliseconds)
{
	position += Vector2f(velocity.x * miliseconds, velocity.y * miliseconds);
}

void Ball::move(const Vector2f& displacement)
{
	position += displacement;
}

///////////////////PLAY///////////////////////////////
void Ball::play()
{
	hit.play();
}
////////////////////////GETTERS////////////////////////////
Vector2f Ball::getVelocity() const
{
	return velocity;
}

float Ball::getRadius() const
{
	return radius;
}

Vector2f Ball::getPosition() const
{
	return position;
}

float Ball::getMass() const
{
	return mass;
}

Vector2f Ball::getAcceleration() const
{
	return acceleration;
}

bool Ball::screenCollided() const
{
	return screenCollision;
}

///////////////////////SETTERS////////////////////////////
void Ball::setVelocity(const Vector2f& newVel)
{
	velocity = newVel;
}

void Ball::setColor(const Color& newColor)
{
	color = newColor;
}

void Ball::setPosition(const Vector2f& newPos)
{
	position = newPos;
}

void Ball::setScreenCollision(bool state)
{
	screenCollision = state;
}

void Ball::setAcceleration(const Vector2f& newAcc)
{
	acceleration = newAcc;
}

void Ball::accelerate(const Vector2f& acc)
{
	acceleration += acc;
}