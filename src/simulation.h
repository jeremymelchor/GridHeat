#ifndef SIMULATION
#define SIMULATION
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "main.h"
/**
@authors : Jeremy Melchor
Matthieu Perrin
**/
#define TAILLE_MIN 256
#define TAILLE_MAX 67108864
#define NB_MIN_THREAD 1
#define NB_MAX_THREAD 1024
#define TEMP_CHAUD 150
#define TEMP_FROID 0

bool MFLAG;
bool AFLAG;
bool MMFLAG;

int i_min;
int i_max;
int taillePlaque;

struct Param{
	int *p_array;
	int size;
};

void print_plaque(float (*plaque)[taillePlaque]);
void simulation(int puissance_taillePlaque, int nbIterations, int nbThread);
void iterative_way(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque], int nbIterations);
void calculate_grid(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque]);
float vertical(float (*plaque_apres)[taillePlaque], float current_value, int i, int j);
int convertPowToSize(int puissance_taillePlaque);
void update_heat(float (*plaque)[taillePlaque], int i_min, int i_max);

#endif