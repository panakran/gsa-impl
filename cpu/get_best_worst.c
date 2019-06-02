#include "gsa.h"

int get_best_worst( int n_pop, double *fitness, double *best, double *worst ){
    printf( "\n---get_best_worst");
    int p, i=0;
    double fmin = fitness[0], fmax = fitness[0];

    for( p=1; p<n_pop; p++ ){
        if( fitness[p] < fmin ){
            fmin = fitness[p];
            i = p;
        }

        if( fitness[p] > fmax )
        fmax = fitness[p];
    }
    
    printf( "\n b-w for i:%d is %f-%f", i, *best, *worst);
    *best = fmin; *worst = fmax;
    return i;
}
