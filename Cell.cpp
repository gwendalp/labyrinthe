#include "Cell.h"
#include <iostream>
#include <fstream>
using namespace std;

Cell::Cell(int x, int y): x(x), y(y) {nb_neighb = 0; int n =100; m_neighb = new Cell*[n]; m_displayed=false;}

Cell::Cell(): x(0.), y(0.) {}


Cell** Cell::get_neighb()
{
    return m_neighb;
}

void Cell::add_neighb(Cell *c)
{   int i = 0;
    for (i; i < nb_neighb+1; i++)
    {
        if (m_neighb[i] == c)
        {
            break; 
        }
    }

    if (i == nb_neighb+1) 
        {
            
            nb_neighb = nb_neighb + 1; 
            m_neighb[nb_neighb - 1] = c;
            c->add_neighb(this);
        }      

}

ostream& operator<<(ostream& stream, const Cell& c)
{
    stream << "(" << c.x << "," << c.y << ")";
    return stream;
}


istream& operator>>(istream& stream, Cell& c)
{
    stream.ignore(1,'(');
    stream >> c.x;
    stream.ignore(1,',');
    stream >> c.y;
}