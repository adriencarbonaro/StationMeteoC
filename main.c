//*****************************************************************************************************************
// Requete HTTP en C - Rev 2.0
//*****************************************************************************************************************
// Fichiers :  - main.c
//             - fonctions.h
//             - fonctions.c
//*****************************************************************************************************************
// Crée une requette vers le serveur de la Raspberry Pi (index.php)
// Boucle infinie toute les 5 minutes
//*****************************************************************************************************************
// Ressources C : Sockets
// Liens utiles : http://broux.developpez.com/articles/c/sockets/
//                https://openclassrooms.com/courses/les-requetes-http  
//                https://openclassrooms.com/forum/sujet/envoyer-une-chaine-de-caractere-63149
//                https://openclassrooms.com/courses/apprenez-a-programmer-en-c/lire-et-ecrire-dans-des-fichiers       
//*****************************************************************************************************************
// Rev 0.1 :   - On demande le site à l'utilisateur
//             - On affiche la requette
//             - On affiche la réponse et le contenu
//*****************************************************************************************************************
// Rev 0.2 :   - Création d'une fonction pour créer la requette
//               en fonction de l'url de l'utilisateur
//             - Possibilité de mettre un code à la requete 
//               pour faire des requetes avec paramètres
//               ex : 192.168.1.17/?M
//*****************************************************************************************************************
// Rev 0.3 :   - Créations de différentes fonctions
//               pour mieux découper le programme
//             - Création de différents fichiers pour ranger ces fonctions
//             - Blindage du code de requete demandé
//             - Enregistrement de la trame dans une variable 
//               pour l'utiliser plus tard
//*****************************************************************************************************************
// Rev 1.0 :   - Enregistrement de la trame dans un fichier texte
//*****************************************************************************************************************
// Rev 2.0 :   - Boucle infinie toute les 5 minutes
//             - Tout le travail sur la requete se fait ensuite dans le fichier index.php
//*****************************************************************************************************************
// Auteur      : Adrien CARBONARO
// Mise à jour : 10/02/2018 - 22:38
//*****************************************************************************************************************

// Fichier contenant tous les prototypes de fonctions
// et les définitions de préprocesseur
#include "fonctions.h"

//--------------------------------------------------------------
// Main
//--------------------------------------------------------------
int main(int argc, char const *argv[])
{
   while(1){
      connection();
      sleep(300);
   }
}