#include "cell.h"
using namespace std;

void cell::draw(int row, int col) const
{
	cout << "\x1b[" << row + 1 << ";" << col + 1 << "H";
	cout << (alive ? live_cell : dead_cell);
}