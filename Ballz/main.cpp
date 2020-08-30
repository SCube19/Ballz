#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Collisions.h"
#include "Maths.h"
#include "Physics.h"
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

int main()
{
	//testing init
	//preparing 1920x1080 window (res independence will come)
	RenderWindow window(VideoMode(1920, 1080), "Ballz", Style::Fullscreen);
	window.setVerticalSyncEnabled(false);
	//every ball object uses the same circle shape to lessen memory usage
	CircleShape blueprintCircle;
	blueprintCircle.setOutlineColor(Color::White);
	blueprintCircle.setOutlineThickness(1);

	//velocity line, same reason as before
	VertexArray blueprintLine(LinesStrip, 2);
	blueprintLine[0].color = Color::Green;
	blueprintLine[1].color = Color::Green;

	SoundBuffer soundb;
	if (!soundb.loadFromFile("hit.wav"))
		return -1;

	//naive balls init, in-sim creation to do
	std::vector<Ball> ballz;
	Ball ball(soundb), ball2(40, 2, Vector2f(0.5, 1.0f), Vector2f(200, 200), soundb), ball3(50, 2.0f, Vector2f(sqrt(2)/2, 0.5), Vector2f(400, 250), soundb)
		, ball4(20, 1, Vector2f(1, 0.5), Vector2f(1000, 1000), soundb),
		ball5(100, 1, Vector2f(0.5, 0.75), Vector2f(1500, 500), soundb);

	Ball sun(100, 3, Vector2f(0.25, -0.5), Vector2f(1920 / 2, 1080 / 2), soundb), planet(20, 1, Vector2f(1, 0), Vector2f(50, 50), soundb);
	ballz.push_back(sun);
	ballz.push_back(planet);
	
	ballz.push_back(ball);
	ballz.push_back(ball2);
	ballz.push_back(ball3);
	ballz.push_back(ball4);
	ballz.push_back(ball5);

	
	Ball* selectedBall = nullptr;

	//for frame-independent movement
	Clock updateLimiter;
	
	while (window.isOpen())
	{
		//sfml event handler
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape: 
					window.close();
					break;
				default:
					break;
				}
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					selectedBall = nullptr;
					for (auto& x : ballz)
						if (mouseCollision(x, Mouse::getPosition()))
						{
							x.setColor(Color::Red);
							selectedBall = &x;
							selectedBall->setVelocity(Vector2f(0, 0));
							break;
						}
				}
				
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (selectedBall != nullptr)
				{
					selectedBall->setColor(Color::Transparent);
					selectedBall = nullptr;
				}
			}
		}
		//time passed from last frame
		Time frameTime = updateLimiter.restart();
		
		//for (int i = 0; i < ballz.size(); i++)
			//for (int j = i + 1; j < ballz.size(); j++)
				//gravity(ballz[i], ballz[j]);
				
			
		if (selectedBall != nullptr)
			selectedBall->setPosition(Vector2f(Mouse::getPosition().x, Mouse::getPosition().y));

		//position update
		for (auto& x : ballz)
		{
			x.move(frameTime);
		}

		//screen collisions
		for (auto& x : ballz)
		{
			screenCollision(x, window);
		}

		//vector of pairs of collided balls
		std::vector<std::pair<Ball&, Ball&>> collidedBallz;

		//static collisions, dynamic is next thing to do
		for (auto i = 0; i < ballz.size(); i++)
		{
			for (auto j = 0; j < ballz.size(); j++)
			{
				if (i != j && areColliding(ballz[i], ballz[j]))
				{
					staticCollisionResolution(ballz[i], ballz[j]);
					std::pair<Ball&, Ball&> collisionPair(ballz[i] , ballz[j]);
					collidedBallz.push_back(collisionPair);
				}
			}
		}
		
		for (auto& x : collidedBallz)
			dynamicCollisionResolution(x.first, x.second);

		//render 
		window.clear();
		for (auto &x: ballz)
			x.draw(window, blueprintCircle, blueprintLine);
		window.display();
	}

	return 0;
}