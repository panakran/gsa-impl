#include "gsa.h"

double de_jong( int n_dim, double *x ){
    int d;
    double sum=0.0;

    for( d=0; d<n_dim; d++ ){
        sum = sum + pow(x[d], 2);
    }

    return sum;
}
