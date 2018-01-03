//---------------------------------------------------------------------------
// Requete HTTP en C - Rev 0.3
//---------------------------------------------------------------------------
// Fichiers :  - main.c
//             - fonctions .h
//             - fonctions.c
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
//             - Création de différents fichiers pour ranger ces fonctions
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

#include "fonctions.h"

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