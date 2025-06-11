#pragma once

#include "Grain.h"
#include <array>
#include "Random.h"

class Grid
{
public:
	Grid(const int cols, const int rows);
	~Grid();
	static Grid* getInstance() { return instance; };
	static Grid* instance;

	static void update();

	static std::vector<std::vector<Grain*>>& getCells();
	static void setCell(const Grain::Type& type, const int col, const int row);

	static bool isAir(const int row, const int col);
	static bool isWater(const int row, const int col);
	static bool isAirOrWater(const int row, const int col);
private:

	static void updateSand(const int row, const int col);
	static void updateWater(const int row, const int col);
	static void updateMud(const int row, const int col);

	static std::vector<std::vector<Grain*>> _cells;
};
