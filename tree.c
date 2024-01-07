#include "utils.h"

/*
--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------
*/

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int min(int a, int b) {
    if (a < b) return a;
    return b;
}

/*
---------------------------
Fonctions de matrice de float
-----------------------------*/

/*
Input : un entier, 2 matrices de float
Output : None
Main : Procedure qui copie l'ancienne matrice dans le nouveau
*/
void set_copy(int entries, float new_tab[][entries], float old_tab[][entries]) {
    for (int i = 0; i < entries; i++) {
        for (int j = 0; j < entries; j++) {
            new_tab[i][j] = old_tab[i][j];
        }
    }
}

/*
Input : - 2 entiers
        - une matrice de float
        - un pointeur sur un float
        - 2 pointeurs sur des entiers
Output : None
Main : Procedure qui trouve la valeur min dans la matrice Inferieur et stocke cette valeur 
       dans le pointeur et ces index dans les 2 autres pointeurs
*/
void find_min_index_distance_matrix(int entries, int nb_noeud, float matrice_distance[][entries], float* min, int* i_min, int* j_min) {
    *min = INFINITY;  //utiliser une valeur initiale suffisamment grande.
    for (int i = 0; i < nb_noeud; i++) {
        for (int j = i + 1; j < nb_noeud; j++) {  //vérifier de ne pas comparer les mêmes noeuds.
            if (matrice_distance[i][j] < *min) {
                *min = matrice_distance[i][j];
                *i_min = i;
                *j_min = j;
            }
        }
    }
}


/*--------------------------------
Fonctions de manipulation de noeud
----------------------------------*/
/*
Input : Un Noeud
Output : Entier
Main : Fonction qui retourne 1 si un noeud est une feuille, 0 sinon
*/
int est_feuille(Noeud* e) {
    if (e->suivant_left == NULL && e->suivant_right == NULL) {
        return 1;
    }
    return 0;
}

/*
Input : None
Output : pointeur sur un noeud
Main : qui cree un noeud vide
*/
Noeud* new_noeud() {
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    n->suivant_left = NULL;
    n->suivant_right = NULL;
    n->valeur = NULL;
    n->nb_noeud = 1;
    return n;
}

/*
Input : pointeur sur un noeud
Output : pointeur sur un noeud
Main : qui cree une copie du noeud, en copiant chaque element un par un
*/
Noeud* create_copy(Noeud* e) {
    Noeud* n = new_noeud();
    n->valeur = e->valeur;
    n->nb_noeud = e->nb_noeud;

    if (e->suivant_left != NULL) {
        Noeud* left = create_copy(e->suivant_left);
        n->suivant_left = left;
    }

    if (e->suivant_right != NULL) {
        Noeud* right = create_copy(e->suivant_right);
        n->suivant_right = right;
    }
    return n;
}

/*-----------------------------------
Fonctions de manipulation d'affichage
-------------------------------------*/


/*
Input : pointeur sur un arbre
Output : None
Main : procedure qui affiche un arbre 
*/


//fonction récursive auxiliaire pour afficher un noeud et ses enfants avec indentation et branches
void afficher_noeud(Noeud* n, int level, char* prefix) {
    if (n == NULL) return;

    //afficher le préfixe pour la branche
    printf("%s", prefix);

    //afficher la valeur du noeud
    if (n->valeur != NULL) {
        printf("%s\n", n->valeur);
    } else {
        printf("[Noeud sans valeur]\n");
    }

    //créer un nouveau préfixe pour les enfants
    char newPrefix[100]; //vérifier que c'est suffisamment grand pour le préfixe
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, level == 0 ? "  |- " : "|   ");

    //appels récursifs pour les enfants, augmentant le niveau pour l'indentation
    if (n->suivant_left != NULL) {
        afficher_noeud(n->suivant_left, level + 1, newPrefix);
    }
    if (n->suivant_right != NULL) {
        afficher_noeud(n->suivant_right, level + 1, newPrefix);
    }
}

//afficher un arbre avec une nouvelle mise en page
void new_affichage(Arbre* a) {
    if (a != NULL && a->tete != NULL) {
        afficher_noeud(a->tete, 0, "");  //On commence avec le niveau 0 pour la racine et aucun préfixe
    }
}



/*
Input : pointeur sur un noeud
Output : None
Main : procedure qui affiche le noeud (d'une maniere plate)
*/
void afficher_elem_plat(Noeud* e) {
    if (e == NULL) return;

    if (est_feuille(e)) printf("%s", e->valeur);
    else {
        printf("(");
        afficher_elem_plat(e->suivant_left);
        printf(", ");
        afficher_elem_plat(e->suivant_right);
        printf(")");
    }
}

/*
Input : pointeur sur un arbre
Output : None
Main : procedure qui affiche un arbre (d'une maniere plate)
*/
void afficher_arbre_plat(Arbre* a) {
    Noeud* e = a->tete;
    printf("\n");
    afficher_elem_plat(e);
    printf("\n");
}

/*-----------------------------------------
Fonctions de manipulation de liste de noeud
-------------------------------------------*/

/*
Input : pointeur d'une Liste de Noeud
Output : entier
Main : Fonction qui retourne le nombre d'elements dans la liste
*/
int get_nb_noeuds(List_Noeuds* list) {
    return list->nb_elements;
}

/*
Input : pointeur d'une Liste de Noeud et un entier
Output : Pointeur sur un element
Main : Fonction qui retourne l'element qui se trouve à l'index i
*/
Element* get_element(List_Noeuds* list, int i) {
    if (i < get_nb_noeuds(list)) {
        Element* temp_ele = list->head;
        for (int k = 0; k < i; k++) {
            temp_ele = temp_ele->next;
        }
        return temp_ele;
    }
}

/*
Input : pointeur d'une Liste de Noeud et un entier
Output : Pointeur sur un noeud
Main : Fonction qui retourne le noeud stocke dans l'element qui se trouve à l'index i
*/
Noeud* get_noeud_from_list(List_Noeuds* list, int i) {
    return get_element(list, i)->data;
}

/*
Input : pointeur d'une Liste de Noeud et un pointeur sur un noeud
Output : None
Main : Procedure qui cree un nouvel element, stocke le noeud dans l'element et qui 
       ajoute l'element à la fin de la liste, en faisant attention de bien modifier la 
       taille de la liste.
*/
void add_Noeud(List_Noeuds* list, Noeud* n) {
    Element* temp = get_element(list, get_nb_noeuds(list) - 1);
    Element* to_add = (Element*)malloc(sizeof(Element));
    to_add->next = NULL;
    to_add->data = n;
    temp->next = to_add;

    list->nb_elements++;
}

/*
Input : pointeur d'une Liste de Noeud et 2 entiers
Output : pointeur sur une liste
Main : Fonction qui regroupe ensemble les deux noeuds qui se trouvent à l'index i et j
       et place cette nouvelle noeud dans un element qui se place au debut d'une
       nouvelle liste. Ainsi les autres elements de la liste originale sont concatenes 
       à la nouvelle dans le même ordre. Ainsi taille(nouvelle) = taille(ancienne)-1.
       Elle retourne le pointeur de cette nouvelle liste.
*/

//permet de grouper deux noeuds basés sur les indices i et j et retourne la nouvelle liste de noeuds.
List_Noeuds* group_together(List_Noeuds* list_param, int i, int j) {
    Noeud* nodeI = get_noeud_from_list(list_param, i);
    Noeud* nodeJ = get_noeud_from_list(list_param, j);

    //création d'un nouveau noeud comme parent de nodeI et nodeJ
    Noeud* newNode = new_noeud();
    newNode->suivant_left = nodeI;
    newNode->suivant_right = nodeJ;
    newNode->nb_noeud = nodeI->nb_noeud + nodeJ->nb_noeud; //MAJ du nombre de noeuds sous le nouveau noeud

    //créer une nouvelle liste de noeuds avec newNode et tous les autres noeuds sauf i et j
    List_Noeuds* newList = (List_Noeuds*)malloc(sizeof(List_Noeuds));

    return newList;
}

/*------------------
Fonctions pour UPGMA
--------------------*/

/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float 
        - 3 entiers
Output : float
Main : Fonction qui calcule la valeur d'une nouvelle cellule dans la matrice à partir de la formule d_ij,k
*/
// Calcule la nouvelle distance selon la formule UPGMA et retourne cette nouvelle distance.
float calcule_new_cell(int entries, List_Noeuds* list, float matrice_distance[][entries], int i, int j, int k) {
    float newDistance = (matrice_distance[i][k] + matrice_distance[j][k]) / 2; // Formule UPGMA pour la nouvelle distance
    return newDistance;
}


/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float 
Output : pointeur d'une Liste de Noeud
Main : Fonction qui effectue une etape de l'algorithme de UPGMA et qui retourne un pointeur 
      sur une nouvelle liste de noeuds
*/

// Fusionne les noeuds les plus proches et met à jour la matrice de distance en conséquence.
List_Noeuds* fuse_matrice_upgma(int entries, List_Noeuds* list, float matrice_distance[][entries]) {
    float minDistance;
    int i_min, j_min;
    find_min_index_distance_matrix(entries, get_nb_noeuds(list), matrice_distance, &minDistance, &i_min, &j_min);

    List_Noeuds* newList = group_together(list, i_min, j_min);

    // TODO: Mettre à jour toutes les distances liées au nouveau noeud et supprimer les distances liées aux anciens noeuds i et j

    return newList;
}


/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeuds
        - matrice de float 
Output : Un arbre
Main : Fonction qui effectue l'algorithme de UPGMA et qui retourne un arbre
*/
Arbre UPGMA(int entries, List_Noeuds* list, float matrice_distance[][entries]) {

    int nb_noeuds = get_nb_noeuds(list);
    while (nb_noeuds > 1) {
        list = fuse_matrice_upgma(entries, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
    }

    Arbre a;
    a.tete = list->head->data;

    return a;
}

/*-----------------------------
Fonctions pour Neighbor Joining
-------------------------------*/

//Lexique :

//entries : la taille de la matrice de distances.
//nb_noeuds : le nombre de noeuds dans la matrice de distances.
//S[] : le tableau des sommes de distances pour chaque noeud.
//matrice : la matrice de distances entre les noeuds.
//min_val : le minimum de Mij trouvé.
//i_min, j_min : indices de la paire de noeuds avec le minimum Mij.


/*
Input : - taille de la matrice (entier)
        - Nombre de noeuds
        - Liste de float 
        - matrice de float 
Output : None
Main : Procedure qui calcule les S de la matrice de distance donnee en parametre en suivant les regles definies dans le lien 
*/
void calcul_S(int entries, int nb_noeuds, float S[], float matrice[][entries]) {
    //parcourir tous les noeuds pour calculer leur somme de distances entre chaque
    for (int i = 0; i < nb_noeuds; i++) {
        float sum = 0.0; //initialiser la somme pour le noeud d'indice i
        //puis calculer la somme des distances de i à tous les autres noeuds
        for (int j = 0; j < nb_noeuds; j++) {
            sum += matrice[i][j]; //accumuler la distance à la variable sum
        }
        S[i] = sum; //stocker la somme dans S[i]
    }
}


/*
Input : - taille de la matrice (entier)
        - Nombre de noeuds
        - Liste de float 
        - matrice de float 
        - pointeur sur un float
        - 2 pointeurs sur des entiers
Output : None
Main : Procedure qui calcule le plus petit Mij et qui stocke les i et j dans les pointeurs
*/
void calcule_pair_Mij(int entries, int nb_noeuds, float S[], float matrice[][entries], float* min_val, int* i_min, int* j_min) {
    *min_val = INFINITY; //initialiser la valeur minimale à l'infini
    //D'abord parcourir toutes les paires de noeuds pour trouver la plus petite valeur M[i][j]
    for (int i = 0; i < nb_noeuds; i++) {
        for (int j = i + 1; j < nb_noeuds; j++) {
            //calculer M[i][j] en ajustant la distance avec la somme des distances
            float Mij = matrice[i][j] - (S[i] + S[j]) / (nb_noeuds - 2);
            //Check up pour vérifier si cette paire a la plus petite valeur Mij jusqu'à présent
            if (Mij < *min_val) {
                *min_val = Mij; //MAJ de la valeur minimale
                *i_min = i;     //stocker l'indice i de la paire
                *j_min = j;     //stocker l'indice j de la paire
            }
        }
    }
}


/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float 
Output : pointeur d'une Liste de Noeud
Main : Fonction qui effectue une etape de l'algorithme de Neighbor Joining et qui retourne un pointeur 
      sur une nouvelle liste de noeuds
*/
List_Noeuds* fuse_matrice_NJ(int entries, List_Noeuds* list, float matrice_distance[][entries]) {
    //calculer le vecteur S pour tous les noeuds
    float S[entries]; //vérifier que la taille de S correspond à nb_noeuds, mais on part de ce principe-là
    calcul_S(entries, get_nb_noeuds(list), S, matrice_distance);

    //trouver la paire de noeuds avec le plus petit Mij
    float min_val;
    int i_min, j_min;
    calcule_pair_Mij(entries, get_nb_noeuds(list), S, matrice_distance, &min_val, &i_min, &j_min);

    return list; //retourner la liste mise à jour après fusion
}


/*
Input : - taille de la matrice (entier)
        - pointeur d'une Liste de Noeud
        - matrice de float 
Output : Un arbre
Main : Fonction qui effectue l'algorithme de Neighbor Joining et qui retourne un arbre
*/
Arbre Neighbor_Joining(int entries, List_Noeuds* list, float matrice_distance[][entries]) {

    int nb_noeuds = get_nb_noeuds(list);
    while (nb_noeuds > 1) {
        list = fuse_matrice_NJ(entries, list, matrice_distance);
        nb_noeuds = get_nb_noeuds(list);
    }

    Arbre a;
    a.tete = list->head->data;
    return a;
}

//---------------------------------------------------------------------------------------

/*
Input : - une chaîne de caracteres correspondant à une adresse
        - l'algorithme de construction voulu, un caractere (U ou N)
Output : None
Main : Une procedure qui prend une adresse d'un fichier, le parse, extrait les sequences
       alignees et ensuite construit et affiche l'arbre phylogenetique correspondant 
       Soit avec l'algo UPGMA ou Neighbor joining.
*/
void show_tree(char* file_aligne, char Algorithme) {
    int nb_entries = get_number_entries(file_aligne);
    Sequence tab_sequences_aligne[nb_entries];
    parse_file(file_aligne, tab_sequences_aligne);

    float matrice_distance[nb_entries][nb_entries];
    initialise_matrice(nb_entries, matrice_distance);
    fill_distance_matrix(nb_entries, matrice_distance, tab_sequences_aligne);

    List_Noeuds list;
    list.head = NULL;
    Noeud* n = new_noeud();
    n->valeur = tab_sequences_aligne[0].ID;

    Element* temp = (Element*)malloc(sizeof(Element));
    temp->next = NULL;
    temp->data = n;
    list.head = temp;
    list.nb_elements = 1;

    for (int i = 1; i < nb_entries; i++) {
        Noeud* n = new_noeud();
        n->valeur = tab_sequences_aligne[i].ID;
        add_Noeud(&list, n);
    }

    Arbre a;
    if (Algorithme == 'U') {
        printf("Arbre UPGMA construit pour le fichier '%s' :\n", file_aligne);
        a = UPGMA(nb_entries, &list, matrice_distance);
    }
    else {
        printf("Arbre NEIGHBOR JOINING construit pour le fichier '%s' :\n", file_aligne);
        a = Neighbor_Joining(nb_entries, &list, matrice_distance);
    }
    afficher_arbre_plat(&a);
}
