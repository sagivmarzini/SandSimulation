#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Renderer.h"

constexpr double FRAME_RATE = 60.0f;
constexpr sf::Time deltaTime = sf::seconds(1.f / FRAME_RATE);;

int main()
{
	Grid grid(180, 80);
	Renderer renderer(sf::VideoMode({ 1800, 800 }), "Sandy Boi", FRAME_RATE, grid);

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;

	while (renderer.isOpen())
	{
		renderer.processEvents();

		sf::Time frameTime = clock.restart();
		accumulator += frameTime;

		while (accumulator >= deltaTime)
		{
			grid.update();

			accumulator -= deltaTime;
		}

		renderer.draw();
	}

	return 0;
}