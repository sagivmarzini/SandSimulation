#pragma once

#include <SFML/Graphics.hpp>

class Grain
{
public:
	enum class Type
	{
		AIR,
		SAND
	};

	Grain();

	void setType(const Type& type);
	Type getType() const;

	sf::Color getColor() const;

private:
	void assignColor();

	Type _type;
	sf::Color _color;
};
