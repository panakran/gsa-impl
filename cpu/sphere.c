#include "gsa.h"

double sphere( int n_dim, double *x )
{
    int d;
    double sum=0.0;

    for( d=0; d<n_dim; d++ )
    {
        sum = sum + ( (d+1) * pow(x[d], 2) );
    }

    return sum;
}
