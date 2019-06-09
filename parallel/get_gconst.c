#include "gsa.h"

double get_gconst( double alpha, double g0, int i, int max_i ){
    // printf( "\n---get_gconst");
    // printf( "\n new G const at iteration %d:%f", i, ( g0 * exp(-alpha * i/max_i) ));
    return ( g0 * exp(-alpha * i/max_i) );
}
