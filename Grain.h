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

private:
	Type _type;
};
