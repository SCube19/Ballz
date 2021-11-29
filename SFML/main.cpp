#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Ball.h"
#include "Collisions.h"
#include "Maths.h"
#include "Physics.h"


using namespace sf;

//time in seconds
//the target is 60fps
constexpr int timeStep = 16;

int main()
{
	//testing init
	//preparing 1920x1080 window (res independence will come)
	RenderWindow window(VideoMode(1920, 1080), "Ballz", Style::Fullscreen);
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(100);
	std::cout << window.getSize().x;

	SoundBuffer soundb;
	if (!soundb.loadFromFile("hit.wav"))
		return -1;

	//naive balls init, in-sim creation to do
	std::vector<Ball> ballz;
	Ball ball(soundb), ball2(40, 2, Vector2f(0.5, 1.0f), Vector2f(200, 200), soundb), ball3(50, 2.0f, Vector2f(sqrt(2)/2, 0.5), Vector2f(400, 250), soundb)
		, ball4(20, 1, Vector2f(1, 0.5), Vector2f(1000, 1000), soundb),
		ball5(100, 1, Vector2f(0.5, 0.75), Vector2f(1500, 500), soundb);

	Ball sun(100, 1000, Vector2f(0, 0), Vector2f(1920 / 2, 1080 / 2), soundb), planet(20, 1, Vector2f(0.7f, 0), Vector2f(1920 / 2, 150), soundb);
	
	Ball binary1(50, 150, Vector2f(0, 0.5f), Vector2f(1920 / 4, 1080 / 2), soundb);
	Ball binary2(50, 150, Vector2f(0, -0.5f), Vector2f(3 * 1920 / 4, 1080 / 2), soundb);

	Ball stationary1(50, 20, Vector2f(0, 0), Vector2f(1920 / 4, 1080 / 2), soundb);
	Ball stationary2(50, 20, Vector2f(0, 0), Vector2f(3 * 1920 / 4, 1080 / 2), soundb);

	ballz.push_back(stationary1);
	ballz.push_back(stationary2);
	//ballz.push_back(binary1);
	//ballz.push_back(binary2);

	//ballz.push_back(sun);
	//ballz.push_back(planet);
	
	//ballz.push_back(ball);
	//ballz.push_back(ball2);
	//ballz.push_back(ball3);
	//ballz.push_back(ball4);
	//ballz.push_back(ball5);

	Ball* selectedBall = nullptr;
	
	//used for semi-constant frame time physics
	int notSimulatedTime = 0;
	//frame time measurment
	Clock frameClock;
	
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

		//interaction
		//if (selectedBall != nullptr)
			//selectedBall->setPosition(Vector2f(Mouse::getPosition().x, Mouse::getPosition().y));

		//time passed from last frame
		notSimulatedTime += frameClock.restart().asMilliseconds();

		//simulate in timeStep discrete steps until notSimulatedTime is smaller than the step
		while (notSimulatedTime >= timeStep)
		{
			Ballz::applyPhysics(ballz, window, timeStep);
			notSimulatedTime -= timeStep;
		}

		//render 
		window.clear();
		for (auto &x: ballz)
			x.draw(window);
		window.display();
	}

	return 0;
}