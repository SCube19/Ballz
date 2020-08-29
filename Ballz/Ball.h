#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
	float mass;
	float radius;
	Vector2f velocity;
	Vector2f position;
	Color color;

public:

	//default constructor 
	Ball();
	//customizable constructor
	Ball(float radius, float mass, Vector2f initVelocity, Vector2f initPosition);
	//draw func
	void draw(RenderWindow& window, CircleShape& circle, VertexArray line);
	//real-time move using velocity
	void move(Time elapsed);
	//fixed value move
	void move(Vector2f displacement);

	//getters & setters
	Vector2f getVelocity();
	void setVelocity(Vector2f newVel);
	float getRadius();
	Vector2f getPosition();
	void setColor(Color newColor);
	float getMass();
};