#ifndef FONCTIONSH
#define FONCTIONSH

//--- Includes ---//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

//--- Defines ---//
#define PORT 80

//--- Structs ---//
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef int SOCKET;

//--- Variables ---//
char rep[1000];

//-------------------------------------------------------------------------------
// Prototypes fonctions
//-------------------------------------------------------------------------------

//-- Requete --//
void creerRequete(char* buf, char* lien, char* code); // Créer Requette
void afficherRequete(char* requete); // Afficher Requette

//-- Code et clavier --//
void demanderCode(char* code, char* codes_trames); // Demander le code de requete
void clean(const char *buffer, FILE *fp); // Nettoyer le buffer du clavier 

//-- Conversion --//
char* charToString(char c); // Convertir un char en string

//-- Trame --//
char* acquerirTrame(char* code, char* trame, char* rep); // On extrait la trame de la réponse
void afficherReponse(char* trame, char* rep); // On affiche la trame ou la réponse s'il n'y a pas de trame
void enregistrerTrame(char* trame, FILE* fichier); // On enregistre la trame

//-- Fichier --//
FILE* initFichier(); // On initialise le fichier d'enregistrement
void fermerFichier(FILE* fichier); // On ferme le fichier


#endif