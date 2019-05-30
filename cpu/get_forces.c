#include "gsa.h"

void get_forces( int n_pop, int n_dim, double epsilon, double *position, double *intertia_mass, double *force )
{
    int d, p, k;
    double r;

    for( p=0; p<n_pop; p++ )
    {
        for( d=0; d<n_dim; d++ )
        {
            force[d+p*n_dim] = 0.0;

            for( k=0; k<n_pop; k++ )
            {
                if( k != p )
                {
                    r = p_norm_distance( n_dim, &position[k*n_dim], &position[p*n_dim] );

                    force[d+p*n_dim] = force[d+p*n_dim] + ( get_rand() * intertia_mass[k] * (position[d+k*n_dim] - position[d+p*n_dim]) / (r + epsilon) );
                }
            }
        }
    }
}
