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
void creerRequete(char* buf, char* lien, char* code); // Créer Requette
void afficherRequete(char* requete); // Afficher Requette
void clean(const char *buffer, FILE *fp); // Nettoyer le buffer du clavier 
void demanderCode(char* code, char* codes_trames); // Demander le code de requete
char* charToString(char c); // Convertir un char en string
void afficherReponse(char* code, char* trame, char* rep);
