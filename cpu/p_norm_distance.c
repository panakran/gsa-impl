#include "gsa.h"

double p_norm_distance( int n_dim, double *k, double *p )
{
    int d;
    double sum=0.0;

    for( d=0; d<n_dim; d++ )
    {
        sum = sum + pow( (k[d] - p[d]), 2 );
    }

    return pow(sum, 0.5);
} 
