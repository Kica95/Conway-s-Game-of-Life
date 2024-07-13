#include "grid.h"
using namespace std;

void grid::create(int row, int col) 
{
	cells[row][col].create();
}

void grid::draw() 
{
	//ANSI control command \x1b means "escape" Escape[2J clears the screan and returns the cursor to the "home" position
	cout << "\x1b[2J";

	for (int row = 0; row < row_max; row++) 
	{
		for (int col = 0; col < col_max; col++)
		{
			cells[row][col].draw(row, col);
		}
	}
}

//Populate the grid with cells, at random
void grid::randomize()
{
	const int factor = 5;
	const int cutof = RAND_MAX / factor;//one in five probability od the cell being initialy populated

	time_t now;
	time(&now);
	//srand(now); we dont want to seed the the rezult so with this comented we will always get the same output

	for (int row = 1;row < row_max; ++row)
	{
		for (int col = 1;col < col_max; ++col)
		{
			if (rand() / cutof == 0) //evert fifth will be created for a large bunch of random numbers
			{
				create(row, col);
			}
		}
	}
}
bool grid::will_survive(int row, int col) 
{
	if (!cells[row][col].is_alive()) 
	{
		return false;
	}

	//Algoritham for finding the number of live neighnouts
	int neighbours = cells[row - 1][col - 1].is_alive() +
					 cells[row - 1][col].is_alive() +
					 cells[row - 1][col + 1].is_alive() +
					 cells[row][col - 1].is_alive() +
					 cells[row][col + 1].is_alive() +
					 cells[row + 1][col - 1].is_alive() +
					 cells[row + 1][col].is_alive() +
					 cells[row + 1][col + 1].is_alive();
					

	if (neighbours < min_neighbours || neighbours > max_neighbours) 
	{
		return false;
	}

	return true;
}

bool grid::will_create(int row, int col)
{
	if (cells[row][col].is_alive())
	{
		return false; //There is already a cell at this position
	}

	int parants = cells[row - 1][col - 1].is_alive() +
		cells[row - 1][col].is_alive() +
		cells[row - 1][col + 1].is_alive() +
		cells[row][col - 1].is_alive() +
		cells[row][col + 1].is_alive() +
		cells[row + 1][col - 1].is_alive() +
		cells[row + 1][col].is_alive() +
		cells[row + 1][col + 1].is_alive();

	if (parants < min_parents || parants > max_parents)
	{
		return false;
	}

	return true;

}

void grid::update(const grid& next)
{
	for (int row = 1;row < row_max; ++row)
	{
		for (int col = 1;col < col_max; ++col)
		{
			cells[row][col] = next.cells[row][col];
		}
	}
}


//By default the cell in the new generation will be set to unpopulated
//we populate them acording to specified rules
void calculate(grid& old_generation, grid& new_generation) 
{
	for (int row = 1;row < row_max; ++row)
	{
		for (int col = 1;col < col_max; ++col)
		{
			//will the cell survive in the next gen so it needs to be populated
			if (old_generation.will_survive(row, col))
			{
				new_generation.create(row, col);
			}//will the cell be created in the next gen so it needs to be populated
			else if (old_generation.will_create(row, col)) 
			{
				new_generation.create(row, col);
			}
		}
	}
}