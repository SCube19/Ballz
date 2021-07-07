#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

namespace
{
	//Structure to optimize memory (static members were not allowed)
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
	//physical variables
	float mass;
	float radius;
	Vector2f velocity;
	Vector2f position;

	//additional variables
	Color color;
	Sound hit;

	//state variables
	bool screenCollision;

public:

	//default constructor 
	Ball(const SoundBuffer& sound);

	//customizable constructor
	Ball(float radius, float mass, const Vector2f& initVelocity, const Vector2f& initPosition, const SoundBuffer& sound);

	//draw func
	void draw(RenderWindow& window);

	//real-time move using velocity
	void move(const Time& elapsed);
	//fixed value move
	void move(const Vector2f& displacement);

	//play hit sound
	void play();

	//getters & setters
	float getRadius() const;
	float getMass() const;
	Vector2f getPosition() const;
	Vector2f getVelocity() const;
	bool screenCollided() const;

	void setVelocity(const Vector2f& newVel);
	void setColor(const Color& newColor);
	void setPosition(const Vector2f& newPos);
	void setScreenCollision(bool state);

	void accelerate();
};