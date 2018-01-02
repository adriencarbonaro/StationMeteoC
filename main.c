//---------------------------------------------------------------------------
// Requete HTTP en C - Rev 0.3
//---------------------------------------------------------------------------
// Crée une requette vers le site www.perdu.com
// et lit affiche la réponse du site
//---------------------------------------------------------------------------
// Ressources C : Sockets
// Liens utiles : http://broux.developpez.com/articles/c/sockets/
//                https://openclassrooms.com/courses/les-requetes-http         
//---------------------------------------------------------------------------
// Rev 0.1 :   - On demande le site à l'utilisateur
//             - On affiche la requette
//             - On affiche la réponse et le contenu
//---------------------------------------------------------------------------
// Rev 0.2 :   - Création d'une fonction pour créer la requette
//               en fonction de l'url de l'utilisateur
//             - Possibilité de mettre un code à la requete 
//               pour faire des requetes avec paramètres
//               ex : 192.168.1.17/?M
//---------------------------------------------------------------------------
// Rev 0.3 :   - Créations de différentes fonctions
//               pour mieux découper le programme
//             - Blindage du code de requete demandé
//             - Enregistrement de la trame dans une variable 
//               pour l'utiliser plus tard
//---------------------------------------------------------------------------
// Rev 1.0 :   - Fichiers ???
// A faire :   - Sortir l'acquisition de la trame de la fonction d'affichage
//             -> Créer une fonction d'acquisition
//---------------------------------------------------------------------------
// Auteur      : Adrien CARBONARO
// Mise à jour : 02/01/2018 - 19:39
//---------------------------------------------------------------------------

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

//--------------------------------------------------------------
// Main
//--------------------------------------------------------------
int main(int argc, char const *argv[])
{
   
   SOCKET sock; // On crée la socket
   sock = socket(AF_INET, SOCK_STREAM, 0); // On configure la socket
   
   if(sock != -1)
   {
      char lien[100];
      char code[10] = {'0'};
      char codes_trames[10] = "MXSV"; // Tous les codes possibles M, V, X, S
      int i=0;
      char* trame = NULL;
      printf("Trame : %s", trame);
      printf("Entrez le nom d'un site : ");
      fgets(lien, sizeof(lien), stdin); // On récupère l'entrée au clavier
      clean(lien, stdin); // On nettoie le flux d'entrée clavier
      if(strcmp(lien, "192.168.1.17") == 0){
         demanderCode(code, codes_trames); // On demande le code à l'utilisateur en blindant
      }

      const char* url = lien;
      struct hostent* host = gethostbyname(url);
      SOCKADDR_IN sin;
      bcopy(host->h_addr, &(sin.sin_addr), host->h_length); // erreur inexpliquée mais programme marche
      sin.sin_family= AF_INET;
      sin.sin_port= htons(PORT);
      //pas besoin de bind, j attaque le connect
      if(connect(sock, (SOCKADDR*)&sin, sizeof sin)!= -1)
      {
         //printf("connexion établie ! \n");
         char buf[1000]; // Buffer contenant la requete
         creerRequete(buf, lien, code); // On crée la requete HTTP
         if(send(sock, buf, strlen(buf), 0)!=-1)
         {
            //printf("Requete envoyée! \n");
            while(recv(sock, rep, 1000,0)>0)
            {
               afficherReponse(code, trame, rep);  
            }
            printf("\n");
         }else perror("Requete non transmise\n");
      }else perror("La connexion a echoué !\n");
   }else perror("chkeltiha f la creation ! ");
}

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
   
   // Le "/" signifie qu'on récupère la racine du serveur
   // On peut écrire à la place /fichier.php
   // pour récupérer un fichier en particulier
   strcpy(buf, "GET /");
   //printf("longueur : %d\n", (int)strlen(code));
   strcat(buf, "?");  // On ajoute le "?"
   strcat(buf, code); // et le code (M, X, V ...)
   
   // On ajoute le reste de la requete dans le buffer //
   strcat(buf, " HTTP/1.1\r\nHost: ");
   strcat(buf, lien);
   strcat(buf, "\r\n\r\n"); // Les requetes HTTP doivent se terminer par \r\n\r\n

   //afficherRequete(buf); // On affiche la requete
}

//--------------------------------------------------------------
// Afficher Requete
//--------------------------------------------------------------
// void afficherRequete(char* requete)
//--------------------------------------------------------------
// requete : la requete qu'on envoie au serveur
//--------------------------------------------------------------
// On affiche la requete complète à envoyer au serveur
// ex :
//
// GET /?M HTTP/1.1
// Host: 192.168.1.17
//
//--------------------------------------------------------------
void afficherRequete(char* requete){
   printf("--------\n");
   printf("REQUETE :\n\n");
   puts(requete);
   printf("--------\n"); // Pour bien délimiter la requete à l'affichage
}

//----------------------------------------------------------------------------
// Nettoyer le buffer du clavier
//----------------------------------------------------------------------------
// void clean(const char *buffer, FILE *fp)
//----------------------------------------------------------------------------
// buffer  : le buffer à nettoyer
// fp : le flux d'entrée (le flux du clavier)
//----------------------------------------------------------------------------
// https://openclassrooms.com/courses/utiliser-les-bonnes-fonctions-d-entree
//----------------------------------------------------------------------------
void clean(const char *buffer, FILE *fp)
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
        *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

//----------------------------------------------------------------------------
// Demander le code de requete
//----------------------------------------------------------------------------
// void demanderCode(char* code, char* codes_trames)
//----------------------------------------------------------------------------
// code : la chaine vide qu'on renverra après vérifications
// codes_trames : le tableau de caractères contenant
//                tous les codes acceptés
//----------------------------------------------------------------------------
void demanderCode(char* code, char* codes_trames){
   int i = 0; // index pour parcourir le tableau des codes acceptés
   int test = 0; // le binaire disant si le code est bon

   printf("Entre le code de trame (M, X, S, V) : ");
   fgets(code, sizeof(code), stdin); // On récupère l'entrée au clavier du code
   clean(code, stdin); // On nettoie le flux du clavier

   for(i=0; i<strlen(codes_trames); i++){ // On parcourt le tableau des codes acceptés

      // Si le code n'existe pas dans le tableau des codes acceptés OU que le code fait plus d'1 caractère
      // Et que le binaire test est toujours à 0
      if((code[0] != codes_trames[i] || (int)strlen(code) != 1) && test == 0)
      {
         test = 0; // On laisse le binaire à 0;
      }
      
      // Si le code existe dans le tableau et qu'il fait bien un seul caractère
      else if(code[0] == codes_trames[i] && (int)strlen(code) == 1)
      {
         test = 1; // On met le binaire à 1;
      }
   }


   if(test == 0){ // Si le code est incorrect (qu'il n'est pas dans le tableau des codes acceptés ou qu'il fait plus d'un caractère)
      demanderCode(code, codes_trames); // On relance la fonction et on test un nouveau code
   }
}

//----------------------------------------------------------------------------
// Convertir un char en string
//----------------------------------------------------------------------------
// char* charToString(char c)
//----------------------------------------------------------------------------
// c : le caractère à convertir
//----------------------------------------------------------------------------
char* charToString(char c)
{
   char *str=malloc(2*sizeof(char));
   if(str==NULL) return NULL;
   str[0]=c;
   str[1]='\0';
   return str;
}

//----------------------------------------------------------------------------
// Afficher la réponse à la requete
//----------------------------------------------------------------------------
// void afficherReponse(char* code, char* trame, char* rep)
//----------------------------------------------------------------------------
// code  : le code de la requete
// trame : la trame vide qu'on va récupérer et enregistrer
// rep   : la réponse du serveur
//----------------------------------------------------------------------------
void afficherReponse(char* code, char* trame, char* rep){
   if(code[0] != '0'){ // Si il y a un code de requete
      trame = strstr(rep, strcat(charToString(code[0]), ";")); // On récupère la trame et on la sauvegarde
      printf("Trame : %s\n\n", trame); // On affiche la trame
   }

   if(trame == NULL) puts(rep); // S'il n'y a pas de trame on affiche la réponse
                                // (ex : sur www.perdu.com on affiche la page html)
}