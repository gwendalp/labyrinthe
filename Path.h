#ifndef __PATH_H__
#define __PATH_H__

#include "Cell.h"
#include <iostream>
#include "vibes.h"
using namespace std; 


class Path
{
    public:
    Path(const Cell *c);
    void add_to_path(const Cell *c);
    void print_path(void);
    void draw_path(void);


    protected:

    const Cell *m_c;
    Path *m_next = NULL;

};




#endif