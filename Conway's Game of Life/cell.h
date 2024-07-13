#pragma once
#ifndef CELL_H_
#define CELL_H_

#include <iostream>
#include "life.h"

class cell
{
	bool alive;

public:
	cell() :alive(false) {}

	void draw(int row, int col) const;

	void create()
	{
		alive = true;
	}

	void erase()
	{
		alive = false;
	}

	bool is_alive() const { return alive; }
};


#endif // !CELL_H_
