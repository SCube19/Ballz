#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace 
{
	//Structure to optimize memory (static members were not allowed)
	//Later the addition of custom textures is planned
	struct BallTexture
	{
		CircleShape shape;
		VertexArray line;

		BallTexture() : line(LinesStrip, 2)
		{
			shape.setOutlineColor(Color::White);
			shape.setOutlineThickness(1);
			line[0].color = Color::Green;
			line[1].color = Color::Green;
		}
	};
}

class Ball
{
	//Physical variables
	float mass;
	float radius;
	Vector2f velocity;
	Vector2f position;
	Vector2f acceleration;

	//State variables
	bool screenCollision;

	//Additional variables
	Color color;
	Sound hit;

public:

	//Default constructor 
	Ball(const SoundBuffer& sound);

	//Customizable constructor
	Ball(float radius, float mass, const Vector2f& initVelocity, const Vector2f& initPosition, const SoundBuffer& sound);

	//Draw function
	//A ball is drawn on [window] based on its internal variables
	void draw(RenderWindow& window) const;

	//Real-time move using velocity
	void move(const Time& elapsed);
	//fixed value move
	void move(const Vector2f& displacement);

	//Plays sound bound to a ball
	void play();

	//Getters & Setters
	Vector2f getVelocity() const;
	float getRadius() const;
	Vector2f getPosition() const;
	float getMass() const;
	Vector2f getAcceleration() const;
	bool screenCollided() const;
	

	void setVelocity(const Vector2f& newVel);
	void setColor(const Color& newColor);
	void setPosition(const Vector2f& newPos);
	void setScreenCollision(bool state);
	void setAcceleration(const Vector2f& newAcc);
	void accelerate(const Vector2f& acc);
};