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

const int similarity_matrix[NB_BASE][NB_BASE] = {{10, -1, -3, -4, -5},
                                                 {-1,  7, -5, -3, -5},
                                                 {-3, -5,  9,  0, -5},
                                                 {-4, -3,  0,  8, -5},
                                                 {-5, -5, -5, -5,  0}};


/*----------------------------------------------------------------------------------
Fonctions permettant de calculer le score d'alignement entre 2 chaînes de caracteres
------------------------------------------------------------------------------------*/

/*
Input : Un caractere
Output : Un entier
Main : Fonction qui prend un caractere et retourne l'index correspondant (voir l'enum Base_Azotee)
*/
int get_val_base(char a) {
        switch (a) {
        case 'A':
        case 'a':
            return A;
        case 'C':
        case 'c':
            return C;
        case 'G':
        case 'g':
            return G;
        case 'T':
        case 't':
            return T;
        default: // corresepond aux gaps
            return E;
    }
}

/*
Input : Deux caracteres 
Output : Un entier
Main : Fonction qui prend en entier 2 caracteres et qui retourne 
       le score entre les 2 caracteres suivant la matrice de similarite
*/
int similarity_score(char ch1, char ch2) {
    return similarity_matrix[get_val_base(ch1)][get_val_base(ch2)];
}

/*
Input : Deux chaînes de caracteres s
Output : Un entier
Main : Fonction qui prend en entier 2 chaînes de caracteres et qui retourne 
       le score d'alignement entre les deux chaînes
*/
int score_alignement(char* alignement1, char* alignement2) {
    //                                                  IMPORTANT, ON CONSIDERE LES SEQUENCES DE MEME LONGUEUR
    int score = 0;
    
    int len1 =  strlen(alignement1); //calcule la longueur de la premiere sequence
    int len2 =  strlen(alignement2); //calcule la longueur de la deuxieme sequence
    
    for (int i = 0; i < len1; i++) {
        score += similarity_score(alignement1[i], alignement2[i]);
    }

    return score;
}

/*
Input : Deux chaînes de caracteres et un score
Output : None
Main : Procedure qui prend en entier 2 chaînes de caracteres et un score
       Et qui fait un bel affichage montrant l'alignement et le score
*/
void print_quality_alignement(char* ali1, char* ali2, int score) {
    //Va print un les deux sequences, puis leurs score. Entre les deux sequences, nous mettons des "|" entre les 
    //characteres pour les matchs et des espaces pour les mismatchs 
    printf("\n");
    printf("le score d'alignement: %d\n", score);
    printf("%s\n", ali1);
    
    for (int i = 0; ali1[i] != '\0' && ali2[i] != '\0'; i++) {
        // Test si les deux sequences on le me meme charactere (match), la fonction met un "|", sinon, un espace.
        printf("%c", ali1[i] == ali2[i] ? '|' : ' ');
    }
    printf("\n"); // pour que ce soit joli dans le terminal
    printf("%s\n", ali2);
    printf("\n");
}

/*----------------------------
Algorithme de Needleman-Wunsch
------------------------------*/

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice M
*/
void initialise_M(int n, int m, int M[][m]) {
        // Initialise la premiere ligne
    for (int i = 0; i <= m; i++) {
        M[0][i] = -5 * i;
    }

    // initialise la permiere colone 
    for (int j = 0; j <= n; j++) {
        M[j][0] = -5 * j;
    }
}

/*
Input : 2 entiers et une matrice
Output : None
Main : Procedure qui Initialise la matrice T
*/
void initialise_T(int n, int m, char T[][m]) {
    T[0][0] = 'o';
        // Initialise la premiere ligne
    for (int i = 0; i <= m; i++) {
        T[0][i] = 'l';
    }

    // premiere colonne.
    for (int j = 0; j <= n; j++) {
        T[j][0] = 'u';
    }
}

/*
Input : un entier
Output : un caractere
Main : Fonction qui retourne le caractere correspondant au maximum index de la formule Mij
*/
char symbole(int entier) {
    if (entier == 0) {
        return 'd';
    }
    else if (entier == 1) {
        return 'l';
    }
    return 'u';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Procedure qui inverse une chaîne de caracteres
*/
void reverse_string(char* str)
{
    // récupère la longueur de la string
    int n = strlen(str);
 
    // commence à échanger les caractères des deux extrémités de la string
    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}

//void reverse_string(char* str) {
    //printf("%s\n", strrev(str)); 
    // apres test, seulement certains compilateurs accepte strrev.
    //https://www.javatpoint.com/reverse-a-string-in-c
//}

/*
Input : - 2 Sequences
        - 2 index
        - 2 tailles
        - une matrice de taille n*m
        - Deux pointeurs sur des entiers
Output : None
Main : Procedure qui applique la formule Mij et qui sauvegarde 
       la plus grande valeur dans le premier pointeur et l'index
       correspondant (0, 1 ou 2) dans le deuxieme.
*/
// Fonction Mij améliorée
void fonction_Mij(Sequence* s1, Sequence* s2, int i, int j, int n, int m, int M[][m], int* max, int* index) {
    int scoreDiagonal = M[i-1][j-1] + similarity_score(s1->seq[i-1], s2->seq[j-1]);
    int scoreUp = M[i-1][j] - 5; // Pénalité de gap pour un score 'up'
    int scoreLeft = M[i][j-1] - 5; // Pénalité de gap pour un score 'left'

    // Détermine le score maximal et l'index correspondant
    int maxScore = scoreDiagonal; // assume diagonal is max initially
    int maxIndex = 0; // 'd' diagonale

    if (scoreLeft > maxScore) {
        maxScore = scoreLeft;
        maxIndex = 1; // 'l' left
    }
    if (scoreUp > maxScore) {
        maxScore = scoreUp;
        maxIndex = 2; // 'u' up
    }

    M[i][j] = maxScore;   // Mise à jour de la matrice avec le score maximal

    // Mise à jour du score maximal et de l'index
    *max = maxScore;
    *index = maxIndex;
}

/*
Input : - 2 Sequences
        - Deux chaînes de caracteres
Output : None
Main : Procedure qui applique l'algorithme Needleman-Wunsch
       sur les 2 sequences et qui sauvegarde les alignements
       dans les 2 pointeurs
*/

void needleman_wunsch(Sequence seq1, Sequence seq2, char* alignment1, char* alignment2) {
    int len1 = strlen(seq1.seq);
    int len2 = strlen(seq2.seq);
    int M[len1+1][len2+1];
    char T[len1+1][len2+1]; //T n'a pas de valeurs numériques, contrairement à M, qui n'a que des valeurs numériques (int)

    // Initialisation des matrices.
    initialise_M(len1, len2, M);
    initialise_T(len1, len2, T);

    // Remplissage de M en utilisant la fonction_Mij definie precedement.
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int max;
            int index; //Stocke la direction par laquelle on a eu le max par la fonction Mij
            fonction_Mij(&seq1, &seq2, i, j, len1, len2, M, &max, &index);

            // On met a jour la matrice T avec la valeur de index (la direction)
            T[i][j] = symbole(index);
        }
    }
    // Traceback de la matrice T
    int x = len1;
    int y = len2;
    int align1_pos = 0;
    int align2_pos = 0;

    while (x > 0 || y > 0) {
        if (T[x][y] == 'd') {
            alignment1[align1_pos++] = seq1.seq[--x];
            alignment2[align2_pos++] = seq2.seq[--y];
        } else if (T[x][y] == 'u') {
            alignment1[align1_pos++] = seq1.seq[--x];
            alignment2[align2_pos++] = '-';
        } else if (T[x][y] == 'l') {
            alignment1[align1_pos++] = '-';
            alignment2[align2_pos++] = seq2.seq[--y];
        }
    }

    // On inverse les alignements, ils ont ete construits a l'envers dans la matrice
    alignment1[align1_pos] = '\0';
    alignment2[align2_pos] = '\0';
    reverse_string(alignment1);
    reverse_string(alignment2);
}
