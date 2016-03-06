#ifndef MAIN
#define MAIN
#include "simulation.h"

/**
@authors : Jeremy Melchor
Matthieu Perrin
**/
int taillePlaque;
struct Param{
	int *p_array;
	int size;
};
void init_plaque(float (*plaque)[taillePlaque], int i_min, int i_max);
void display_options(int nb_iterations,struct Param *program_step,struct Param *num_threads,struct Param *nb_case_per_line,bool MFLAG, bool AFLAG);
void chercherMoyenne(double *time_spent);

#endif