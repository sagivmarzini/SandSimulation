#include "Grid.h"
#include "Random.h"
#include <algorithm>

Grid::Grid(const int cols, const int rows)
	: _cells(rows, std::vector<Grain>(cols, Grain()))
{
	//init random
	Random::seed(123);
}

void Grid::update()
{
	for (int row = static_cast<int>(_cells.size()) - 2; row >= 0; --row)
	{
		for (int col = 0; col < static_cast<int>(_cells[row].size()); ++col)
		{
			auto& current = _cells[row][col];

			using enum Grain::Type;
			switch (current.getType())
			{
			case Sand:
				updateSand(row, col);
				break;
			case Mud:
				updateMud(row, col);
				break;
			case Water:
				updateWater(row, col);
				break;
			default:
				break;
			}
		}
	}
}

const std::vector<std::vector<Grain>>& Grid::getCells() const
{
	return _cells;
}

void Grid::setCell(const Grain::Type& type, const int col, const int row)
{
	if (_cells.empty() ||
		row < 0 || row >= _cells.size() ||
		col < 0 || col >= _cells[0].size() ||
		_cells[row][col].getType() != Grain::Type::Air) return;

	_cells[row][col].setType(type);
}

bool Grid::isAir(const int row, const int col) const
{
	if (row < 0 || col < 0 ||
		row >= _cells.size() || col >= _cells[0].size())
		return false;

	return _cells[row][col].getType() == Grain::Type::Air;
}

bool Grid::isWater(const int row, const int col) const
{
	if (row < 0 || col < 0 ||
		row >= _cells.size() || col >= _cells[0].size())
		return false;
	return _cells[row][col].getType() == Grain::Type::Water;
}

bool Grid::isAirOrWater(const int row, const int col) const
{
	if (row < 0 || col < 0 ||
		row >= _cells.size() || col >= _cells[0].size())
		return false;

	const auto type = _cells[row][col].getType();
	return type == Grain::Type::Air || type == Grain::Type::Water;
}

void Grid::updateSand(const int row, const int col)
{
	auto& current = _cells[row][col];
	auto& currentRow = _cells[row];
	auto& nextRow = _cells[row + 1];


	//check for srounding water to change into mud
	const bool upOrDownIsWater = isWater(row + 1, col) || isWater(row - 1, col);
	const bool topDiagonalsAreWater = isWater(row - 1, col + 1) || isWater(row - 1, col - 1);
	const bool sidesAreWater = isWater(row, col + 1) || isWater(row, col - 1);

	if (upOrDownIsWater || topDiagonalsAreWater || sidesAreWater)
	{
		//if water is touching the sand, turn into mud
		_cells[row][col].setType(Grain::Type::Mud);
	}

	//apply gravity
	if (isAirOrWater(row + 1, col))
	{
		std::swap(current, nextRow[col]);
		return;
	}

	const bool downLeftEmpty = isAirOrWater(row + 1, col - 1);
	const bool downRightEmpty = isAirOrWater(row + 1, col + 1);
	const bool leftEmpty = isAirOrWater(row, col - 1);
	const bool rightEmpty = isAirOrWater(row, col + 1);

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

void Grid::updateWater(const int row, const int col)
{
	auto& current = _cells[row][col];

	// Water physics priority:
	// 1. Fall straight down if possible
	// 2. Fall diagonally down if possible
	// 3. Flow horizontally if can't fall

	// 1. Try to fall straight down
	if (isAir(row + 1, col))
	{
		std::swap(current, _cells[row + 1][col]);
		return;
	}

	// 2. Try to fall diagonally
	const bool canFallLeft = isAir(row + 1, col - 1);
	const bool canFallRight = isAir(row + 1, col + 1);

	if (canFallLeft && canFallRight)
	{
		// Both diagonal directions available - choose randomly
		int direction = Random::randomItem(std::array{ -1, 1 });
		std::swap(current, _cells[row + 1][col + direction]);
		return;
	}
	else if (canFallRight)
	{
		std::swap(current, _cells[row + 1][col + 1]);
		return;
	}
	else if (canFallLeft)
	{
		std::swap(current, _cells[row + 1][col - 1]);
		return;
	}

	// 3. Can't fall anywhere - try to flow horizontally
	const bool canFlowLeft = isAir(row, col - 1);
	const bool canFlowRight = isAir(row, col + 1);

	if (canFlowLeft && canFlowRight)
	{
		// Both horizontal directions available - choose randomly
		int direction = Random::randomItem(std::array{ -1, 1 });
		std::swap(current, _cells[row][col + direction]);
	}
	else if (canFlowLeft)
	{
		std::swap(current, _cells[row][col - 1]);
	}
	else if (canFlowRight)
	{
		std::swap(current, _cells[row][col + 1]);
	}
	// If no movement possible, water stays put
}

void Grid::updateMud(const int row, const int col)
{
	auto& current = _cells[row][col];


	//check if needs to move (1/5)
	const bool shouldUpdate = Random::intInRange(1, 5) == 5;
	if (shouldUpdate == false)
	{
		return;
	}

	//pick a random direction
	const int direction = Random::randomItem(std::array{ -1, 0, 1 });

	const bool canSink = isAirOrWater(row + 1, col + direction);
	if (canSink)
	{
		std::swap(current, _cells[row + 1][col + direction]);
	}
}
