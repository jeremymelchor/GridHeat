#include "main.h"
/**
@authors : Jeremy Melchor
Matthieu Perrin
**/



/* Initialise la plaque avec TEMP_CHAUD au milieu et le reste a TEMP_FROID */
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

/* Affiche les options avec lesquelles on a lance le programme */
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

/*Fonction qui permet d'afficher la moyenne des 10 executions quand l'option -M*/
void chercherMoyenne(double *time_spent){
	double max=0,max2=0;
	int indice1, indice2;
	for(int i=0; i < 10; i++){
		if(time_spent[i] > max){
			max = time_spent[i];
			indice1 = i;
		}
		if(time_spent[i] > max2 && time_spent[i] != max){
			max2= time_spent[i];
			indice2 = i;
		}
	}
	time_spent[indice1] = -1;
	time_spent[indice2] = -1;

	double moy=0;
	for(int i=0; i < 10; i++){
		if(time_spent[i] > 0){
			moy += time_spent[i];
		}
	}
	moy = moy/8;

	printf("Moyenne : %G\n", moy);

}

/* La recuperation des parametres se fait dans le main */
int main(int argc, char *argv[]) {

	int nb_iterations = 10000;

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
				nb_case_per_line.p_array[index] = (int)num;
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
		if (strcmp(argv[i],"-M") == 0) {
			//mode stats
			MMFLAG=true;
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

	if(MFLAG) 
		display_options(nb_iterations,&program_step,&num_threads,&nb_case_per_line,MFLAG,AFLAG);

	clock_t begin, end;
	double time_spent[10];
	int limit,i=0;

	if(MMFLAG)
		limit=10;
	else
		limit=1;

	for(;i < limit; i++){
		begin = clock();
		simulation(0,nb_iterations,NB_MIN_THREAD);
		end = clock();
		time_spent[i] = (double)(end - begin) / CLOCKS_PER_SEC;
		printf(" Time spent: %G \n",time_spent[i]);
	}

	if(MMFLAG)
		chercherMoyenne(time_spent);

}

