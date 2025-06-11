#pragma once
#include "../Grid.h"


class Sand : public Grain
{
public:
	Sand();
	virtual ~Sand() = default;
	
	void update(const int row, const int col) override;

};

