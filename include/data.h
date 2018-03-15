#ifndef DATA_H
#define	DATA_H
#include "GoverningEquations.h"
#include "config.h"
struct Cell 
{
    double U[NUM_RK_STEPS + 1][NUM_VARS]; // Average Conservative variables
    double UWest[NUM_VARS]; // Reconstructed values
    double UEast[NUM_VARS]; // Reconstructed values
    double totalFlux[NUM_VARS];    
    double dx; // width of cell
    double cx; // centroid of cell
};
typedef struct Cell Cell;

typedef enum 
{
    false, true
} bool;
#endif	/* DATA_H */

