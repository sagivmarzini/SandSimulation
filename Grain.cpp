#include "Grain.h"
#include "Random.h"

Grain::Grain()
	: _type(Type::Air)
{
}

void Grain::setType(const Type& type)
{
	_type = type;
	assignColor();
}

Grain::Type Grain::getType() const
{
	return _type;
}

sf::Color Grain::getColor() const
{
	return _color;
}

void Grain::assignColor()
{
	using enum Grain::Type;

	switch (_type)
	{
	case Air:
		_color = sf::Color::Transparent;
		break;
	case Sand:
		_color = sf::Color(Random::intInRange(220, 240), Random::intInRange(175, 190), Random::intInRange(115, 130), 255);
		break;
	case Mud:
		_color = sf::Color(Random::intInRange(120, 130), Random::intInRange(100, 150), Random::intInRange(70, 85), 255);
		break;
	case Water:
		_color = sf::Color(0, 0, Random::intInRange(240, 255));
		break;
	default:
		break;
	}
}