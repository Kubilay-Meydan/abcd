/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
Input : Deux Sequences
Output : Float
Main : Fonction qui retourne la distance entre deux sequences 
*/

float distance(Sequence seq1, Sequence seq2) {
    int len = strlen(seq1.seq) - 2;
    //printf("La longeur est de %d%",len);
    int diff = 0;
    
    for (int i = 0; i < len; i++) {
        if (seq1.seq[i] != seq2.seq[i]) {
            diff++;
        }
    }
    
    if (len == 0) return 0.0;  // Éviter la division par zéro
    return (float)diff / len;  // Normalisation de la distance
}



/*
Input : Float
Output : Float
Main : Fonction qui applique la correction de Jukes-Cantor
*/
//https://www.programiz.com/c-programming/library-function/math.h/log
float jukes_cantor(float x) {
    if (x >= 0.75) {  // Éviter une erreur mathématique
        return INFINITY;  // Ou gérer comme vous le jugez approprié
    }
    return -(3.0 / 4.0) * log(1 - (4.0 / 3.0) * x);
}


/*-------------------------------------------------
Fonctions de manipulation de la matrice de distance
---------------------------------------------------*/

/*
Input : un entier et Une matrice de float
Output : None
Main : Procedure qui initialise une matrice à une matrice nulle
*/
void initialise_matrice(int entries, float matrice_distance[][entries]) {
    for (int i = 0; i < entries; i++) {
        for (int j = 0; j < entries; j++) {
            matrice_distance[i][j] = 0.0;  //On initialise a une distance de 0 entre chaque element. 
        }
    }
}

/*
Input : Deux entiers et Une matrice de float
Output : None
Main : Procedure qui print une matrice
*/
/*void print_matrix_float(int n, int m, float matrix[][m]) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > j)
                {
                    printf("%f\t", matrix[i][j]);
                }
                else printf(".\t");
        }
        printf("\n"); //On saute de ligne apres chaque ligne
    }
}*/

void print_matrix_float(int n, int m, float matrix[][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > j ) {
                printf("%.5f\t", matrix[i][j]); // Modifié pour six chiffres après la virgule
            } else if (i == j) {
                printf(".\t"); // Point pour la diagonale
            } else {
                printf(".\t"); // Espace pour la partie non calculée
            }
        }
        printf("\n");
    }
}




/*
Input : entier, matrice de float et une liste de sequence
Output : None
Main : Procedure qui remplit la matrice avec la distance entre les sequences
*/
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[]) {
    for (int i = 0; i < entries; i++) {
        for (int j = i + 1; j < entries; j++) { // Commencez à j = i + 1 pour éviter de calculer la diagonale
            float distance_non_corrigee = distance(sequences[i], sequences[j]); 
            matrice_distance[i][j] = distance_non_corrigee;
            matrice_distance[j][i] = matrice_distance[i][j]; // Assurez-vous que la matrice est symétrique
        }
    }
}


/*
Input : Un fichier
Output : None
Main : Fonction qui prend une adresse en entree et qui calcule et affiche la matrice de distance correspondant aux sequences
*/
void show_distance_matrix(char* file_aligne){
    int nb_entries = get_number_entries(file_aligne);
    //printf("Le nombre d'entré est %d%", nb_entries);
    Sequence tab_sequences_aligne[nb_entries];
    parse_file(file_aligne, tab_sequences_aligne);
    //for(int i = 0; i < nb_entries; i++) {
    //printf("ID: %s\n", tab_sequences_aligne[i].ID);
    //printf("Sequence: %s\n\n", tab_sequences_aligne[i].seq);}


    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);
    printf("La matrice de distance calculee pour le fichier '%s' :\n", file_aligne);
    printf("\n"); //histoire d'y voir un peu plus clair dans le terminal
    print_matrix_float(nb_entries, nb_entries, matrice_distance);
    printf("\n");
}

