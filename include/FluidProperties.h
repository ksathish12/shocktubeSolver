#ifndef FLUIDPROPERTIES_H
#define	FLUIDPROPERTIES_H
#define GAMMA 1.4
#define R 287.0
#define CV (R / (GAMMA - 1.0))

double EOS_P(double rho, double temperature) 
{
    return rho * R * temperature;
}
double EOS_T(double p, double rho) 
{
    return p / rho / R;
}

double EOS_RHO(double p, double temperature) 
{
    return p / R / temperature;
}
#endif	/* FLUIDPROPERTIES_H */

