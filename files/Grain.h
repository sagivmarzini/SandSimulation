#pragma once

#include <SFML/Graphics.hpp>

class Grain
{
public:
	enum class Type
	{
		Air,
		Sand,
		Mud,
		Water
	};

	Grain();
	Grain(const Type& type);

	void setType(const Type& type);
	Type getType() const;

	sf::Color getColor() const;

	virtual void update(const int row, const int col) = 0;

private:
	void assignColor();

	Type _type;
	sf::Color _color;
};
