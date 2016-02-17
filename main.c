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

struct Param{
	int *p_array;
	int size;
};

// void init_plaque(float **plaque, int taillePlaque, int i_min, int i_max) {
// 	for (int i=0; i<taillePlaque; i++) {
// 		for (int j=0; j<taillePlaque; j++) {
// 			if (i>i_min && i<i_max)
// 				plaque[i][j] = TEMP_CHAUD;
// 			else
// 				plaque[i][j] = TEMP_FROID;
// 		}
// 	}
// }

int simulation(int taillePlaque, int nbIterations, int nbThread) {
	if (taillePlaque*taillePlaque > TAILLE_MAX || taillePlaque*taillePlaque < TAILLE_MIN) {
		printf("%d\n",taillePlaque*taillePlaque);
		printf("Taille de la plaque trop grande\n");
		exit(0);
	}

	float plaque[taillePlaque][taillePlaque];
	int i_min = pow(2,taillePlaque-1) - pow(2,taillePlaque-4);
	int i_max = pow(2,taillePlaque-1) + pow(2,taillePlaque-4);
	printf("%d i_min : \n",i_min);
	printf("%d i_max : \n",i_max);

	//init_plaque(plaque, taillePlaque, i_min, i_max);

	for (int i=0; i<taillePlaque; i++) {
		for (int j=0; j<taillePlaque; j++) {
			printf("%f\n",plaque[i][j]);
		}
	}

	return 0;
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

	float **grid;
	int nb_iterations=10000;

	struct Param program_step;
	program_step.size=0;
	struct Param num_threads;
	num_threads.size=0;

	struct Param nb_case_per_line;
	nb_case_per_line.size=0;


	bool MFLAG=false;
	bool AFLAG=false;

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
				realloc(nb_case_per_line.p_array,((int)strlen(s_param)*sizeof(int)));

				index++;
			}
			nb_case_per_line.size= index;

			/*//A DEPLACER//////////////////
			//on crée la dimension 1;
			grid = malloc(nb_case_per_line*sizeof(float*));
			//puis les lignes dimension 2
			for(int i = 0 ; i < nb_case_per_line;i++){
			grid[i] = malloc(nb_case_per_line*sizeof(float));
			}
			//////////////////////////////*/
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
			nb_iterations = atoi(argv[i]);
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
				realloc(program_step.p_array,((int)strlen(e_param))*sizeof(int));
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
				realloc(num_threads.p_array,((int)strlen(t_param))*sizeof(int));

				index++;
			}
			num_threads.size = index;
		}

	}

	display_options(nb_iterations,&program_step,&num_threads,&nb_case_per_line,MFLAG,AFLAG);
}

