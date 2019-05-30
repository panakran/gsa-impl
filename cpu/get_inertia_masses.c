#include "gsa.h"

void get_inertia_masses( int n_pop, double best, double worst, double *fitness, double *mass, double *inertia_mass )
{
    int p;
    double sum=0.0;

    // Mass
    for( p=0; p<n_pop; p++)
    {
        if( best == worst )
            mass[p] = 1.0;
        else
            mass[p] = (fitness[p] - worst) / (best - worst);

        sum = sum + mass[p];
    }

    // Inertia mass
    for( p=0; p<n_pop; p++)
    {
        inertia_mass[p] = mass[p] / sum;
    }
}
