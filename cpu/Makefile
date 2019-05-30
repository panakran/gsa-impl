all: gsa

gsa: get_best_worst.o get_fitness.o get_forces.o get_gconst.o get_inertia_masses.o get_rand.o init_gsa.o init_params.o main.o p_norm_distance.o show_solution.o update_agents.o usage.o save_solution.o timeval_subtract.o de_jong.o sphere.o
	gcc -lm -o gsa get_best_worst.o get_fitness.o get_forces.o get_gconst.o get_inertia_masses.o get_rand.o init_gsa.o init_params.o main.o p_norm_distance.o show_solution.o update_agents.o usage.o save_solution.o timeval_subtract.o de_jong.o sphere.o

get_best_worst.o: get_best_worst.c
	gcc -lm -c get_best_worst.c

get_fitness.o: get_fitness.c
	gcc -lm -c get_fitness.c

get_forces.o: get_forces.c
	gcc -lm -c get_forces.c

get_gconst.o: get_gconst.c
	gcc -lm -c get_gconst.c

get_inertia_masses.o: get_inertia_masses.c
	gcc -lm -c get_inertia_masses.c

get_rand.o: get_rand.c
	gcc -lm -c get_rand.c

init_gsa.o: init_gsa.c
	gcc -lm -c init_gsa.c

init_params.o: init_params.c
	gcc -lm -c init_params.c

main.o: main.c
	gcc -lm -c main.c

p_norm_distance.o: p_norm_distance.c
	gcc -lm -c p_norm_distance.c

show_solution.o: show_solution.c
	gcc -lm -c show_solution.c

update_agents.o: update_agents.c
	gcc -lm -c update_agents.c

usage.o: usage.c
	gcc -lm -c usage.c

save_solution.o: save_solution.c
	gcc -lm -c save_solution.c

square_sum.o: square_sum.c
	gcc -lm -c square_sum.c

timeval_subtract.o: timeval_subtract.c
	gcc -lm -c timeval_subtract.c

de_jong.o: de_jong.c
	gcc -lm -c de_jong.c

sphere.o: sphere.c
	gcc -lm -c sphere.c

clean:
	rm -rf *.o gsa