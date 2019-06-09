#include "gsa.h"

int main( int argc, char **argv ){
    int best_idx, d, c, z;
    int n_pop=5, n_dim=2, i=0, max_i=100, func=1;
    double min=0.0, max=0.0, alpha=20, g0=100, epsilon=0.1;
    double g, best, worst, best_z;
    double *position, *velocity, *acceleration, *x_min, *x_max, *fitness, *mass, *inertia_mass, *force, *best_x;
    struct timeval tvBegin, tvEnd, tvDiff;
    // Initialize
    init_params( argc, argv, &n_pop, &n_dim, &min, &max, &max_i, &alpha, &g0, &epsilon, &func );

    //////////////////////////////////////////////////
    double *buffer_position, *buffer_velocity, *buffer_acceleration, *buffer_fitness, *buffer_mass, *buffer_inertia_mass, *buffer_force;
    
    int rank, size;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    printf( "Hello World from process %d of %d\n", rank, size );

    buffer_position = (double *) calloc( n_pop/size * n_dim, sizeof(double) );
    buffer_velocity = (double *) calloc( n_pop/size * n_dim, sizeof(double) );
    buffer_acceleration = (double *) calloc( n_pop/size * n_dim, sizeof(double) );
    buffer_fitness = (double *) calloc( n_pop/size, sizeof(double) );
    buffer_mass = (double *) calloc( n_pop/size, sizeof(double) );
    buffer_inertia_mass = (double *) calloc( n_pop/size, sizeof(double) );
    buffer_force = (double *) calloc( n_pop/size * n_dim, sizeof(double) );
    //////////////////////////////////////////////////



    if( func == 1 ) objective_function = &de_jong;
    else if( func == 2 ) objective_function = &sphere;
    else return -1;

    position = (double *) calloc( n_pop * n_dim, sizeof(double) );
    velocity = (double *) calloc( n_pop * n_dim, sizeof(double) );
    acceleration = (double *) calloc( n_pop * n_dim, sizeof(double) );
    x_min = (double *) calloc( n_dim, sizeof(double) );
    x_max = (double *) calloc( n_dim, sizeof(double) );
    fitness = (double *) calloc( n_pop, sizeof(double) );
    mass = (double *) calloc( n_pop, sizeof(double) );
    inertia_mass = (double *) calloc( n_pop, sizeof(double) );
    force = (double *) calloc( n_pop * n_dim, sizeof(double) );
    best_x = (double *) calloc( n_dim, sizeof(double) );

    gettimeofday(&tvBegin, NULL);

    //FIXME BCAST GLOBALS
    init_gsa( n_pop, n_dim, min, max, x_min, x_max, velocity, position );

    // Start iterations
    while( i<max_i ){

        // Scatter agents
        MPI_Scatter(position, n_pop/size, MPI_DOUBLE, buffer_position, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(fitness, n_pop/size, MPI_DOUBLE, buffer_fitness, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Update fitness
        get_fitness( n_pop/size, n_dim, buffer_position, buffer_fitness );
        // printf( "\n\nPROCESS World from process %d of %d\n", rank, size );
        // for(d=0; d<n_pop/size; d++ ){
        //     printf( "\nStarting position of %d update fitness %f::%f", buffer_position[d], buffer_fitness[d]);
        // }
        //Gather agents
        MPI_Gather(buffer_position, n_pop/size, MPI_DOUBLE, position, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_fitness, n_pop/size, MPI_DOUBLE, fitness, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if(rank==0){ //FIXME best worst need to BCAST
            // Get G constant
            g = get_gconst( alpha, g0, i, max_i );

            // Get best & worst fitness    
            best_idx = get_best_worst( n_pop, fitness, &best, &worst );

            // Save best solution
            if( (i == 0) || (best < best_z) ){
                best_z = best;
                save_solution( n_dim, position, best_idx, best_x );
            }
        }
        MPI_Bcast(&best, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&worst, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Scatter agents
        MPI_Scatter(fitness, n_pop/size, MPI_DOUBLE, buffer_fitness, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(mass, n_pop/size, MPI_DOUBLE, buffer_mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(inertia_mass, n_pop/size, MPI_DOUBLE, buffer_inertia_mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Calculate inertia masses
        get_inertia_masses( n_pop/size, best, worst, buffer_fitness, buffer_mass, buffer_inertia_mass );
        // printf( "\n\ninertia mass %d of %d\n", rank, size );
        // for(d=0; d<n_pop/size; d++ ){
        //     printf( "\ninertia mass %d update fitness %f::%f::%f", d, buffer_fitness[d], buffer_mass[d], buffer_inertia_mass[d]);
        // }

        //Gather agents
        MPI_Gather(buffer_fitness, n_pop/size, MPI_DOUBLE, fitness, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_mass, n_pop/size, MPI_DOUBLE, mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_inertia_mass, n_pop/size, MPI_DOUBLE, inertia_mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);


        // Scatter agents
        MPI_Scatter(position, n_pop/size, MPI_DOUBLE, buffer_position, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(inertia_mass, n_pop/size, MPI_DOUBLE, buffer_inertia_mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(force, n_pop/size, MPI_DOUBLE, buffer_force, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Scatter(velocity, n_pop/size, MPI_DOUBLE, buffer_velocity, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        // Calculate forces
        get_forces( n_pop/size, n_dim, epsilon, buffer_position, buffer_inertia_mass, buffer_force );

        // Update agents
        update_agents( n_pop/size, n_dim, g, buffer_force, x_min, x_max, buffer_velocity, buffer_position );

        printf( "\n\nUpdate agents %d of %d\n", rank, size );
        for(d=0; d<n_pop/size; d++ ){
            printf( "\nUpdate agents %d update fitness %f::%f::%f::%f",
            d, buffer_position[d], buffer_inertia_mass[d], buffer_force[d], buffer_velocity[d]);
        }

         //Gather agents
        MPI_Gather(buffer_position, n_pop/size, MPI_DOUBLE, position, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_inertia_mass, n_pop/size, MPI_DOUBLE, inertia_mass, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_force, n_pop/size, MPI_DOUBLE, force, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Gather(buffer_velocity, n_pop/size, MPI_DOUBLE, velocity, n_pop/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        i++;
    }
    if(rank==0){
        gettimeofday(&tvEnd, NULL);
        timeval_subtract(&tvDiff, &tvEnd, &tvBegin);

        // Show best solution
        printf( "\nAfter %d iterations...\n\n", max_i );
        show_solution( n_dim, best_z, best_x );  
        printf("t: %ld.%06ld s\n\n", tvDiff.tv_sec, tvDiff.tv_usec);
    }
    free( position ); free( velocity ); free( acceleration ); free( x_min ); free( x_max ); 
    free( fitness ); free( mass ); free( inertia_mass ); free( force ); free( best_x );

    free( buffer_position ); free( buffer_velocity ); free( buffer_acceleration );
    free( buffer_fitness ); free( buffer_mass ); free( buffer_inertia_mass ); free( buffer_force );

    MPI_Finalize();
    return 0;
}
