#include "gsa.h"

int get_best_worst( int n_pop, double *fitness, double *best, double *worst )
{
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
    
    *best = fmin; *worst = fmax;
    return i;
}
