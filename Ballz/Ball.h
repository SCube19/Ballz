#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Ball
{
	float mass;
	float radius;
	Vector2f velocity;
	Vector2f position;
	Color color;
	Sound hit;
	bool screenCollision;

public:

	//default constructor 
	Ball(SoundBuffer& sound);
	//customizable constructor
	Ball(float radius, float mass, Vector2f initVelocity, Vector2f initPosition, SoundBuffer& sound);
	//draw func
	void draw(RenderWindow& window, CircleShape& circle, VertexArray line);
	//real-time move using velocity
	void move(Time elapsed);
	//fixed value move
	void move(Vector2f displacement);
	void play();

	//getters & setters
	Vector2f getVelocity();
	void setVelocity(Vector2f newVel);
	float getRadius();
	Vector2f getPosition();
	void setColor(Color newColor);
	float getMass();
	void setPosition(Vector2f newPos);
	bool screenCollided();
	void setScreenCollision(bool state);
};