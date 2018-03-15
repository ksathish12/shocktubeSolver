#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "data.h"
#include "SetupCellGeometryData.h"
#include "Initializer.h"
#include "FluidProperties.h"
#include "TimeStepCalculator.h"
#include "GhostCellUpdater.h"
#include "TimeIntegrator.h"
#include "SolutionReconstructor.h"
#include "FluxCalculator.h"
//#include "debug.h"
#include "FileWriter.h"
#include "SolutionCopier.h"

int main(int argc, char** argv) 
{    
    Cell cells[NUM_CELLS + 2 * NUM_GHOST_CELLS]; // Create cell array, Set dx, cx
    setUpGeometry(cells);    
    initializeSolution(cells);  // Initialize all cells
    bool lastTimeStep = false;
    double time = 0.0;    
    long timeIter;
    printf("\nStarting time iterations...\n");
    for (timeIter = 0; timeIter < MAX_TIME_ITER; timeIter++) // time loop, timeIter = [0 ... MAX_TIME_ITER]:
    {        
        double dt = getTimeStep(cells); // calculate dt based on CFL
        if (time + dt > STOPPING_TIME)
        {
            dt = STOPPING_TIME - time;
            lastTimeStep = true;
        }
        // For each Runge-Kutta intermediate step
        int rkStep;
        for (rkStep = 0; rkStep < NUM_RK_STEPS; rkStep++) 
        {
            updateGhostCells(cells, rkStep);
            reconstructSolution(cells, rkStep);
            calculateFlux(cells, rkStep);
            updateCells(cells, rkStep, dt);
        }        
        copyBackToLevelN(cells);// copy cell values from (n+1) to n
        time = time + dt;
        printf("\ntime = %.4e, dt = %.4e", time, dt);
        if (lastTimeStep)
        {
            break;
        }
    }

    printf("\nTime iterations done.\n");
    writeSolutionToFile(cells);
    return (EXIT_SUCCESS);
}

