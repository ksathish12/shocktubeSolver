#ifndef FLUXCALCULATOR_H
#define	FLUXCALCULATOR_H
#include "config.h"
#include "GoverningEquations.h"
#include "data.h"
//#include "debug.h"
#define GAMMA 1.4

void laxFriedrichRiemannSolver(double UL[], double UR[], double* flux) 
{
    double FL[NUM_VARS];
    double FR[NUM_VARS];
    F(UL, FL);
    F(UR, FR);
    double maxWaveSpeed = fmax(getMaxAbsEigenValue(UL), getMaxAbsEigenValue(UR));
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        flux[var] = 0.5 * (FL[var] + FR[var]) - 0.5 * maxWaveSpeed * (UR[var] - UL[var]);
    }
}
void calculateFlux(Cell cells[], int rkStep) 
{
    int i;
    for (i = 0; i < NUM_CELLS + 2 * NUM_GHOST_CELLS; i++) 
    {
        int var;
        for (var = 0; var < NUM_VARS; var++) 
        {
            cells[i].totalFlux[var] = 0.0;
        }
    }
    double flux[NUM_VARS];
    int cellInterface;
    for (cellInterface = NUM_GHOST_CELLS; cellInterface < NUM_CELLS + NUM_GHOST_CELLS + 1; cellInterface++) 
    {
        double* UL = cells[cellInterface - 1].UEast;
        double* UR = cells[cellInterface].UWest;
        laxFriedrichRiemannSolver(UL, UR, flux);
        int var;
        for (var = 0; var < NUM_VARS; var++) 
        {
            cells[cellInterface - 1].totalFlux[var] += flux[var];
            cells[cellInterface].totalFlux[var] -= flux[var];
        }
    }
}
#endif	/* FLUXCALCULATOR_H */

