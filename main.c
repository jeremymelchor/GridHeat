#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAILLE_MIN 256
#define TAILLE_MAX 67108864
#define NB_MIN_THREAD 1
#define NB_MAX_THREAD 1024
#define TEMP_CHAUD 150
#define TEMP_FROID 0

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

int main(int argc, char *argv[]) {
	//int a = atoi(argv[1]);
	//simulation(a,0,0);

	int *test = NULL;
	test = malloc(10*sizeof(int));
	printf("size: %i\n",sizeof(test));

	float **grid;
	int nb_iterations=10000;
	int program_step= NULL;
	int num_threads= NULL;

	for (int i =0; i<argc; i++) {
		// Récupération de la taille du problème
		if (strcmp(argv[i],"-s") == 0) {
			char *s_param = argv[i+1];
			//récuperer les différentes tailles dans un tableau de int
			int *nb_case_per_line = NULL;			
			int index = 0;

			while (s_param[index] != '\0') {
				nb_case_per_line = malloc(((int)strlen(s_param))*sizeof(int));
				nb_case_per_line[index] = atoi(&s_param[index]);
				index++;
			}
			
			/*//A DEPLACER//////////////////
			//on crée la dimension 1;
			grid = malloc(nb_case_per_line*sizeof(float*));
			//puis les lignes dimension 2
			for(int i = 0 ; i < nb_case_per_line;i++){
				grid[i] = malloc(nb_case_per_line*sizeof(float));
			}
			//////////////////////////////*/
		}
		if (strcmp(argv[i],"-m") == 0) {
			//mode execution
		}
		if (strcmp(argv[i],"-a") == 0) {

		}
		if (strcmp(argv[i],"-i") == 0) {
			nb_iterations = atoi(argv[i]);
		}
		if (strcmp(argv[i],"-e") == 0) {
			program_step = atoi(argv[i]);
		}
		if (strcmp(argv[i],"-t") == 0) {
			num_threads = atoi(argv[i]);
		}

	}
}