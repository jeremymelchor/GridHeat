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
	printf("%li\n",sizeof(test));

	for (int i =0; i<argc; i++) {
		// Récupération des différentes tailles du problème
		if (strcmp(argv[i],"-s") == 0) {
			char *liste_taille_probleme = argv[i+1];
			int iterateur = 0;

			int *memoireAllouee = NULL;
			memoireAllouee = malloc(sizeof(int));
			if (memoireAllouee == NULL) exit(0);

			while (liste_taille_probleme[iterateur] != '\0') {
				memoireAllouee[iterateur] = liste_taille_probleme[iterateur] - '0';
				printf("%d\n",memoireAllouee[iterateur]);
			 	memoireAllouee = realloc(memoireAllouee, (iterateur+2)*sizeof(int));
			 	iterateur++;
			}
			printf("%d\n",sizeof(memoireAllouee));
			//int j=0;
			//while (memoireAllouee[j]!='\0') printf("%d\n",memoireAllouee[j]);
		}
	}
}