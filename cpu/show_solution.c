#include "gsa.h"

void show_solution( int n_dim, double best_z, double *best_x )
{
    int d;

    for( d=0; d<n_dim; d++ )
    {
        printf( "x(%d): %f\n", d+1, best_x[d] );
    }

    printf( "\nz: %f\n\n", best_z );
}
