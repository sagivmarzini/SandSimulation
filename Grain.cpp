#include "Grain.h"

Grain::Grain()
	: _type(Type::AIR)
{
}

void Grain::setType(const Type& type)
{
	_type = type;
}

Grain::Type Grain::getType() const
{
	return _type;
}