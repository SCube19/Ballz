#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Collisions.h"
#include "Maths.h"

using namespace sf;

int main()
{
	//testing init
	//preparing 1920x1080 window (res independence will come)
	RenderWindow window(VideoMode(1920, 1080), "Ballz", Style::Fullscreen);
	//every ball object uses the same circle shape to lessen memory usage
	CircleShape blueprintCircle;
	blueprintCircle.setOutlineColor(Color::White);
	blueprintCircle.setOutlineThickness(5);

	//velocity line, same reason as before
	VertexArray blueprintLine(LinesStrip, 2);
	blueprintLine[0].color = Color::Green;
	blueprintLine[1].color = Color::Green;

	//naive balls init, in-sim creation to do
	std::vector<Ball> ballz;
	Ball ball, ball2(40, 2, Vector2f(0.5, 1), Vector2f(200, 200)), ball3(50, 2, Vector2f(sqrt(2)/2, 0.5), Vector2f(400, 250))
		, ball4(20, 1, Vector2f(1, 0.5), Vector2f(1000, 1000)),
		ball5(100, 1, Vector2f(0.5, 0.75), Vector2f(1500, 500));
	ballz.push_back(ball);
	ballz.push_back(ball2);
	ballz.push_back(ball3);
	ballz.push_back(ball4);
	ballz.push_back(ball5);

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
		}
		//time passed from last frame
		Time frameTime = updateLimiter.restart();
		
		//position update
		for (auto &x: ballz)
			x.move(frameTime);

		//screen collisions
		for (auto &x: ballz)
			screenCollision(x);

		//static collisions, dynamic is next thing to do
		for (int i = 0; i < ballz.size(); i++)
		{
			for (int j = i + 1; j < ballz.size(); j++)
			{
				if (areColliding(ballz[i], ballz[j]))
				{
					staticCollisionResolution(ballz[i], ballz[j]);
					ballz[i].setVelocity(Vector2f(0, 0));
					ballz[j].setVelocity(Vector2f(0, 0));
				}
				
				
			}
		}
		
		//render 
		window.clear();
		for (auto &x: ballz)
			x.draw(window, blueprintCircle, blueprintLine);
		window.display();
	}

	return 0;
}