#include "simulation.h"
/**
@authors : Jeremy Melchor
Matthieu Perrin
**/

/* Affiche la grille sur le terminal */
void print_plaque(float (*plaque)[taillePlaque]) {
	for (int i=0; i<taillePlaque; i++) {
		printf("\n");
		for (int j=0; j<taillePlaque; j++) {
			printf("%.1f     ",plaque[i][j]);
		}
	}
	printf("\n");
}

void update_heat(float (*plaque)[taillePlaque], int i_min, int i_max) {
	for (int i=0; i<taillePlaque; i++) {
		for (int j=0; j<taillePlaque; j++) {
			if ( (j>=i_min && j<i_max) && (i>=i_min && i<i_max) )
				plaque[i][j] = TEMP_CHAUD;
		}
	}
}


/* Convertit la puissance passee en parametre en taille */
int convertPowToSize(int puissance_taillePlaque) {
	return pow(2,(puissance_taillePlaque+4));
}


/* Fais les calculs verticalement sur la grille a partir
de l'emplacement i et j passe en parametre ainsi que la valeur 
de la case du milieu. Return la valeur de la case du milieu */
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


/* methode principale de calcul de la grille, pour chaque case ayant une valeur
non nulle de temperature, on calcule ses valeurs verticale avec la fonction
vertical, puis on inscrit la valeur de la case centrale */
void calculate_grid(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque]) {
	for (int i=0; i<taillePlaque; i++) {
		for (int j=0; j<taillePlaque; j++) {
			if (plaque_avant[i][j] != TEMP_FROID) {
				// Si on sort de la grille a gauche
				if ( (j-1) < 0 ) 
					plaque_apres[i][j+1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j+1);
				// Si on sort de la grille a droite
				else if ( (j+1) >= taillePlaque ) 
					plaque_apres[i][j-1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j-1); 
				else {
					plaque_apres[i][j-1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j-1);
					plaque_apres[i][j+1] += vertical(plaque_apres,(plaque_avant[i][j])/6, i, j+1);
				}
				float value = plaque_avant[i][j] - plaque_avant[i][j]/3;
				plaque_apres[i][j] += vertical(plaque_apres, value, i, j);
				
			}
		}
	}
	update_heat(plaque_apres, i_min, i_max);
}



/* fonction gerant la methode iterative */
void iterative_way(float (*plaque_avant)[taillePlaque], float (*plaque_apres)[taillePlaque], int nbIterations) {
	for (int i=0; i<nbIterations; i++) {
		calculate_grid(plaque_avant, plaque_apres);

		// simple switch de pointeur, la plaque t+1 devient celle à t, la t est préparée pour t+1;
		float (*temp)[taillePlaque] = plaque_apres;
		plaque_apres = plaque_avant;
		plaque_avant = temp;
		
		// Permet de reinitialiser la plaque a 0 
		memset(plaque_apres,0,taillePlaque*taillePlaque*sizeof(float));

		if(MFLAG){
			print_plaque(plaque_avant);
		}
	}
}


/* methode principale, c'est elle qui dit quelle methode sera lancee
en fonction des differents parametres recus */
void simulation(int puissance_taillePlaque, int nbIterations, int nbThread) {
	taillePlaque = convertPowToSize(puissance_taillePlaque);

	if (taillePlaque*taillePlaque > TAILLE_MAX || taillePlaque*taillePlaque < TAILLE_MIN) {

		if (MFLAG) {
			printf("%d\n",taillePlaque*taillePlaque);
			printf("Taille de la plaque trop grande\n");
		}
		exit(0);
	}

	float plaque_avant[taillePlaque][taillePlaque];
	float plaque_apres[taillePlaque][taillePlaque];
	memset(plaque_apres,0,taillePlaque*taillePlaque*sizeof(float));

	i_min = pow(2,sqrt(taillePlaque)-1) - pow(2,sqrt(taillePlaque)-4);
	i_max = pow(2,sqrt(taillePlaque)-1) + pow(2,sqrt(taillePlaque)-4);

	init_plaque(plaque_avant, i_min, i_max);

	if (nbThread == 1) 
		iterative_way(plaque_avant, plaque_apres, nbIterations);
	else {
		printf("Pas encore géré !");
		exit(0);
	}
}