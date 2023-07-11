/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 2                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse adresse IP                                              *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : RIPICEANU Denisa                                             *
*                                                                             *
*  Nom-prénom2 : DELAGNES Antoine                                             *
*                                                                             *
*  Nom-prénom3 : TAMBOURA Kerima                                              *
*                                                                             *
*  Nom-prénom4 : -                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : sources.h                                                 *
*                                                                             *
******************************************************************************/

// Extraire le masque à partir de l'adresse IP
int extraire_masque(const char* adresseIP);  
// Déterminer la classe de l'adresse IP en fonction des octets
int obtenir_classe(int* champs);  
// Déterminer le type d'adresse en fonction des octets
int obtenir_type(int* champs);  
// Vérifier le format valide de l'adresse IP
int verifier_format(const char *adresseIP);  
// Extraire les octets et le masque à partir de l'adresse IP
void extraire_octets(const char* adresseIP, int* champs, int* masque);  
// Vérifier si les valeurs des octets sont valides
int verifier_valeurs_octets(int* champs);  
// Vérifier si la valeur du masque est valide
int verifier_valeur_masque(int masque);  
// Trouver l'adresse du réseau à partir des octets et du masque
void trouver_adresse_reseau(int* champs, int nb_masque, int* adresse_reseau);  
// Trouver l'adresse de l'hôte à partir des octets et du masque
void trouver_adresse_hote(int* adresse_reseau, int* adresse_hote, int masque_reseau);
// Afficher le type d'adresse
void afficher_type_adresse(int type); 
// Afficher la classe d'adresse
void afficher_classe_adresse(int classe);  
// Afficher l'adresse du réseau
void afficher_adresse_reseau(const int adresse_reseau[]);  
// Afficher l'adresse de l'hôte
void afficher_adresse_hote(const int adresse_hote[]);  
// Afficher les résultats (type, classe, adresse du réseau, adresse de l'hôte) à partir de l'adresse IP
void afficher_resultats(const char* adresseIP);  
// Enregistre les résultats de la fonction afficher_resultats dans un fichier spécifié.
void enregistrer_resultats( char* adresseIP,  char* nomFichier);
