#include "gsa.h"

void update_agents( int n_pop, int n_dim, double g, double *force, double *x_min, double *x_max, double *velocity, double *position ){
    int d, p;
  
    for( p=0; p<n_pop; p++){
        for(d=0; d<n_dim; d++){
            velocity[d+p*n_dim] = (get_rand() * velocity[d+p*n_dim]) + (g * force[d+p*n_dim]);
	
            if( ((position[d+p*n_dim] + velocity[d+p*n_dim]) < x_min[d]) || ((position[d+p*n_dim] + velocity[d+p*n_dim]) > x_max[d]) ){
                position[d+p*n_dim] = get_rand() * (x_max[d] - x_min[d]) + x_min[d];
            }
            else{
                position[d+p*n_dim] = position[d+p*n_dim] + velocity[d+p*n_dim];
            }
        }
    }
}
