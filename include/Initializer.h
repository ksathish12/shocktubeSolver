#ifndef INITIALIZER_H
#define	INITIALIZER_H
#include "data.h"
#include "config.h"
#include "FluidProperties.h"


void initializeSolution(Cell cells[]) 
{
    printf("\nInitializing solution in the domain...");
    // shock tube problem
    //double pressureLeft = 10 * 101325.0;
    double pressureLeft = 300000.0;
    double temperatureLeft = 288.0;
    double uLeft = 0.0;
    double rhoLeft = EOS_RHO(pressureLeft, temperatureLeft);
    double consVarLeft[NUM_VARS];
    double primVarLeft[] = {rhoLeft, uLeft, pressureLeft};
    primitiveToConservative(primVarLeft, consVarLeft);

    //double pressureRight = 1 * 101325.0;
    double pressureRight = 30000;
    double temperatureRight = 288.0;
    double uRight = 0.0;
    double rhoRight = EOS_RHO(pressureRight, temperatureRight);
    double consVarRight[NUM_VARS];
    double primVarRight[] = {rhoRight, uRight, pressureRight};
    primitiveToConservative(primVarRight, consVarRight);

    const int rkStep = 0;
    int i;
    for (i = 0; i < NUM_CELLS + 2 * NUM_GHOST_CELLS; i++) 
    {
        double x = cells[i].cx;
        int var;
        for (var = 0; var < NUM_VARS; var++) 
        {
            if (x < 0.0) 
            {
                cells[i].U[rkStep][var] = consVarLeft[var];
            } 
            else 
            {
                cells[i].U[rkStep][var] = consVarRight[var];
            }
        }
    }
    printf(" done.");
}
#endif	/* INITIALIZER_H */

