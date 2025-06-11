#include "Grid.h"
#include "Random.h"
#include <algorithm>

#include "Types/Sand.h"
#include "Types/Water.h"
#include "Types/Mud.h"

#include <iostream>
// Define static members
Grid* Grid::instance = nullptr;
std::vector<std::vector<Grain*>> Grid::_cells;

Grid::Grid(const int cols, const int rows)
{
	//set instance
	instance = this;

	//init cells
	_cells = std::vector<std::vector<Grain*>>(rows, std::vector<Grain*>(cols, nullptr));

	//init random
	Random::seed(123);
}

Grid::~Grid()
{
	for (int row = 0; row < _cells.size(); row++)
	{
		for (int col = 0; col < _cells[0].size(); col++)
		{
			if (_cells[row][col] != nullptr)
				delete _cells[row][col];
		}
	}
}

void Grid::update()
{
	for (int row = static_cast<int>(_cells.size()) - 2; row >= 0; --row)
	{
		for (int col = 0; col < static_cast<int>(_cells[row].size()); ++col)
		{
			if (_cells[row][col] != nullptr)
			_cells[row][col]->update(row, col); //update all grains
		}
	}
}


std::vector<std::vector<Grain*>>& Grid::getCells()
{
	return _cells;
}

void Grid::setCell(const Grain::Type& type, const int col, const int row)
{
	if (_cells.empty() ||
		row < 0 || row >= _cells.size() ||
		col < 0 || col >= _cells[0].size()) return;

	if (_cells[row][col] != nullptr)
	{
		//if the cell trying to set isnt air, then delete it first
		delete _cells[row][col];
	}

	switch (type)
	{
	case Grain::Type::Sand:
		_cells[row][col] = new Sand();
		break;
	case Grain::Type::Water:
		_cells[row][col] = new Water();
		break;
	case Grain::Type::Mud:
		_cells[row][col] = new Mud();
		break;
	default:
		std::cout << "unable to find tpye to set a cell!\n";
		break;
	}
}


bool Grid::isAir(const int row, const int col)
{
	if (row < 0 || col < 0 ||
		row >= _cells.size() || col >= _cells[0].size())
		return false;

	return _cells[row][col] == nullptr;
}

bool Grid::isWater(const int row, const int col)
{
	if (isAir(row, col))
		return false;
	return _cells[row][col]->getType() == Grain::Type::Water;
}

bool Grid::isAirOrWater(const int row, const int col)
{
	return isAir(row, col) || isWater(row, col);
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

	if (isAir(row + 1, col) && isAir(row + 1, col + 1) && isAir(row + 1, col - 1))
	{
		//id the bottom 3 places of the mud are air, then fall normally
		std::swap(current, _cells[row + 1][col]);
	}

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
