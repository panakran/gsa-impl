#include "gsa.h"

void init_params( int argc, char **argv, int *n_pop, int *n_dim, double *min, double *max, int *max_i, double *alpha, double *g0, double *epsilon, int *func )
{
    char c;

    while( (c = getopt(argc, argv, "a:d:x:X:i:A:G:e:f:h")) != -1 )
    {
        switch( c )
        {
            case 'a':
                *n_pop = atoi(optarg);
                break;
            case 'd':
                *n_dim = atoi(optarg);
                break;
            case 'x':
                *min = atof(optarg);
                break;
            case 'X':
                *max = atof(optarg);
                break;
            case 'i':
                *max_i = atoi(optarg);
                break;
            case 'A':
                *alpha = atof(optarg);
                break;
            case 'G':
                *g0 = atof(optarg);
                break;
            case 'e':
                *epsilon = atof(optarg);
                break;
            case 'f':
                *func = atoi(optarg);
                break;
            case 'h':
                usage();
                break;
            default:
                usage();
                break;
        }
    }

    if( argc < 8 )
    {
        exit(EXIT_FAILURE);
    }
}
