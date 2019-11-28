#include "Path.h"
#include <iostream>
#include "Cell.h"
#include "vibes.h"
#include <vector>
using namespace std;

Path::Path(const Cell *c) 
{
    m_c = new Cell;
    m_c = c;
}

void Path::add_to_path(const Cell *c)
{
    Path *p = this;
   
    while(p->m_next != NULL)
	{
		p = p->m_next;
	}
    
    p->m_next = new Path(c);

    p->m_next->m_next = NULL;

}

void Path::print_path(void)
{
    Path *p;
    p = this;
    vector<double> X;
    vector<double> Y;


    while(p != NULL)
    {
        cout << "(" << p->m_c->x << "," << p->m_c->y << ")"  << endl; 
        X.push_back(p->m_c->x+0.5);
        Y.push_back(p->m_c->y+0.5);
        
        p = p->m_next;
    }
    
    
    vibes::drawLine(X, Y, "green");

}

