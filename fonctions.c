
#include "fonctions.h"

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

char* acquerirTrame(char* code, char* trame, char* rep){
  if(code[0] != '0'){ // Si il y a un code de requete
      trame = strstr(rep, strcat(charToString(code[0]), ";")); // On récupère la trame et on la sauvegarde
   }

   return trame;
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

//-----------------------------------------------------------------------------------
// Initialiser le fichier d'enregistrement
//-----------------------------------------------------------------------------------
// FILE* initFichier()
//-----------------------------------------------------------------------------------
// return : On retourne le pointeur sur le fichier ouvert pour pouvoir
//          lire et écrire dedans
// a+     : Droit d'accès en lecture et écriture mais seulement à partir de la fin
//          du fichier (permet d'éviter de supprimer des données)
//-----------------------------------------------------------------------------------
FILE* initFichier(){
  
  FILE* fichier = NULL;
  fichier = fopen("test.txt", "a+");
  
  if(fichier != NULL)
  {
    return fichier;
  }

  else
  {
    printf("ERREUR OUVERTURE FICHIER");
    return NULL;
  }
}

//-----------------------------------------------------------------------------------
// Ferme le fichier d'enregistrement
//-----------------------------------------------------------------------------------
// void fermerFichier(FILE* fichier)
//-----------------------------------------------------------------------------------
// fichier : Le pointeur du fichier à fermer
//-----------------------------------------------------------------------------------
void fermerFichier(FILE* fichier){
  
  if(fichier != NULL)
  {
    fclose(fichier);
  }

  else
  {
    printf("ERREUR FERMETURE FICHIER");
  }
}

//----------------------------------------------------------------------------
// Enregistrer la trame à la fin du fichier
//----------------------------------------------------------------------------
// void enregistrerTrame(char* trame, FILE* fichier)
//----------------------------------------------------------------------------
// trame   : la trame extraite de la réponse
// fichier : le pointeur du fichier dans lequel enregistrer la trame
//----------------------------------------------------------------------------
void enregistrerTrame(char* trame, FILE* fichier){
  if(trame != NULL) fprintf(fichier, "Trame : %s\n", trame);
  else fprintf(fichier, "Trame : N/A\n");
}