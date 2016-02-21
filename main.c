#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_MIN 256
#define TAILLE_MAX 67108864
#define NB_MIN_THREAD 1
#define NB_MAX_THREAD 1024
#define TEMP_CHAUD 150
#define TEMP_FROID 0

int taillePlaque;
bool MFLAG=false;
bool AFLAG=false;

struct Param{
	int *p_array;
	int size;
};

void print_plaque(float (*plaque)[taillePlaque]) {
	for (int i=0; i<taillePlaque; i++) {
		printf("\n");
		for (int j=0; j<taillePlaque; j++) {
			printf("%.1f     ",plaque[i][j]);
		}
	}
	printf("\n");
}

void init_plaque(float (*plaque)[taillePlaque], int i_min, int i_max) {
	for (int i=0; i<taillePlaque; i++) {
		for (int j=0; j<taillePlaque; j++) {
			if ( (j>=i_min && j<i_max) && (i>=i_min && i<i_max) )
				plaque[i][j] = TEMP_CHAUD;
			else
				plaque[i][j] = TEMP_FROID;
		}
	}
}


int convertPowToSize(int puissance_taillePlaque) {
	return pow(2,(puissance_taillePlaque+4));
}


float vertical(float (*plaque_apres)[taillePlaque], float current_value, int i, int j) {
	if ( (i-1) < 0 ) 
		plaque_apres[i+1][j] += current_value/6;
	else if ( (i+1) >= taillePlaque) 
		plaque_apres[i-1][j] += current_value/6; 
	else {
		plaque_apres[i-1][j] += current_value/6;
		plaque_apres[i+1][j] += current_value/6;
	}
	return current_value -= current_value/3;
}

void calculate_grid(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque]) {
	for (int i=0; i<taillePlaque; i++) {
		for (int j=0; j<taillePlaque; j++) {
			if (plaque_avant[i][j] != TEMP_FROID) {
				if ( (j-1) < 0 ) 
					plaque_apres[i][j+1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j+1);
				else if ( (j+1) >= taillePlaque ) 
					plaque_apres[i][j-1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j-1); 
				else {
					plaque_apres[i][j-1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j-1);
					plaque_apres[i][j+1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j+1);
				}
				float value = plaque_avant[i][j] - plaque_avant[i][j]/3;
				plaque_apres[i][j] += vertical(plaque_apres,value, i, j);
			}
			//print_plaque(plaque_apres);
		}
	}
}

void matrix_copy(float (*dest)[taillePlaque], float (*src)[taillePlaque]) {
	memcpy(dest, src, taillePlaque*taillePlaque*sizeof(float));
}

void iterative_way(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque], int nbIterations) {
	for (int i=0; i<nbIterations; i++) {
		calculate_grid(plaque_avant, plaque_apres);
		matrix_copy(plaque_avant, plaque_apres);
		print_plaque(plaque_apres);
		memset(plaque_apres,0,taillePlaque*taillePlaque*sizeof(float));
		if(!MFLAG){
			print_plaque(plaque_apres);
		}
	}
}


void simulation(int puissance_taillePlaque, int nbIterations, int nbThread) {
	taillePlaque = convertPowToSize(puissance_taillePlaque);

	if (taillePlaque*taillePlaque > TAILLE_MAX || taillePlaque*taillePlaque < TAILLE_MIN) {
		if (!MFLAG) {
			printf("%d\n",taillePlaque*taillePlaque);
			printf("Taille de la plaque trop grande\n");
		}
		exit(0);
	}

	float plaque_avant[taillePlaque][taillePlaque];
	float plaque_apres[taillePlaque][taillePlaque];
	memset(plaque_apres,0,taillePlaque*taillePlaque*sizeof(float));

	int i_min = pow(2,sqrt(taillePlaque)-1) - pow(2,sqrt(taillePlaque)-4);
	int i_max = pow(2,sqrt(taillePlaque)-1) + pow(2,sqrt(taillePlaque)-4);

	init_plaque(plaque_avant, i_min, i_max);

	if (nbThread == 1) {
		iterative_way(plaque_avant, plaque_apres, nbIterations);
	}
	else {
		printf("Pas encore géré !");
		exit(0);
	}
}

void display_options(int nb_iterations,struct Param *program_step,struct Param *num_threads,struct Param *nb_case_per_line,bool MFLAG, bool AFLAG){
	int index = 0;

	printf("NB of iterations: %d\n",nb_iterations);

	if(program_step->size != 0){
		printf("Steps to be executed:\n");
		while (index < program_step->size ) {
			printf("%d", program_step->p_array[index]);
			index++;
		}
		puts("");
		index = 0;
	}

	if(num_threads->size != 0){
		printf("Numbers of threads:\n");
		while (index < num_threads->size) {
			printf("%d", num_threads->p_array[index]);
			index++;
		}
		puts("");
		index = 0;
	}

	if(nb_case_per_line->size != 0){
		printf("Size of the grid:\n");
		while (index < nb_case_per_line->size ) {
			printf("%d", nb_case_per_line->p_array[index]);
			index++;
		}
		puts("");
	}

	printf("MFLAG: %d\n",MFLAG);

	printf("AFLAG: %d\n",AFLAG);
}

int main(int argc, char *argv[]) {

	int nb_iterations = 2;

	struct Param program_step;
	program_step.size=0;
	struct Param num_threads;
	num_threads.size=0;

	struct Param nb_case_per_line;
	nb_case_per_line.size=0;


	

	for (int i =1; i<argc; i++) {
		// Récupération de la taille du problème
		if (strcmp(argv[i],"-s") == 0) {
			char *s_param = argv[i+1];
			//récuperer les différentes tailles dans un tableau de int
			int index = 0;
			nb_case_per_line.p_array =(int*) malloc(((int)strlen(s_param)*sizeof(int)));

			while (s_param[index] != '\0') {
				//et on range les int dedans
				char num = s_param[index] - '0';
				//printf("%d\n", (int)num);
				nb_case_per_line.p_array[index] = (int)num;
				//printf("%d\n", nb_case_per_line.p_array[index]);
				//printf("%d\n",nb_case_per_line[index]);
				//on construit le tableau à la bonne taille
				nb_case_per_line.p_array = realloc(nb_case_per_line.p_array,((int)strlen(s_param)*sizeof(int)));

				index++;
			}
			nb_case_per_line.size = index;
			i++;
		}
		if (strcmp(argv[i],"-m") == 0) {
			//mode execution
			MFLAG=true;
		}
		if (strcmp(argv[i],"-a") == 0) {
			AFLAG=true;

		}
		if (strcmp(argv[i],"-i") == 0) {
			nb_iterations = atoi(argv[i+1]);
		}
		if (strcmp(argv[i],"-e") == 0) {
			int index = 0;
			char *e_param = argv[i+1];
			program_step.p_array = (int*) malloc(((int)strlen(e_param)*sizeof(int)));

			while (e_param[index] != '\0') {
				//et on range les int dedans
				char num = e_param[index] - '0';

				program_step.p_array[index] = (int)num;
				//on construit le tableau à la bonne taille
				program_step.p_array = realloc(program_step.p_array,((int)strlen(e_param))*sizeof(int));
				index++;
			}
			program_step.size = index;
		}
		if (strcmp(argv[i],"-t") == 0) {
			int index = 0;
			char *t_param = argv[i+1];
			num_threads.p_array = (int*) malloc(((int)strlen(t_param)*sizeof(int)));

			while (t_param[index] != '\0') {
				//on construit le tableau à la bonne taille
				//et on range les int dedans
				char num = t_param[index] - '0';
				num_threads.p_array[index] = (int)num;
				num_threads.p_array = realloc(num_threads.p_array,((int)strlen(t_param))*sizeof(int));

				index++;
			}
			num_threads.size = index;
		}

	}

	if(!MFLAG){
		display_options(nb_iterations,&program_step,&num_threads,&nb_case_per_line,MFLAG,AFLAG);
	}
	simulation(0,nb_iterations,NB_MIN_THREAD);
}

