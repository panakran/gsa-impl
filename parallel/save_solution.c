#include "gsa.h"

void save_solution( int n_dim, double *position, int best_idx, double *solution ){
    int d;

    //printf( "\n---save_solution");
    
    
    for( d=0; d<n_dim; d++ ){
        solution[d] = position[d+best_idx*n_dim];
        //printf( "\nsolution for dimension %d ::%f", d, solution[d]);
    }
}
