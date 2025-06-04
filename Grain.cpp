#include "Grain.h"
#include "Random.h"

Grain::Grain()
	: _type(Type::AIR)
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
	switch (_type)
	{
	case Grain::Type::AIR:
		_color = sf::Color::Transparent;
		break;
	case Grain::Type::SAND:
		_color = sf::Color(Random::intInRange(220, 255), 0, 0);
		break;
	default:
		break;
	}
}