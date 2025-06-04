#pragma once

#include "Grain.h"
#include <array>

class Grid
{
public:
	Grid(const int cols, const int rows);

	void update();

	const std::vector<std::vector<Grain>>& getCells() const;
	void setCell(const Grain::Type& type, const int col, const int row);

private:
	bool isEmpty(const int row, const int col) const;

	std::vector<std::vector<Grain>> _cells;
};
