#include "gsa.h"

void init_gsa( int n_pop, int n_dim, double min, double max, double *velocity, double *position ){
    printf( "\n---init_gsa\n");
    printf( "\nparams: n_pop: %d, n_dim: %d, min: %f, max: %f", n_pop,  n_dim,  min,  max,  *velocity,  *position );
    
    
    int p, d;

    // Agents
    for( p=0; p<n_pop; p++ ){
        for( d=0; d<n_dim; d++ ){
            // Position
            position[d+p*n_dim] = get_rand() * (max - min) + min;
            printf( "\nStarting position of %d at dimesion %d::%f", p, d, position[d+p*n_dim]);
            // Velocity
            velocity[d+p*n_dim] = 0.0;
        }
    }
}
