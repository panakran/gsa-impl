#include "gsa.h"

double get_rand( void ){
    static long int n = 0;

    srand( (unsigned)time(NULL) + n );
    n = n + 1;

    return rand() / ( (double)RAND_MAX + 1 );
}
