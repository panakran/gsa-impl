#include "gsa.h"

void get_fitness( int n_pop, int n_dim, double *position, double *fitness ){
    int p;
    for( p=0; p<n_pop; p++ ){
        fitness[p] = objective_function( n_dim, &position[p*n_dim] );
    }
}
