#include "Sand.h"

Sand::Sand() : Grain(Grain::Type::Sand)
{
}

void Sand::update(const int row, const int col)
{
	auto& current = Grid::instance->getCells()[row][col];
	auto& currentRow = Grid::instance->getCells()[row];
	auto& nextRow = Grid::instance->getCells()[row + 1];


	//check for srounding water to change into mud
	const bool upOrDownIsWater = Grid::isWater(row + 1, col) || Grid::isWater(row - 1, col);
	const bool bottomDiagonalsAreWater = Grid::isWater(row + 1, col + 1) || Grid::isWater(row + 1, col - 1);
	const bool sidesAreWater = Grid::isWater(row, col + 1) || Grid::isWater(row, col - 1);

	if (upOrDownIsWater || bottomDiagonalsAreWater || sidesAreWater)
	{
		//if water is touching the sand, turn into mud
		Grid::instance->setCell(Grain::Type::Mud, col, row);
	}

	//apply gravity
	if (Grid::isAirOrWater(row + 1, col))
	{
		std::swap(current, nextRow[col]);
		return;
	}

	const bool downLeftEmpty = Grid::isAirOrWater(row + 1, col - 1);
	const bool downRightEmpty = Grid::isAirOrWater(row + 1, col + 1);
	const bool leftEmpty = Grid::isAirOrWater(row, col - 1);
	const bool rightEmpty = Grid::isAirOrWater(row, col + 1);

	// FIXME: If there is water below try to move it to the side before moving down
	if (downLeftEmpty && !downRightEmpty && leftEmpty)
		std::swap(current, nextRow[col - 1]);
	else if (!downLeftEmpty && downRightEmpty && rightEmpty)
		std::swap(current, nextRow[col + 1]);
	else if (downLeftEmpty && downRightEmpty && rightEmpty && leftEmpty)
	{
		int direction = Random::randomItem(std::array{ -1, 1 });
		std::swap(current, nextRow[col + direction]);
	}
	// else: no move possible, stay put
}
