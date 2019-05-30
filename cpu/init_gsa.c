#include "gsa.h"

void init_gsa( int n_pop, int n_dim, double min, double max, double *x_min, double *x_max, double *velocity, double *position ){
    int p, d;

    // Boundaries
    for( d=0; d<n_dim; d++ ){
        x_min[d] = min;
        x_max[d] = max;
    }

    // Agents
    for( p=0; p<n_pop; p++ ){
        for( d=0; d<n_dim; d++ ){
            // Position
            position[d+p*n_dim] = get_rand() * (x_max[d] - x_min[d]) + x_min[d];

            // Velocity
            velocity[d+p*n_dim] = 0.0;
        }
    }
}
