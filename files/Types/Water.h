#pragma once
#include "../Grid.h"


class Water : public Grain
{
public:
	Water();
	virtual ~Water() = default;

	void update(const int row, const int col) override;
};

