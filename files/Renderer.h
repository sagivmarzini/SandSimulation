#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"

class Renderer
{
public:
	Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate);

	void draw();

	void processEvents();

	bool isOpen() const;
private:
	void drawGrid();
	void drawBrush();

	void useBrush(const int col, const int row, const Grain::Type grainType);

	sf::RenderWindow _window;
	float _sideLength;
	int _brushSize;
};
