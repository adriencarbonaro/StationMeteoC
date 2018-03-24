#ifndef FONCTIONSH
#define FONCTIONSH

//*** Includes ***//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

//*** Defines ***//
#define PORT 80
#define HOST "192.168.1.105"
#define FICHIER "index.php"

//*** Structs ***//
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef int SOCKET;

//*** Variables ***//
char rep[1000];

//*******************************************************************************
// Prototypes fonctions
//*******************************************************************************

//** Connection **/
void connection();
SOCKET initSocket();

//** Requete **//
void creerRequete(char* buf, char* lien, char* fichier); // Créer Requette
void afficherRequete(char* requete); // Afficher Requette

#endif
