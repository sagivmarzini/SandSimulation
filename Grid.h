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
	bool isAir(const int row, const int col) const;
	bool isAirOrWater(const int row, const int col) const;

	void updateSand(const int row, const int col);
	void updateWater(const int row, const int col);

	std::vector<std::vector<Grain>> _cells;
};
