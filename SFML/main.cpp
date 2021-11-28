#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Ball.h"
#include "Collisions.h"
#include "Maths.h"
#include "Physics.h"


using namespace sf;

int main()
{
	//testing init
	//preparing 1920x1080 window (res independence will come)
	RenderWindow window(VideoMode(1920, 1080), "Ballz", Style::Fullscreen);
	window.setVerticalSyncEnabled(false);
	std::cout << window.getSize().x;

	SoundBuffer soundb;
	if (!soundb.loadFromFile("hit.wav"))
		return -1;

	//naive balls init, in-sim creation to do
	std::vector<Ball> ballz;
	Ball ball(soundb), ball2(40, 2, Vector2f(0.5, 1.0f), Vector2f(200, 200), soundb), ball3(50, 2.0f, Vector2f(sqrt(2)/2, 0.5), Vector2f(400, 250), soundb)
		, ball4(20, 1, Vector2f(1, 0.5), Vector2f(1000, 1000), soundb),
		ball5(100, 1, Vector2f(0.5, 0.75), Vector2f(1500, 500), soundb);

	Ball sun(100, 15, Vector2f(0.25, -0.5), Vector2f(1920 / 2, 1080 / 2), soundb), planet(20, 1, Vector2f(1, 0), Vector2f(50, 50), soundb);

	Ball binary1(100, 5, Vector2f(0, 0.5f), Vector2f(1920 / 4, 1080 / 2), soundb);
	Ball binary2(100, 5, Vector2f(0, -0.5f), Vector2f(3 * 1920 / 4, 1080 / 2), soundb);
	ballz.push_back(binary1);
	ballz.push_back(binary2);

	//ballz.push_back(sun);
	//ballz.push_back(planet);
	
	ballz.push_back(ball);
	ballz.push_back(ball2);
	ballz.push_back(ball3);
	//ballz.push_back(ball4);
	//ballz.push_back(ball5);

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
						if (Ballz::mouseCollision(x, Mouse::getPosition()))
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
		
		//physics
		//for (int i = 0; i < ballz.size(); i++)
			//for (int j = i + 1; j < ballz.size(); j++)
				//gravity(ballz[i], ballz[j]);
		
		//interaction
		if (selectedBall != nullptr)
			selectedBall->setPosition(Vector2f(Mouse::getPosition().x, Mouse::getPosition().y));

		//position update
		for (auto& x : ballz)
		{
			x.move(frameTime);
		}

		//screen collisions detection and resolution
		for (auto& x : ballz)
		{
			Ballz::screenCollisionResolution(x, window);
		}

		//vector of pairs of collided balls
		std::vector<std::pair<Ball&, Ball&>> collidedBallz;

		//static collisions
		for (auto i = 0; i < ballz.size(); i++)
		{
			for (auto j = 0; j < ballz.size(); j++)
			{
				if (i != j && Ballz::areColliding(ballz[i], ballz[j]))
				{
					Ballz::staticCollisionResolution(ballz[i], ballz[j]);
					std::pair<Ball&, Ball&> collisionPair(ballz[i] , ballz[j]);
					collidedBallz.push_back(collisionPair);
				}
			}
		}
		
		//dynamic collision resolution
		for (auto& x : collidedBallz)
			Ballz::dynamicCollisionResolution(x.first, x.second);

		//render 
		window.clear();
		for (auto &x: ballz)
			x.draw(window);
		window.display();
	}

	return 0;
}