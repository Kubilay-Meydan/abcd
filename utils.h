/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//Sequence
#define ID_MAX_LENGTH 50
#define seq_MAX_LENGTH 400

typedef struct Sequence {
    char ID[ID_MAX_LENGTH];
    char seq[seq_MAX_LENGTH];
} Sequence;

void show_sequences_file(char* file);


//Alignement
#define NB_BASE 5

typedef enum Base_Azotee {
    A = 0, C = 1, G = 2, T = 3, E = 4
} Base_Azotee;


int score_alignement(char* alignement1, char* alignement2);
void print_quality_alignement(char* ali1, char* ali2, int score);
void set_empty_string(char* str);
void set_sequence(Sequence* sequence, char* ID, char* seq);
void needleman_wunsch(Sequence seq1, Sequence seq2, char* alignement1, char* alignement2);

//MATRICE DE DISTANCE
void show_distance_matrix(char* file_aligne);
int get_number_entries(char* file_aligne);
void parse_file(char* file_aligne, Sequence tab_sequences_aligne[]);
float distance(Sequence seq1, Sequence seq2); 
float jukes_cantor(float x);

//TREE
typedef struct Noeud {
    char* valeur;
    struct Noeud* suivant_left;
    struct Noeud* suivant_right;
    int nb_noeud;
}Noeud;

typedef struct Element {
    struct Element* next;
    Noeud* data;
}Element;

typedef struct List_Noeuds {
    Element* head;
    int nb_elements;
}List_Noeuds;


typedef struct Arbre {
    Noeud* tete;
}Arbre;

void show_tree(char* file_aligne, char Algorithme);
void afficher_noeud(Noeud* n, int level, char* prefix);
void initialise_matrice(int entries, float matrice_distance[][entries]);
void fill_distance_matrix(int entries, float matrice_distance[][entries], Sequence sequences[]);