#include "Grid.h"
#include "Random.h"
#include <algorithm>

Grid::Grid(const int cols, const int rows)
	: _cells(rows, std::vector<Grain>(cols, Grain()))
{
	_cells[rows / 2][cols / 2].setType(Grain::Type::SAND);
}

void Grid::update()
{
	for (int row = static_cast<int>(_cells.size()) - 2; row >= 0; --row)
	{
		auto& currentRow = _cells[row];
		auto& nextRow = _cells[row + 1];

		for (int col = 0; col < static_cast<int>(currentRow.size()); ++col)
		{
			auto& current = currentRow[col];

			if (isEmpty(row + 1, col))
			{
				std::swap(current, nextRow[col]);
				continue;
			}

			const bool leftEmpty = isEmpty(row + 1, col - 1);
			const bool rightEmpty = isEmpty(row + 1, col + 1);

			if (leftEmpty && !rightEmpty)
				std::swap(current, nextRow[col - 1]);
			else if (!leftEmpty && rightEmpty)
				std::swap(current, nextRow[col + 1]);
			else if (leftEmpty && rightEmpty)
			{
				int direction = Random::randomItem(std::array{ -1, 1 });
				std::swap(current, nextRow[col + direction]);
			}
			// else: no move possible, stay put
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
		_cells[row][col].getType() != Grain::Type::AIR) return;

	_cells[row][col].setType(type);
}

bool Grid::isEmpty(const int row, const int col) const
{
	if (row < 0 || col < 0 ||
		row >= _cells.size() || col >= _cells[0].size())
		return false;

	return _cells[row][col].getType() == Grain::Type::AIR;
}