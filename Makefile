# Règle pour compiler l'application entière (aucune règle de dépendance)
all: main

# Règle pour effectuer l'édition de liens si les fichiers .o sont plus récents que main
main: main.o sources.o 
	gcc -o main main.o sources.o 

# Règle pour recompiler main.c si main.c ou les fichiers d'en-tête (.h) sont plus récents que main.o
main.o: main.c sources.h 
	gcc -c main.c

# Règle pour recompiler sources.c si sources.c ou les fichiers d'en-tête (.h) sont plus récents que sources.o
sources.o: sources.c sources.h
	gcc -c sources.c

# Règle pour supprimer les fichiers objets et l'exécutable
clean:
	rm main.o sources.o main
