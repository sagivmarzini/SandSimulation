#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"

class Renderer
{
public:
	Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate, Grid& grid);

	void draw();

	void processEvents();

	bool isOpen() const;
private:
	sf::RenderWindow _window;
	Grid& _grid;
	float _sideLength;
};
