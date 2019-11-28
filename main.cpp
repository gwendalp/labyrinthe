#include <iostream>
#include "Cell.h"
#include "vibes.h"
#include <vector>
#include <fstream>
#include <string>
#include "Path.h"
#include <queue>
#include <queue> 

using namespace std;

struct Maze    
{
    Cell *Labyrinthe[4][4];
    Cell *c0;
    Cell *cf;
};

void init()
{
    vibes::beginDrawing(); // initialisation de VIBes
	vibes::newFigure("Maze"); // cr ́eation d’une figure
	vibes::setFigureProperties("Maze",vibesParams("x", 100, "y", 100,"width", 400, "height", 400)); // propri ́et ́es de la figure
	vibes::axisLimits(0-0.5, 4.5, -0.5, 4.5); // dimensions de la vue graphique
}


void draw_gate(const Cell *n1, const Cell *n2)
{
    vibes::drawBox(min(n1->x, n2->x) + 0.1, max(n1->x, n2->x) + 0.9,
    min(n1->y, n2->y) + 0.1, max(n1->y, n2->y) + 0.9,
    "lightGray[lightGray]");
}

void display_cell(Cell *cell)
{
    
    vibes::drawBox(cell->x, cell->x + 1, cell->y, cell->y + 1, "[lightGray]");
    cell->m_displayed = true;
    for(int i = 0 ; i < cell->nb_neighb ; i++)
    {
        if(!cell->get_neighb()[i]->m_displayed)
            display_cell(cell->get_neighb()[i]);
        draw_gate(cell, cell->get_neighb()[i]);
    }
}


Maze create_maze(void)
{
    Maze m;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            m.Labyrinthe[x][y] = new Cell(x, y);
        }
        
    }

    m.Labyrinthe[0][0]->add_neighb(m.Labyrinthe[0][1]);
	m.Labyrinthe[0][1]->add_neighb(m.Labyrinthe[0][2]);
	m.Labyrinthe[0][2]->add_neighb(m.Labyrinthe[0][3]);
	m.Labyrinthe[0][3]->add_neighb(m.Labyrinthe[1][3]);

	m.Labyrinthe[1][0]->add_neighb(m.Labyrinthe[2][0]);
	m.Labyrinthe[1][1]->add_neighb(m.Labyrinthe[1][2]);
	m.Labyrinthe[1][1]->add_neighb(m.Labyrinthe[2][1]);
	m.Labyrinthe[1][3]->add_neighb(m.Labyrinthe[2][3]);

	m.Labyrinthe[2][0]->add_neighb(m.Labyrinthe[3][0]);
	m.Labyrinthe[2][1]->add_neighb(m.Labyrinthe[2][2]);
	m.Labyrinthe[2][1]->add_neighb(m.Labyrinthe[3][1]);
	m.Labyrinthe[2][2]->add_neighb(m.Labyrinthe[3][2]);
	m.Labyrinthe[2][3]->add_neighb(m.Labyrinthe[3][3]);

	m.Labyrinthe[3][0]->add_neighb(m.Labyrinthe[3][1]);
	m.Labyrinthe[3][2]->add_neighb(m.Labyrinthe[3][3]);

    return m;
    
}




void display(Maze m)
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            display_cell(m.Labyrinthe[x][y]);
        }
        
    }
        vibes::drawCircle(1.5, 0.5, 0.3, "[Red]");
        vibes::drawCircle(0.5, 0.5, 0.3, "[Green]");
}

void save_maze(const Maze& maze, const string& file_name)
{
    ofstream ofst(file_name);
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j <4; j++)
        {
            ofst << *maze.Labyrinthe[i][j] << maze.Labyrinthe[i][j]->nb_neighb;

            for (int z =0; z<maze.Labyrinthe[i][j]->nb_neighb; z++)
            {
                ofst << *maze.Labyrinthe[i][j]->get_neighb()[z];
            }
            ofst << endl; 

        }
    }
    
    
    ofst.close();
}


void save_cell(Cell *cell, ofstream *f)
{
    *f << *cell;
    
}

bool find_path(Cell *c, Cell *cf,  Path *p)
{
    p->add_to_path(c);
    c->m_checked = true;

    if (c->x == cf->x && c->y == cf->y)
    { 
        cout << "Found ! " << endl; 
        p -> print_path();
        return true;
    }
    else
    {
        for (int i = 0; i < c->nb_neighb; i++)
        {
            if (c->get_neighb()[i]->m_checked == false)
            {
                if (find_path(c->get_neighb()[i], cf, p))
                {
                    return true;
                }
            }
        }
        return false;
    }
}



int main()
{
    init();
    Maze maze;
    maze = create_maze();
    display(maze);
    Path *path = new Path(maze.Labyrinthe[0][0]);
    find_path(maze.Labyrinthe[0][0], maze.Labyrinthe[1][0], path);
    


}