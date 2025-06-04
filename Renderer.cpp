#include "Renderer.h"

Renderer::Renderer(const sf::VideoMode& videoMode, const std::string& windowName, const int maxFrameRate, Grid& grid)
	: _window(videoMode, windowName),
	_grid(grid),
	_sideLength((float)std::min(_window.getSize().y / grid.getCells().size(), _window.getSize().x / grid.getCells()[0].size())),
	_brushSize(_window.getSize().x / 100 / _sideLength)
{
	//_window.setFramerateLimit(maxFrameRate);
}

void Renderer::draw()
{
	_window.clear(sf::Color::Black);

	drawSand();
	drawBrush();

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
		else if (const auto* mouseEvent = event->getIf<sf::Event::MouseWheelScrolled>())
		{
			if (mouseEvent->delta > 0) _brushSize++;
			if (mouseEvent->delta < 0 && _brushSize > 1) _brushSize--;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

		int col = mousePos.x / _sideLength;
		int row = mousePos.y / _sideLength;

		useBrush(col, row, Grain::Type::Sand);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

		int col = mousePos.x / _sideLength;
		int row = mousePos.y / _sideLength;

		useBrush(col, row, Grain::Type::Water);
	}
}

bool Renderer::isOpen() const
{
	return _window.isOpen();
}

void Renderer::drawSand()
{
	sf::VertexArray vertices(sf::PrimitiveType::Triangles);
	const auto& cells = _grid.getCells();

	for (int row = 0; row < cells.size(); ++row) {
		for (int col = 0; col < cells[row].size(); ++col) {
			const auto& cell = cells[row][col];
			if (cell.getType() == Grain::Type::Air)
				continue; // skip empty cells

			float x = col * _sideLength;
			float y = row * _sideLength;

			vertices.append(sf::Vertex{ { x, y }, cell.getColor() });
			vertices.append(sf::Vertex{ { x + _sideLength, y }, cell.getColor() });
			vertices.append(sf::Vertex{ { x + _sideLength, y + _sideLength }, cell.getColor() });

			vertices.append(sf::Vertex{ { x, y }, cell.getColor() });
			vertices.append(sf::Vertex{ { x + _sideLength, y + _sideLength }, cell.getColor() });
			vertices.append(sf::Vertex{ { x, y + _sideLength }, cell.getColor() });
		}
	}

	_window.draw(vertices);
}

void Renderer::drawBrush()
{
	const auto mousePosition = sf::Mouse::getPosition(_window);
	const auto brushSize = _brushSize * _sideLength;

	auto brushCursor = sf::CircleShape(brushSize);
	brushCursor.setOrigin({ (float)brushSize,(float)brushSize });
	brushCursor.setPosition({ (float)mousePosition.x, (float)mousePosition.y });
	brushCursor.setOutlineThickness(2);
	brushCursor.setFillColor(sf::Color(255, 255, 255, 100));

	_window.draw(brushCursor);
}

void Renderer::useBrush(const int col, const int row, const Grain::Type grainType)
{
	const int radius = _brushSize / 2;

	for (int x = -radius; x <= radius; x++)
	{
		for (int y = -radius; y <= radius; y++)
		{
			// Make it circular instead of square
			if (x * x + y * y <= radius * radius)
			{
				_grid.setCell(grainType, col + x, row + y);
			}
		}
	}
}