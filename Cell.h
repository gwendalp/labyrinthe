#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <fstream>
using namespace std;

class Cell
{
	public:
	friend ostream& operator<<(ostream& stream, const Cell& c);
	friend istream& operator>>(istream& stream, Cell& c);
	Cell();
	Cell(int x, int y);
	int x; 
	int y; 
	int nb_neighb = 0;
	bool m_displayed = false;
	bool m_checked = false;
	void add_neighb(Cell *c);
	Cell** get_neighb();

	private:
	Cell **m_neighb = NULL;

};





#endif