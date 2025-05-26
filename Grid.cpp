#include "Grid.h"
#include <algorithm>

Grid::Grid(const int cols, const int rows)
	: _cells(rows, std::vector<Grain>(cols, Grain()))
{
	_cells[rows / 2][cols / 2].setType(Grain::Type::SAND);
}

void Grid::update()
{
	for (int i = _cells.size() - 2; i >= 0; i--)
	{
		for (int j = 0; j < _cells[i].size(); j++)
		{
			Grain& current = _cells[i][j];

			if (_cells[i + 1][j].getType() == Grain::Type::AIR)
			{
				std::swap(current, _cells[i + 1][j]);
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
	if (_cells.empty() || row < 0 || row >= _cells.size() ||
		col < 0 || col >= _cells[0].size() ||
		_cells[row][col].getType() != Grain::Type::AIR) return;

	_cells[row][col].setType(type);
}