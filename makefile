####################################
#            Master BIBS
#      Universite Paris-Saclay
#    Projet MiniInfo 1 2023-2024
# 
# Sujet propose par George Marchment
#       george.marchment@lisn.fr
####################################

CC=gcc

#On ignore les warnings -> ceci n'est pas conseille!
#Mais je fais ça pour simplifier la vie
CFLAGS=-w

all: phylo

phylo: sequences.o alignement.o matrice_distance.o tree.o main.o
	$(CC)  sequences.o alignement.o matrice_distance.o tree.o main.o -lm -o phylo

tree.o: tree.c utils.h 
	$(CC) -c tree.c $(CFLAGS)

matrice_distance.o: matrice_distance.c utils.h 
	$(CC) -c matrice_distance.c $(CFLAGS)

alignement.o: alignement.c utils.h 
	$(CC) -c alignement.c $(CFLAGS)

sequences.o: sequences.c utils.h 
	$(CC) -c sequences.c $(CFLAGS)

main.o: main.c utils.h 
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f phylo