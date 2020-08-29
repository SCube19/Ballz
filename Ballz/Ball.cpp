#include "Ball.h"
#include "Maths.h"

///////////////////////CONSTRUCTORS//////////////////////////////////

Ball::Ball()
{
	mass = 1.0f;
	radius = 50.0f;
	velocity.x = (float)(sqrt(2) / (float)4);
	velocity.y = (float)(-sqrt(2) / (float)4);
	position.x = 500;
	position.y = 500;
	color = Color::Transparent;
}

Ball::Ball(float radius, float mass, Vector2f initVelocity, Vector2f initPosition)
{
	this->radius = radius;
	this->mass = mass;
	velocity = initVelocity;
	position = initPosition;
}


///////////////////////////DRAW///////////////////////////////////////

void Ball::draw(RenderWindow& window, CircleShape& circle, VertexArray line)
{
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(position);
	circle.setFillColor(color);

	window.draw(circle);

	line[0].position = circle.getPosition();
	line[1].position = line[0].position + normalize(velocity) * radius;
	window.draw(line);

	
}

///////////////////////////////////////MOVE/////////////////////////////////////////

void Ball::move(Time elapsed)
{
	position += Vector2f(velocity.x * elapsed.asMilliseconds(), velocity.y * elapsed.asMilliseconds());
}

void Ball::move(Vector2f displacement)
{
	position += displacement;
}

////////////////////////GETTERS////////////////////////////

Vector2f Ball::getVelocity()
{
	return velocity;
}

float Ball::getRadius()
{
	return radius;
}

Vector2f Ball::getPosition()
{
	return position;
}

///////////////////////SETTERS////////////////////////////

void Ball::setVelocity(Vector2f newVel)
{
	velocity = newVel;
}

void Ball::setColor(Color newColor)
{
	color = newColor;
}
