#pragma once
#include "../Grid.h"

class Mud : public Grain
{
public:
	Mud();
	virtual ~Mud() = default;

	void update(const int row, const int col) override;
};

