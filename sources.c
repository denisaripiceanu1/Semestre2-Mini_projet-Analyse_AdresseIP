#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sources.h"

#define CLASSE_A 1
#define CLASSE_B 2
#define CLASSE_C 3
#define CLASSE_D 4
#define CLASSE_E 5

#define PUBLIC 1
#define PRIVE 2
#define LOCALHOST 3
#define BROADCAST 4
#define MULTICAST 5

// Fonction pour extraire le masque de sous-réseau de l'adresse IP
int extraire_masque(const char* adresseIP) {

    // Séparer l'adresse IP et le masque en utilisant le délimiteur '/'
    char* masque = strtok((char*)adresseIP, "/");

    // Récuperer la partie du masque après la première occurrence du délimiteur '/'
    masque = strtok(NULL, "/");

    // Convertit la chaîne de caractères du masque en entier
    return atoi(masque);
}

// Fonction pour obtenir la classe d'adresse IP
int obtenir_classe(int* champs) {
    // Vérifier les plages des octets
    if (champs[0] >= 1 && champs[0] <= 126) {
        return CLASSE_A;
    } else if (champs[0] >= 128 && champs[0] <= 191) {
        return CLASSE_B;
    } else if (champs[0] >= 192 && champs[0] <= 223) {
        return CLASSE_C;
    } else if (champs[0] >= 224 && champs[0] <= 239) {
        return CLASSE_D;
    } else {
        return CLASSE_E;
    }
}

// Fonction pour obtenir le type d'adresse IP
int obtenir_type(int* champs) {
    if (champs[0] == 255 && champs[1] == 255 && champs[2] == 255 && champs[3] == 255) {
        return BROADCAST;
    }
    // Vérifier si l'adresse est une adresse de multidiffusion (multicast)
    if (champs[0] >= 224 && champs[0] <= 239) {
        return MULTICAST;
    }
    // Vérifier si l'adresse est une adresse localhost
    if (champs[0] == 127) {
        return LOCALHOST;
    }
    // Vérifier si l'adresse est une adresse privée
    if (obtenir_classe(champs) == CLASSE_A && champs[0] == 10) {
        return PRIVE; // Adresse privée de classe A
    }
    if (obtenir_classe(champs) == CLASSE_B && champs[0] == 172 && champs[1] >= 16 && champs[1] <= 31) {
        return PRIVE; // Adresse privée de classe B
    }
    if (obtenir_classe(champs) == CLASSE_C && champs[0] == 192 && champs[1] == 168) {
        return PRIVE; // Adresse privée de classe C
    }
    return PUBLIC; // Adresse publique par défaut
}

// Fonction pour vérifier le format de l'adresse IP
int verifier_format(const char *adresseIP) {
    int nb_points = 0; // Compteur pour le nombre de points dans l'adresse IP
    int taille = strlen(adresseIP); // Taille de la chaîne de caractères
    for (int i = 0; i < taille; i++) {
        if (adresseIP[i] == '.') {
            nb_points++; // Incrémenter le compteur si un point est trouvé
        }
    }
    if (nb_points != 3) {// Si le nombre de points est incorrect
        return 0; // Format invalide
    }
    int nb_slash = 0; // Compteur pour le nombre de slash dans l'adresse IP
    for (int i = 0; i < taille; i++) {
        if (adresseIP[i] == '/') { 
            nb_slash++; // Incrémenter le compteur si un slash est trouvé
        }
    }
    if (nb_slash != 1) {
        return 0; // Format invalide, le nombre de slash est différent de 1
    }
    return 1; // Format valide
}

// Fonction pour extraire les octets de l'adresse IP et le masque de sous-réseau
void extraire_octets(const char* adresseIP, int* champs, int* masque) {
    int octet1, octet2, octet3, octet4, masc;
    sscanf(adresseIP, "%d.%d.%d.%d/%d", &octet1, &octet2, &octet3, &octet4, &masc); // Extraire les valeurs
    champs[0] = octet1; // Stockage de l'octet 1 dans le tableau champs
    champs[1] = octet2;
    champs[2] = octet3;
    champs[3] = octet4;
    *masque = masc; // Stockage du masque dans la variable masque pointée par le pointeur
}
// Fonction pour vérifier les valeurs des octets de l'adresse IP
int verifier_valeurs_octets(int* champs) {
    for (int i = 0; i < 4; i++) {
        if (champs[i] < 0 || champs[i] > 255) {
            return 0;  // Valeur d'octet invalide
        }
    }
    return 1;  // Toutes les valeurs sont valides
}

// Fonction pour vérifier la valeur du masque de sous-réseau
int verifier_valeur_masque(int masque) {
    if (masque < 0 || masque > 32) {
        return 0;  // Masque de sous-réseau invalide
    }
    return 1;  // Valeur du masque valide
}

// Fonction pour trouver l'adresse réseau à partir des octets de l'adresse IP et du masque de sous-réseau
void trouver_adresse_reseau(int* champs, int nb_masque, int* adresse_reseau) {
    int masque = (int)pow(2, nb_masque) - 1; // Calcul du masque de sous-réseau
    int nb_octet = nb_masque / 8; // Nombre d'octets complets dans le masque
    int octets_manquants = nb_masque % 8; // Nombre d'octets manquants dans le masque
    int masque_resultat[4] = {0, 0, 0, 0}; // Tableau pour stocker le résultat du masquage

    // Calcule le dernier octet du masque de sous-réseau en utilisant le masque généré précédemment et en ajustant les décalages de bits si nécessaire
    masque_resultat[nb_octet] = masque << (8 - octets_manquants);  
    for (int i = 0; i < nb_octet; i++) {
        masque_resultat[i] = 255;  // Les octets complets du masque sont tous définis à 255
    }
    for (int i = 0; i < 4; i++) {
        adresse_reseau[i] = champs[i] & masque_resultat[i]; // Application du masque pour obtenir l'adresse réseau
    }
}

// Fonction pour trouver l'adresse de l'hôte à partir des octets de l'adresse IP et du masque de sous-réseau
void trouver_adresse_hote(int* adresse_reseau, int* adresse_hote, int masque_reseau) {
    // Initialiser tous les octets de l'adresse hôte à 0
    for (int i = 0; i < 4; i++) {
        adresse_hote[i] = 0;
    }
    // Calculer le nombre d'octets complets du masque
    int nb_octets_reseau = masque_reseau / 8;
    // Calculer le nombre d'octets partiels du masque
    int octets_manquants = masque_reseau % 8;
    // Initialiser le masque avec les bits les plus significatifs à 1
    int masque = 255;
    int increment = 0;
    // Calculer le masque complet en ajoutant des bits à 1
    for (int i = 0; i < 8 - octets_manquants; i++) {
        increment = (int)pow(2, i);
        masque += increment;
    }
    // Appliquer le masque aux octets de l'adresse IP source pour obtenir l'adresse d'hôte
    for (int i = 0; i < 4; i++) {
        if (i < nb_octets_reseau) {
            // Les octets avant le dernier octet complet sont mis à 0
            adresse_hote[i] = 0;
        } else if (i == nb_octets_reseau) {
            // L'octet correspondant au dernier octet complet est obtenu en appliquant le masque avec l'opérateur AND
            adresse_hote[i] = adresse_reseau[i] & masque;
        } else {
            // Les octets après le dernier octet complet sont copiés tels quels
            adresse_hote[i] = adresse_reseau[i];
        }
    }
}

void enregistrer_resultats(char* adresseIP, char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur à l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    
    // Rediriger la sortie vers le fichier
    FILE* sortie = stdout;
    stdout = fichier;

    // Appeler la fonction afficher_resultats
    afficher_resultats(adresseIP);
    printf("Enregistrement des résultats dans le fichier %s réussi\n", nomFichier);

    // Restaurer la sortie standard
    stdout = sortie;

    // Fermeture du fichier
    fclose(fichier);
}

// TOUS CES FONTIONS SERONT UTILISÉES POUR L'AFFICHAGES DES INFORMATIONS

// Fonction pour afficher le type d'adresse IP
void afficher_type_adresse(int type) {
    printf("Type d'adresse : ");
    switch (type) {
        case PUBLIC:
            printf("Publique\n");
            break;
        case PRIVE:
            printf("Privée\n");
            break;
        case LOCALHOST:
            printf("Localhost\n");
            break;
        case BROADCAST:
            printf("Broadcast\n");
            break;
        case MULTICAST:
            printf("Multicast\n");
            break;
        default:
            printf("Inconnu\n");
            break;
    }
}

// Fonction pour afficher la classe d'adresse IP
void afficher_classe_adresse(int classe) {
    printf("Classe d'adresse : ");
    switch (classe) {
        case CLASSE_A:
            printf("A\n");  // Afficher la classe A si la valeur de 'classe' correspond à la classe A
            break;
        case CLASSE_B:
            printf("B\n");  // Afficher la classe B si la valeur de 'classe' correspond à la classe B
            break;
        case CLASSE_C:
            printf("C\n");  // Afficher la classe C si la valeur de 'classe' correspond à la classe C
            break;
        case CLASSE_D:
            printf("D\n");  // Afficher la classe D si la valeur de 'classe' correspond à la classe D
            break;
        case CLASSE_E:
            printf("E\n");  // Afficher la classe E si la valeur de 'classe' correspond à la classe E
            break;
        default:
            printf("Inconnue\n");  // Afficher "Inconnue" si la valeur de 'classe' ne correspond à aucune classe connue (A, B, C, D ou E)
            break;
    }
}

// Afficher l'adresse du réseau
void afficher_adresse_reseau(const int adresse_reseau[]) {
    printf("Adresse du réseau : %d.%d.%d.%d\n", adresse_reseau[0], adresse_reseau[1], adresse_reseau[2], adresse_reseau[3]);
}

// Afficher l'adresse de l'hôte
void afficher_adresse_hote(const int adresse_hote[]) {
    int compteur = 0;
    // Parcourir les 4 octets de l'adresse hôte
    for (int i = 0; i < 4; i++) {
        if (adresse_hote[i] == 0) { // Si l'octet est égal à 0
            compteur += 1; // On incrémente le comptoir
        }
    }
    // Vérifier si tous les octets sont à zéro
    if (compteur == 4) {
        printf("Il n'y a pas d'adresse hôte.\n");
    } else {
        printf("Adresse de l'hôte : %d.%d.%d.%d\n", adresse_hote[0], adresse_hote[1], adresse_hote[2], adresse_hote[3]);
    }
}

// Afficher les résultats (type, classe, adresse du réseau, adresse de l'hôte) à partir de l'adresse IP
void afficher_resultats(const char* adresseIP) {
    // Vérifier le format de l'adresse IP
    if (!verifier_format(adresseIP)) {
        printf("Format d'adresse invalide.\n");
        return;
    }

    // Extraire les octets et le masque de l'adresse IP
    int champs[4];
    int masque;
    extraire_octets(adresseIP, champs, &masque);

    // Vérifier les valeurs des octets et du masque
    if (!verifier_valeurs_octets(champs) && !verifier_valeur_masque(masque)) {
        printf("Valeurs d'octets et de masque invalides.\n");
        return;
    }

    // Vérifier les valeurs des octets
    if (!verifier_valeurs_octets(champs)) {
        printf("Valeurs d'octets invalides.\n");
        return;
    }

    // Vérifier la valeur du masque
    if (!verifier_valeur_masque(masque)) {
        printf("Valeur du masque invalide.\n");
        return;
    }

    // Obtenir le type et la classe de l'adresse IP
    int type = obtenir_type(champs);
    int classe = obtenir_classe(champs);

    // Afficher le type d'adresse
    afficher_type_adresse(type);

    // Afficher la classe d'adresse
    afficher_classe_adresse(classe);

    // Trouver l'adresse du réseau à partir des octets et du masque
    int adresse_reseau[4];
    trouver_adresse_reseau(champs, masque, adresse_reseau);

    // Afficher l'adresse du réseau
    afficher_adresse_reseau(adresse_reseau);

    // Trouver l'adresse de l'hôte à partir des octets et du nombre de bits du masque
    int adresse_hote[4];
    int nb_masque = extraire_masque(adresseIP);
    trouver_adresse_hote(champs, adresse_hote, nb_masque);

    // Afficher l'adresse de l'hôte
    afficher_adresse_hote(adresse_hote);
}
