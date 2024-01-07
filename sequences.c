/*--------------------------------
           Master BIBS
     Universite Paris-Saclay
   Projet MiniInfo 1 2023-2024

Sujet propose par George Marchment
      george.marchment@lisn.fr
----------------------------------*/

#include "utils.h"

/*------------------------------------------------
Fonctions de manipulation de chaînes de caracteres
--------------------------------------------------*/

/*
Input : une chaîne de caracteres et un caractere
Output : None
Main : Ajoute le caractere à la fin de la chaîne de caracteres
*/
void appendString(char* str, char c) {
    int length = strlen(str);
    str[length] = c;
    str[length + 1] = '\0';
}

/*
Input : une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres comme une chaîne vide
*/
void set_empty_string(char* str) {
    str[0] = '\0';
}



/*------------------------------------
Fonctions de manipulation de sequences
--------------------------------------*/

/*
Input : une sequence et une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres en tant qu'ID pour la sequence
*/
void set_id(Sequence* sequence, char* ID) {
    int length = strlen(ID);
    for (int i = 0; i < length; i++) {
        sequence->ID[i] = ID[i];
    }
    sequence->ID[length] = '\0';
}

/*
Input : une sequence et une chaîne de caracteres
Output : None
Main : Initialise la chaîne de caracteres en tant que sequence pour l'objet sequence
*/
void set_seq(Sequence* sequence, char* seq) {
    int length = strlen(seq);
    for (int i = 0; i < length; i++) {
        sequence->seq[i] = seq[i];
    }
    sequence->seq[length] = '\0';
}

/*
Input : une sequence et un entier
Output : Un caractere
Main : Retourne le nucleotide correspondant à l'index
*/
char get_nucleotide(Sequence* sequence, int i) {
    return sequence->seq[i];
}

/*
Input : une sequence et deux chaînes de caracteres
Output : None
Main : Initialise l'ID et la sequence pour l'objet sequence
*/
void set_sequence(Sequence* sequence, char* ID, char* seq) {
    set_id(sequence, ID);
    set_seq(sequence, seq);
}

/*
Input : une sequence
Output : None
Main : Effectue l'affichage de la sequence
*/
void affiche_sequence(Sequence* sequence) {
    printf("* ID : %s \n", sequence->ID); // Affiche l'ID de la séquence
    printf("* Sequence : %s\n", sequence->seq); // Affiche la séquence d'ADN
}


/*-------------------------------
Fonctions de manipulation de fichiers
---------------------------------*/

/*
Input : Adresse d'un fichier
Output : Nombre de sequences dans le fichier
Main : Compte le nombre de sequences presentes dans le fichier
*/
//https://www.geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
int get_number_entries(char* address) {
    int num = 0;
    FILE* ptr;
    char ch;
    ptr = fopen(address, "r");
    if (NULL == ptr) {
        printf("Le fichier ne peut pas être ouvert\n");
    }
    do {
        ch = fgetc(ptr);
        if (ch == '>') {
            num += 1;
        }
    } while (ch != EOF);
    fclose(ptr);
    return num;
}

/*
Input : Adresse d'un fichier
Output : Une chaîne de caracteres
Main : Fonction qui lit un fichier et retourne la chaîne de caracteres
*/
//https://stackoverflow.com/a/15713419
char* readFile(char* fileName) {
    FILE* file = fopen(fileName, "r");
    char* code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL; //Impossible d'ouvrir le fichier
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);  //Allocation de mémoire pour lecture de code

    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}

/*
Input : - une chaîne de caracteres correspondant au code
        - un entier correspondant à la position start, à partir de laquelle on va commencer à chercher
        - Une sequence qu'on va set à partir de l'information trouvee dans le code
Output : - un entier correspondant à la position où on a fini de "lire"
Main : Fonction qui prend le code ainsi qu'une position start, elle va chercher la prochaine sequence 
       definie apres le start et set l'objet sequence avec cette information.
       Elle retourne ensuite la derniere position qui est lu. Pour le cas de la derniere
       sequence elle retourne -1 
*/
//TO DO
int extract_next_sequence(char* code, int start, Sequence* sequence) {
    int i = start;
    int j = 0;

    //Chercher le début de la prochaine séquence, supposé format FASTA
    while (code[i] != '>' && code[i] != '\0') {
        i++;
    }

    //Si fin de la chaîne, retourner -1 car caractère NULL rencontré
    if (code[i] == '\0') {
        return -1;
    }

    //Incrémenter de 1 pour aller à l'indice juste après le '>'
    i++;

    //Extraire l'ID de la séquence, supposé première ligne d'un FASTA
    while (code[i] != '\n' && code[i] != '\0') {  //Vérifie que fin de ligne et fin de fichier n'ont pas été atteintes
        sequence->ID[j] = code[i]; //Le caractère à l'indice i de code est copié dans sequence->ID à l'indice j.Accéder à un champ d'un structure avec un pointeur, c.f cours pointeur si besoin
        j++;     //Incrémente indice dans sequence                   
        i++;     //Incrémente indice dans la lecture du fichier (code)
    }
    sequence->ID[j] = '\0'; //Terminateur de chaîne : marquer la fin de l'écriture de ID dans séquence afin de marquer correctement la fin de la chaîne de caractère stocké dans ID

    //Vérifier si il y a une fin inattendue du fichier, si non, alors continuer à lire code
    if (code[i] == '\0') {
        return -1;
    }

    // Passer le '\n' après l'ID
    i++;
    j = 0; //Réinitialiser indice de sequence au début pour extraire séquance ADN cette fois

    //Extraire la séquence d'ADN
    while (code[i] != '>' && code[i] != '\0') { //Même principe mais pour la seq ADN cette fois
        sequence->seq[j] = code[i]; 
        j++;
        i++;
    }
    sequence->seq[j] = '\0'; //Terminateur de chaîne : marquer la fin de l'écriture de la séquence ADN dans séquence afin de marquer correctement la fin de la chaîne de caractère stocké dans seq

    return code[i] == '\0' ? -1 : i; 
    //Retourner la position de la prochaine séquence, c'est à dire la posotion i (ou bien exprimer par ':') l'indice -1 si fin de la chaîne a été atteinte
    //Cette expression a été construite avec l'opérateur ternaire pour optimiser le return.
}


/*
Input : Adresse d'un fichier et une liste de sequences
Output : None
Main : Fonction qui lit un fichier, remplit la liste avec les sequences trouvees dans le fichier
*/
//TO DO
void parse_file(char* address, Sequence tab_sequences[]) {
    char* fileContent = readFile(address);

    //Vérifier si le fichier a été ouvert avec succès ou si un problème est rencontré
    if (fileContent == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    //Initialiser les indices
    int start = 0;
    int i = 0;

    //Extraire les séquences jusqu'à la fin du fichier
    while (start != -1) { //Tant qu'on est pas à la fin du fichier, c'est à dire à l'indice -1 : indicateur de fin de fichier (EOF)
        start = extract_next_sequence(fileContent, start, &tab_sequences[i]);
        if (start != -1) {
            i++; //Incrémente de 1 pour continuer à extraire jusqu'à la fin du fichier
        }
    }

    free(fileContent);
    //Car c.f fonction readfile() : code=malloc(...) -> allocation mémoire
    //Libérer la mémoire allouée pour le contenu du fichier, pour la réutiliser plus tard si besoin. 
    //https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c
}


/*
Input : Adresse d'un fichier
Output : None
Main : Parse le fichier, sauvegarde les sequences dans une liste. 
       Puis affiche une sequence une par une.
*/
void show_sequences_file(char* file){
    int nb_entries = get_number_entries(file);
    printf("Nombre d'entrees : %d\n", nb_entries);
    printf("\n");
    Sequence tab_sequences[nb_entries];
    parse_file(file, tab_sequences);

    for (int i = 0; i < nb_entries; i++) {
        affiche_sequence(&tab_sequences[i]);
        printf("\n");
    }
}


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


//int main() {
//    char* fichierFasta = "/Users/natha/Desktop/Cours/Mini Info 1/Projet_Mini_Info1/Projet_Phylogénétique/cat_dna.fasta";
//    //printf("%d\n", get_number_entries(fichierFasta));
//    //printf("%s\n", readFile(fichierFasta));
//    //printf("Je vais parser le fichier : %s\n", fichierFasta);
//    show_sequences_file(fichierFasta);
//    return 0;   
//}


