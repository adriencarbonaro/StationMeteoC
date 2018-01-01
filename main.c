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
// Rev 0.1 : 	- On demande le site à l'utilisateur
//				- On affiche la requette
//				- On affiche la réponse et le contenu
//--------------------------------------------------------------------
// Auteur      : Adrien CARBONARO
// Mise à jour : 31/12/2017 20:00
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

//--- Main ---//
int main()
{
   SOCKET sock; // On crée la socket
   sock = socket(AF_INET, SOCK_STREAM, 0); // On configure la socket
   
   if(sock != -1)
   {
      printf("Socket créée \n");
      printf("Entrez le nom d'un site : ");
      char lien[100];
      scanf("%s", lien);
      printf("Le nom de votre site est %s \n", lien);
      const char* url = lien;
      struct hostent* host = gethostbyname(url); // On récupère l'url
      SOCKADDR_IN sin;
      bcopy(host->h_addr, &(sin.sin_addr), host->h_length); // erreur inexpliquée mais programme marche
      sin.sin_family= AF_INET;
      sin.sin_port= htons(PORT);
      //pas besoin de bind
      if(connect(sock, (SOCKADDR*)&sin, sizeof sin)!= -1)
      {
         printf("connexion établie ! \n");
         printf("--------\n");
         printf("REQUETE :\n\n");
         // On crée la requette
         char* buf = "GET / HTTP/1.1\r\nHost: www.perdu.com\r\n\r\n";
         puts(buf);
         printf("--------\n");
         if(send(sock, buf, strlen(buf), 0)!=-1)
         {
            printf("Requete envoyée! \n");
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