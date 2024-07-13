#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <vector>
#include <cstdlib>

#include "cell.h"

class grid //cells on screen
{
	cell cells[row_max + 2][col_max + 2]; //+2 added for borders
public:
	void create(int row, int column);

	void draw();

	void randomize();

	bool will_survive(int row, int column);

	bool will_create(int row, int column);

	void update(const grid& next);//update to next genereation

};

void calculate(grid& old_generation, grid& new_generation);

#endif // !1

