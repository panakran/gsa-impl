#include "gsa.h"

double get_gconst( double alpha, double g0, int i, int max_i ){
    return ( g0 * exp(-alpha * i/max_i) );
}
