#ifndef SOLUTIONRECONSTRUCTOR_H
#define	SOLUTIONRECONSTRUCTOR_H
#include "data.h"
#include "config.h"
void reconstructSolution(Cell cells[], int rkStep) 
{
    int i;
    for (i = NUM_GHOST_CELLS - 1; i < NUM_CELLS + NUM_GHOST_CELLS + 1; i++) 
    {
        // Simple first order reconstruction
        int var;
        for (var = 0; var < NUM_VARS; var++) {
            cells[i].UWest[var] = cells[i].U[rkStep][var];
            cells[i].UEast[var] = cells[i].U[rkStep][var];
        }
    }
}
#endif	/* SOLUTIONRECONSTRUCTOR_H */

