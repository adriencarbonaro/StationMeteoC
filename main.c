//--------------------------------------------------------------------
// Requete HTTP en C
//--------------------------------------------------------------------
// Crée une requette vers le site www.perdu.com
// et lit affiche la réponse du site
//--------------------------------------------------------------------
// Ressources C : Sockets
// Liens utiles : http://broux.developpez.com/articles/c/sockets/
//                https://openclassrooms.com/courses/les-requetes-http         
//--------------------------------------------------------------------
// Rev 0.1 :   - On demande le site à l'utilisateur
//             - On affiche la requette
//             - On affiche la réponse et le contenu
//--------------------------------------------------------------------
// Rev 0.2 :   - Création d'une fonction pour créer la requette
//               en fonction de l'url de l'utilisateur
//             - Possibilité de mettre un code à la requete 
//               pour faire des requetes avec paramètres
//               ex : 192.168.1.17/?M
//--------------------------------------------------------------------
// Auteur      : Adrien CARBONARO
// Mise à jour : 01/01/2018 20:25
//--------------------------------------------------------------------

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

//--------------------------------------------------------------
// Créer Requete
//--------------------------------------------------------------
// void creerRequete(char* buf, char* lien, char* code)
//--------------------------------------------------------------
// buf  : le buffer final qui contient la requete
// lien : l'url saisie par l'utilisateur
// code : le code en paramètre pour une requette de type
//        192.168.1.17/?M
//--------------------------------------------------------------
// On crée la requete avec l'url de l'utilisateur
// et le paramètre
//--------------------------------------------------------------
void creerRequete(char* buf, char* lien, char* code){

   // On commence à écrire la requete
   printf("--------\n");
	printf("REQUETE :\n\n");
	
   // Le "/" signifie qu'on récupère la racine du serveur
   // On peut écrire à la place /fichier.php
   // pour récupérer un fichier en particulier
   strcpy(buf, "GET /"); 

	// Si il y a un code à un caractère //
	if(strlen(code) == 1){
		strcat(buf, "?");  // On ajoute le "?"
		strcat(buf, code); // et le code (M, X, V ...)
	}
	
	// On ajoute le reste de la requete dans le buffer //
	strcat(buf, " HTTP/1.1\r\nHost: ");
	strcat(buf, lien);
	strcat(buf, "\r\n\r\n"); // Les requetes HTTP doivent se terminer par \r\n\r\n

	// On affiche la requete
	puts(buf);
	printf("--------\n"); // Pour bien délimiter la requete à l'affichage

}

//--- Main ---//
int main()
{
   SOCKET sock; // On crée la socket
   sock = socket(AF_INET, SOCK_STREAM, 0); // On configure la socket
   
   if(sock != -1)
   {
   	char lien[100];
   	char code[10];

   	printf("Socket créée \n");

      // On saisie l'url
   	printf("Entrez le nom d'un site : ");
   	scanf("%s", lien);
   	fflush(stdin);
   	printf("Le nom de votre site est %s \n", lien);

      // On saisie le code de paramètre de requete
   	printf("Entrez le code : ");
   	scanf("%s", code);
   	fflush(stdin);

   	const char* url = lien;
   	struct hostent* host = gethostbyname(url);
   	SOCKADDR_IN sin;
      bcopy(host->h_addr, &(sin.sin_addr), host->h_length); // erreur inexpliquée mais programme marche
      sin.sin_family= AF_INET;
      sin.sin_port= htons(PORT);
      
      // On se connecte au serveur
      if(connect(sock, (SOCKADDR*)&sin, sizeof sin)!= -1)
      {
      	printf("connexion établie ! \n");
      	char buf[1000];
      	// On cre la requete
         creerRequete(buf, lien, code);
      	// On envoie la requete au serveur
         if(send(sock, buf, strlen(buf), 0)!=-1)
      	{
         	printf("Requete envoyée! \n");
      		// Tant qu'on reçoie des réponses du serveur
            while(recv(sock, rep, 1000,0)>0)
      		{
      			printf("je reçois !\n");
      			printf("%s", rep);
      		}
      		printf(" Fin requete \n");
      	
         }else perror("requete non transmise  \n");
      
      }else perror(" la connexion a echoué !\n");
   
   }else perror("chkeltiha f la creation ! ");
}