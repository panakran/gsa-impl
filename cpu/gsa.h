#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

//double (*objective_function)( int n_dim, double *x );

void init_params( int , char **, int *, int *, double *, double *, int *, double *, double *, double *, int * );

void usage( void );

double get_rand( void );

void init_gsa( int, int, double, double, double *, double * );

void get_fitness( int, int, double *, double * );

int get_best_worst( int, double *, double *, double * );

double get_gconst( double, double, int, int );

void get_inertia_masses( int, double, double, double *, double *, double * );

void get_forces( int, int, double, double *, double *, double * );

double p_norm_distance( int, double *, double * );

void update_agents( int, int, double, double *, double, double, double *, double * );

void show_solution( int, double, double * );

void save_solution( int, double *, int, double * );

int timeval_subtract(struct timeval *, struct timeval *, struct timeval *);

double fitness_function( int, double * );

// double de_jong( int, double * );
// double sphere( int, double * );