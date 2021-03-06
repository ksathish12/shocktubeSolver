#ifndef GOVERNINGEQUATIONS_H
#define	GOVERNINGEQUATIONS_H
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "FluidProperties.h"
#define NUM_VARS 3
#define MAX_VAR_NAME_LENGTH 50
char** getConservativeVariableNames(char* names[]) 
{
    char* consVarNames[] = 
    {
        "rho", "rho u", "E"
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        strcpy(names[var], consVarNames[var]);
    }
    return names;
}
char** getPrimitiveVariableNames(char* names[]) 
{
    char* primVarNames[] = 
    {
        "rho", "u", "p"
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        strcpy(names[var], primVarNames[var]);
    }
    return names;
}
void conservativeToPrimitive(double conservativeVariables[], double* primitiveVariables) 
{
    double rho = conservativeVariables[0];
    double rho_u = conservativeVariables[1];
    double E = conservativeVariables[2];
    double u = rho_u / rho;
    double kineticEnergy = u * u / 2.0;
    double specEnergy = E / rho;
    double internalEnergy = specEnergy - kineticEnergy;
    double T = internalEnergy / CV;
    double p = EOS_P(rho, T);
    double vars[] = 
    {
        rho, u, p
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        primitiveVariables[var] = vars[var];
    }
}
void primitiveToConservative(double primitiveVariables[], double* conservativeVariables) 
{
    double rho = primitiveVariables[0];
    double u = primitiveVariables[1];
    double p = primitiveVariables[2];
    double T = EOS_T(p, rho);
    double internalEnergy = CV * T;
    double kineticEnergy = u * u / 2.0;
    double specEnergy = internalEnergy + kineticEnergy;
    double vars[] = 
    {
        rho, rho * u, rho * specEnergy
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        conservativeVariables[var] = vars[var];
    }
}
void F(double U[], double* F) 
{
    double primVar[NUM_VARS];
    conservativeToPrimitive(U, primVar);
    double rho = primVar[0];
    double u = primVar[1];
    double p = primVar[2];
    double E = U[2];
    double flux[] = 
    {
        rho * u,
        rho * u * u + p,
        (E + p) * u
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        F[var] = flux[var];
    }
}

void ausm_flux(double U[], double* F) 
{
    double primVar[NUM_VARS];
    conservativeToPrimitive(U, primVar);
    double rho = primVar[0];
    double u = primVar[1];
    double p = primVar[2];
    double E = U[2];
    double conv_flux[] = 
    {
        rho * u,
        rho * u * u,
        (E + p) * u
    };
    double press_flux[] = 
    {
        0,
        p,
        0
    };
    int var;
    for (var = 0; var < NUM_VARS; var++) 
    {
        F[var] = conv_flux[var]+press_flux[var];
    }
}
double getMaxAbsEigenValue(double U[]) 
{
    double primVar[NUM_VARS];
    conservativeToPrimitive(U, primVar);
    double rho = primVar[0];
    double u = primVar[1];
    double p = primVar[2];
    return fabs(u) + sqrt(GAMMA * p / rho);
}
#endif	/* GOVERNINGEQUATIONS_H */

