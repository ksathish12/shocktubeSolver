#ifndef SETUPCELLGEOMETRYDATA_H
#define	SETUPCELLGEOMETRYDATA_H    
#include "data.h"    
void setUpGeometry(Cell cells[]) 
{
    printf("\nSetting up the cell geometry data...");
    int i;
    double dx = (MAX_X - MIN_X) / NUM_CELLS;
    double half_dx = dx / 2.0;
    for (i = -NUM_GHOST_CELLS; i < NUM_CELLS + NUM_GHOST_CELLS; i++) 
    {
        struct Cell* cell = (cells + i + NUM_GHOST_CELLS);
        cell -> cx = MIN_X + i * dx + half_dx;
        cell -> dx = dx;
    }
    printf(" done.");
}
#endif	/* SETUPCELLGEOMETRYDATA_H */

