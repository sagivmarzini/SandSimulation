#include "Mud.h"

Mud::Mud() : Grain(Grain::Type::Mud)
{
}

void Mud::update(const int row, const int col)
{
	auto& current = Grid::instance->getCells()[row][col];
	
	if (Grid::isAir(row + 1, col))
	{
		//if under the mud there is air, then fall normally
		std::swap(current, Grid::instance->getCells()[row + 1][col]);
	}

	//check if needs to move (1/5)
	const bool shouldUpdate = Random::intInRange(1, 5) == 5;
	if (shouldUpdate == false)
	{
		return;
	}

	//pick a random direction
	const int direction = Random::randomItem(std::array{ -1, 0, 1 });

	const bool canSink = Grid::isAirOrWater(row + 1, col + direction);
	if (canSink)
	{
		std::swap(current, Grid::instance->getCells()[row + 1][col + direction]);
	}
}
