#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Renderer.h"

constexpr double DELTA_TIME = 30.0f;
constexpr sf::Time LOGIC_DT = sf::seconds(1.f / DELTA_TIME);;

int main()
{
	Grid grid(120, 80);
	Renderer renderer(sf::VideoMode({ 1200, 800 }), "Sandy Boi", 60, grid);

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;

	while (renderer.isOpen())
	{
		sf::Time frameTime = clock.restart();
		accumulator += frameTime;

		while (accumulator >= LOGIC_DT)
		{
			grid.update();

			accumulator -= LOGIC_DT;
		}

		renderer.processEvents();

		renderer.draw();
	}

	return 0;
}