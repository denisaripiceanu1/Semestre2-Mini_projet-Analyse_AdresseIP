#include <stdio.h>
#include <string.h>

#include "sources.h"
int main() {
    // Demande à l'utilisateur d'entrer une adresse IP au format CIDR et stocke la saisie dans la variable adresseIP
    char adresseIP[20];
    printf("Entrez une adresse IP au format CIDR : ");

    // Lit une ligne de caractères (l'adresse IP) à partir de l'entrée standard et la stocke dans le tableau adresseIP
    // La taille maximale de la saisie est limitée à la taille du tableau adresseIP
    fgets(adresseIP, sizeof(adresseIP), stdin);

    // Supprime le caractère de saut de ligne de la saisie utilisateur
    adresseIP[strcspn(adresseIP, "\n")] = '\0';

    // Faire une copie de l'adresse IP saisie par l'utilisateur
    char adresseIPCopie[20];
    strncpy(adresseIPCopie, adresseIP, sizeof(adresseIPCopie) - 1);
    adresseIPCopie[sizeof(adresseIPCopie) - 1] = '\0'; // Ajouter le caractère de fin de chaîne

    // Appelle la fonction pour afficher les résultats des informations sur l'adresse IP
    afficher_resultats(adresseIP);

    enregistrer_resultats(adresseIPCopie, "resultats.txt");
    return 0;
}
