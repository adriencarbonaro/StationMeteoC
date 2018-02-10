
#include "fonctions.h"

//--------------------------------------------------------------
// Créer la connection
//--------------------------------------------------------------
// void connection()
//--------------------------------------------------------------
// On crée la connection puis appelle les autres fonctions
// pour créer puis envoyer la requete vers index.php
//--------------------------------------------------------------
void connection(){
  SOCKET sock; // On crée la socket
  sock = initSocket();

  if(sock != -1)
  {

      // HOST et FICHIER définis dans fonctions.h
    char lien[100] = HOST; 
    char fichier[100] = FICHIER;             

    struct hostent* host = gethostbyname(lien);
    SOCKADDR_IN sin;
      bcopy(host->h_addr, &(sin.sin_addr), host->h_length); // erreur inexpliquée mais programme marche
      sin.sin_family= AF_INET;
      sin.sin_port= htons(PORT);

      if(connect(sock, (SOCKADDR*)&sin, sizeof sin)!= -1)
      {
         //printf("connexion établie ! \n");
         char buf[1000]; // Buffer contenant la requete
         

         creerRequete(buf, lien, fichier); // On crée la requete HTTP
         
         if(send(sock, buf, strlen(buf), 0)!=-1)
         {
               //printf("Requete envoyée! \n");
               //while(recv(sock, rep, 1000,0)>0)
               //{
               //   puts(rep);
               //}

         }
         else perror("Requete non transmise\n");
         
         
       }else perror("La connexion a echoué !\n");


     }else perror("error ! ");
   }

//--------------------------------------------------------------
// Crée la socket de connection
//--------------------------------------------------------------
// void connection()
//--------------------------------------------------------------
// On crée la socket permettant ensuite de se connecter
// au serveur de la Raspberry Pi
//--------------------------------------------------------------
SOCKET initSocket(){
  SOCKET s;
  s = socket(AF_INET, SOCK_STREAM, 0); // On configure la socket
  return s;
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
void creerRequete(char* buf, char* lien, char* fichier){

   // Le "/" signifie qu'on récupère la racine du serveur
   // On peut écrire à la place /fichier.php
   // pour récupérer un fichier en particulier
 strcpy(buf, "GET /");
   //printf("longueur : %d\n", (int)strlen(code));
   //strcat(buf, "?");  // On ajoute le "?"
 strcat(buf, fichier);
   // On ajoute le reste de la requete dans le buffer //
 strcat(buf, " HTTP/1.1\r\nHost: ");
 strcat(buf, lien);
   strcat(buf, "\r\n\r\n"); // Les requetes HTTP doivent se terminer par \r\n\r\n

   afficherRequete(buf); // On affiche la requete
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
// Afficher la réponse à la requete
//----------------------------------------------------------------------------
// void afficherReponse(char* code, char* trame, char* rep)
//----------------------------------------------------------------------------
// code  : le code de la requete
// trame : la trame vide qu'on va récupérer et enregistrer
// rep   : la réponse du serveur
//----------------------------------------------------------------------------
  void afficherReponse(char* trame, char* rep){
   //if(code[0] != '0'){ // Si il y a un code de requete
     // trame = strstr(rep, strcat(charToString(code[0]), ";")); // On récupère la trame et on la sauvegarde
      //printf("Trame : %s\n\n", trame); // On affiche la trame
   //}

   if(trame == NULL) puts(rep); // S'il n'y a pas de trame on affiche la réponse
                                // (ex : sur www.perdu.com on affiche la page html)

   else puts(trame);
 }