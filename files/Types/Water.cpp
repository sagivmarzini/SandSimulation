#include "Water.h"

Water::Water() : Grain(Grain::Type::Water)
{ 
}
	
void Water::update(const int row, const int col)
{
	auto& current = Grid::instance->getCells()[row][col];

	// Water physics priority:
	// 1. Fall straight down if possible
	// 2. Fall diagonally down if possible
	// 3. Flow horizontally if can't fall

	// 1. Try to fall straight down
	if (Grid::isAir(row + 1, col))
	{
		std::swap(current, Grid::instance->getCells()[row + 1][col]);
		return;
	}

	// 2. Try to fall diagonally
	const bool canFallLeft = Grid::isAir(row + 1, col - 1);
	const bool canFallRight = Grid::isAir(row + 1, col + 1);

	if (canFallLeft && canFallRight)
	{
		// Both diagonal directions available - choose randomly
		int direction = Random::randomItem(std::array{ -1, 1 });
		std::swap(current, Grid::instance->getCells()[row + 1][col + direction]);
		return;
	}
	else if (canFallRight)
	{
		std::swap(current, Grid::instance->getCells()[row + 1][col + 1]);
		return;
	}
	else if (canFallLeft)
	{
		std::swap(current, Grid::instance->getCells()[row + 1][col - 1]);
		return;
	}

	// 3. Can't fall anywhere - try to flow horizontally
	const bool canFlowLeft = Grid::isAir(row, col - 1);
	const bool canFlowRight = Grid::isAir(row, col + 1);

	if (canFlowLeft && canFlowRight)
	{
		// Both horizontal directions available - choose randomly
		int direction = Random::randomItem(std::array{ -1, 1 });
		std::swap(current, Grid::instance->getCells()[row][col + direction]);
	}
	else if (canFlowLeft)
	{
		std::swap(current, Grid::instance->getCells()[row][col - 1]);
	}
	else if (canFlowRight)
	{
		std::swap(current, Grid::instance->getCells()[row][col + 1]);
	}
	// If no movement possible, water stays put
}
