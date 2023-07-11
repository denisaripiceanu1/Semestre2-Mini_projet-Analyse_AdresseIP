# Semestre2-Mini_projet-Communication_et_fonctionnement_bas_niveau

Note obtenue : 19/20
Lien du dépôt GIT : https://gitlab.info.iut-tlse3.fr/rpd3994a/sujet2_ripiceanu_delagnes_tamboura.git

Notre équipe, formée par RIPICEANU Denisa, TAMBOURA Kerima et DELAGNES Antoine, a choisi de developer le sujet " Analyse d’adresse IP". Notre programme sait reconnaître, à partir d’une adresse IP en format CIDR donnée en entrée :

le type de l’adresseIP (si elle est publique, privé, localhost, broadcast ou multicast)
la classe de l’adresse (A, B, C, D ou E)
l’adresse du réseau
l’adresse de l’hôte si elle existe.
Dans notre dossier il y a quatre fichiers : « sources.c », « sources.h », « main.c » et le fichier « Makefile ».

Dans le fichier « sources.c » il existe plusieurs fonctions pour manipuler et analyser des adresses IP.

int extraire_masque (const char* adresseIP): extrait le masque de sous-réseau de l'adresse IP fournie en tant que chaîne de caractères.
Cette fonction prend en entrée une chaîne de caractères représentant l'adresse IP au format CIDR.
Elle sort un entier représentant la valeur du masque de sous-réseau extrait de l'adresse IP.

int obtenir_classe (int* champs): détermine la classe de l'adresse IP en fonction des plages d'octets spécifiées pour chaque classe.
Cette fonction prend en entrée un tableau d'entiers représentant les octets de l'adresse IP.
Elle a en sortie un entier représentant la classe d'adresse IP (CLASSE_A, CLASSE_B, CLASSE_C, CLASSE_D ou CLASSE_E, représentés par des constantes).

int obtenir_type (int* champs) : donne le type d'adresse IP en vérifiant les plages spécifiques pour les adresses publiques, privées, localhost, broadcast et multicast.
Cette fonction prend en entrée un tableau d'entiers représentant les octets de l'adresse IP.
Elle donne en sortie un entier représentant le type d'adresse IP (PUBLIC, PRIVE, LOCALHOST, BROADCAST ou MULTICAST, représentés par de constantes).

int verifier_format (const char *adresseIP): vérifie si le format de l'adresse IP est correct, en s'assurant qu'il y a trois points et un slash dans la chaîne de caractères.
Cette fonction prend en entrée une chaîne de caractères représentant l'adresse IP à vérifier.
Elle sort in entier (0 ou 1) indiquant si le format de l'adresse IP est valide ou non.

void extraire_octets (const char* adresseIP, int* champs, int* masque) : extrait les octets de l'adresse IP et le masque de sous-réseau de la chaîne de caractères spécifiée.
Elle prend en entrée une chaîne de caractères représentant l'adresse IP au format CIDR, un tableau d'entiers pour stocker les octets de l'adresse IP et un pointeur d'entier pour stocker le masque de sous-réseau.
Elle n’a pas de sortie. Les octets de l'adresse IP et le masque sont stockés dans les tableaux et la variable pointée respectivement.

int verifier_valeurs_octets (int* champs): vérifie si les valeurs des octets de l'adresse IP sont comprises entre 0 et 255, ce qui correspond à la plage valide pour chaque octet d'une adresse IP.
Elle prend en entrée un tableau d'entiers représentant les octets de l'adresse IP.
Elle sort un entier (0 ou 1) indiquant si les valeurs des octets sont valides ou non.

int verifier_valeur_masque (int masque): vérifie si le masque de sous-réseau est valide, c'est-à-dire s'il est compris entre 0 et 32.
Elle prend en entrée un entier représentant le masque de sous-réseau.
Elle sort un entier (0 ou 1) indiquant si le masque est valide ou non.

void trouver_adresse_reseau (int* champs, int nb_masque, int* adresse_reseau) : trouver l'adresse réseau correspondante à une adresse IP donnée et à un masque de réseau spécifié. L'adresse réseau est calculée en effectuant un "ET logique" bit à bit entre l'adresse IP et le masque de réseau. Le résultat est ensuite stocké dans le tableau de caractères « adresseReseau ».
Elle prend en entrée une chaîne de caractères représentant l'adresse IP, une chaîne de caractères représentant le masque de réseau, un tableau de caractères pour stocker l'adresse réseau.
Elle n’a aucune sortie.

void trouver_adresse_hote (const char* adresseIP, const char* masqueReseau, char* adresseHote): trouve l'adresse hôte correspondante à une adresse IP donnée et à un masque de réseau spécifié. L'adresse hôte est calculée en effectuant un "ET logique inversé" bit à bit entre l'adresse IP et le masque de réseau (en inversant les bits du masque de réseau). Le résultat est ensuite stocké dans le tableau de caractères "adresseHote".
Cette fonction prend en entrée une chaîne de caractères représentant l'adresse IP, une chaîne de caractères représentant le masque de réseau, un tableau de caractères pour stocker l'adresse hôte.
Elle n’a aucune sortie.

void enregistrer_resultats (char* adresseIP, char* nomFichier): enregistre les résultats de la fonction afficher_resultats dans un fichier spécifié.
Cette fonction prend en entrée un pointeur vers une chaîne de caractères représentant l'adresse IP et un pointeur vers une chaîne de caractères représentant le nom du fichier dans lequel enregistrer les résultats.
Elle n’a aucune sortie.

On sait que les consignes du projet ont été de ne pas faire des affichages au sein des fonctions, mais pour optimiser notre programme, on a déicidé de mettre en place ces cinq fonctions pour afficher les informations sur l’adresse IP :

void afficher_type_adresse (int type) : affiche le type d'adresse (public, privé, localhost, diffusion, multicast).
void afficher_classe_adresse (int classe) : affiche la classe d'adresse (A, B, C, D, E).
void afficher_adresse_hote (const int adresse_hote[]): vérifie si tous les octets de l'adresse de l'hôte sont à zéro ou non, et en fonction de cela, elle affiche l'adresse de l'hôte ou un message indiquant l'absence d'adresse d'hôte
void afficher_adresse_reseau (const int adresse_reseau[]) : affiche l'adresse du réseau.
void afficher_resultats (const char* adresseIP) : Affiche les résultats (type, classe, adresse du réseau, adresse de l'hôte) à partir de l'adresse IP
Le fichier « sources.h » contient les signatures de ces fonctions.

Le fichier « main.c » contient la fonction main, qui est le point d'entrée du programme, où l'utilisateur est invité à entrer une adresse IP et où les fonctions de « sources.c » sont utilisées pour afficher des informations sur cette adresse IP.

Notre dossier contient en plus un fichier « Makefile » assurant l'automatisation des étapes de compilation.
