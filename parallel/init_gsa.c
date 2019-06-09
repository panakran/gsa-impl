#include "gsa.h"

void init_gsa( int n_pop, int n_dim, double min, double max, double *x_min, double *x_max, double *velocity, double *position ){
    // printf( "\---ninit_gsa\n");
    // printf( "\nparams: n_pop: %d, n_dim: %d, min: %f, max: %f", n_pop,  n_dim,  min,  max,  *x_min,  *x_max,  *velocity,  *position );
    
    
    int p, d;

    // Boundaries
    for( d=0; d<n_dim; d++ ){
        x_min[d] = min;
        x_max[d] = max;
    //printf( "\n d: %d, x_min: %f, x_max: %f", d, x_min[d], x_max[d]);
    }

    // Agents
    for( p=0; p<n_pop; p++ ){
        for( d=0; d<n_dim; d++ ){
            // Position
            position[d+p*n_dim] = get_rand() * (x_max[d] - x_min[d]) + x_min[d];
            //printf( "\nStarting position of %d at dimesion %d::%f", p, d, position[d+p*n_dim]);
            // Velocity
            velocity[d+p*n_dim] = 0.0;
        }
    }
}
