#include "Renderer.h"

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate, Grid& grid)
	: _window(videoMode, windowName),
	_grid(grid),
	_sideLength((float)std::min(_window.getSize().y / grid.getCells().size(), _window.getSize().x / grid.getCells()[0].size()))
{
	//_window.setFramerateLimit(maxFrameRate);
}

void Renderer::draw()
{
	_window.clear(sf::Color::Black);

	sf::VertexArray vertices(sf::PrimitiveType::Triangles);
	const auto& cells = _grid.getCells();

	for (int row = 0; row < cells.size(); ++row) {
		for (int col = 0; col < cells[row].size(); ++col) {
			if (cells[row][col].getType() == Grain::Type::AIR)
				continue; // skip empty cells

			float x = col * _sideLength;
			float y = row * _sideLength;

			vertices.append(sf::Vertex{ { x, y }, sf::Color::White });
			vertices.append(sf::Vertex{ { x + _sideLength, y }, sf::Color::White });
			vertices.append(sf::Vertex{ { x + _sideLength, y + _sideLength }, sf::Color::White });

			vertices.append(sf::Vertex{ { x, y }, sf::Color::White });
			vertices.append(sf::Vertex{ { x + _sideLength, y + _sideLength }, sf::Color::White });
			vertices.append(sf::Vertex{ { x, y + _sideLength }, sf::Color::White });
		}
	}

	_window.draw(vertices);

	_window.display();
}

void Renderer::processEvents()
{
	const std::optional event = _window.pollEvent();

	if (event.has_value())
	{
		if (event->is<sf::Event::Closed>())
			_window.close();

		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				_window.close();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

		int col = mousePos.x / _sideLength;
		int row = mousePos.y / _sideLength;

		_grid.setCell(Grain::Type::SAND, col, row);
	}
}

bool Renderer::isOpen() const
{
	return _window.isOpen();
}