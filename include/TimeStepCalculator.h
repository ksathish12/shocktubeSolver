#ifndef TIMESTEPCALCULATOR_H
#define	TIMESTEPCALCULATOR_H
#include "data.h"
#include "config.h"
#include "GoverningEquations.h"
double getTimeStep(Cell cells[]) 
{
    const int rkStep = 0;    
    double dx = cells[0].dx; // assuming that dx is uniform
    double min_dt = dx / getMaxAbsEigenValue(cells[0].U[rkStep]);
    int i;
    for (i = 0; i < NUM_CELLS + 2 * NUM_GHOST_CELLS; i++) 
    {
        double dt = dx / getMaxAbsEigenValue(cells[i].U[rkStep]);
        if (dt < min_dt) 
        {
            min_dt = dt;
        }
    }
    return min_dt * CFL;
}
#endif	/* TIMESTEPCALCULATOR_H */

