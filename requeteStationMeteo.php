<?php

//*****************************************************************************************************************
// Requete HTTP en PHP - Rev 0.1
//*****************************************************************************************************************
// Fichiers :  - requeteStationMeteo.php
//*****************************************************************************************************************
// Crée une requette vers la station météo
// et affiche la réponse (Trame de mesure "M")
//*****************************************************************************************************************
// Ressources PHP : Sockets
// Liens utiles   : https://openclassrooms.com/courses/les-requetes-http  
//*****************************************************************************************************************
// Rev 0.1 :   - On écrit l'adresse de la station dans le programme directement
//			   - Aucune interaction avec l'utilisateur car programme automatique
//*****************************************************************************************************************
// Auteur      : Adrien CARBONARO
// Mise à jour : 20/01/2018 - 23:02
//*****************************************************************************************************************

include ('bdd/bddconnect.php');
include ('fonctions.php');

//header('Content-Type: text/plain');
 
$adresseIP = "192.168.1.17";

$requeteHTTP = creerRequete($adresseIP);

$socket = creerSocket($adresseIP);

$réponse = getReponse($socket);
 
socket_close($socket);

echo $réponse;

?>