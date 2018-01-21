<?php

//*****************************************************************************************************************
// Requete HTTP en PHP - Rev 1.0
//*****************************************************************************************************************
// Fichiers :  - requeteStationMeteo.php
//*****************************************************************************************************************
// Crée une requette vers la station météo
// Affiche la réponse (Trame de mesure "M")
// Enregistre la trame dans la base de donnée en y ajoutant la date et une ID
//*****************************************************************************************************************
// Ressources PHP : Sockets
// Liens utiles   : https://openclassrooms.com/courses/les-requetes-http  
//*****************************************************************************************************************
// Rev 0.1 :   - On écrit l'adresse de la station dans le programme directement
//			   - Aucune interaction avec l'utilisateur car programme automatique
//*****************************************************************************************************************
// Rev 1.0 :   - On récupère la trame depuis la station météo
//			   - On enregistre la trame dans la base de données sur le serveur
//*****************************************************************************************************************
// Auteur      : Adrien CARBONARO
// Mise à jour : 21/01/2018 - 15:25
//*****************************************************************************************************************

include ('bdd/bddconnect.php');
include ('fonctions.php');

// adresse IP du shield ethernet de la station météo
$adresseIP = "192.168.1.17";

// On crée la requette pour récupérer la trame
$requeteHTTP = creerRequete($adresseIP);

// On envoie la requete en créant une socket PHP
$socket = creerSocket($requeteHTTP, $adresseIP);

// On récupère la réponse du serveur (de la Station Météo ici)
$réponse = getReponse($socket);
 
// On ferme la socket
socket_close($socket);

// On extrait la trame de la réponse
// Réponse originale : HTTP/1.1 200 OK Content-Type: text/html Access-Control-Allow-Origin: * M;108;108;1016;53;
// Trame : M;108;108;1016;53;
$trame = extraireTrame($réponse);

// On affiche le tout sur la page (debug)
echo "Réponse : " . $réponse . "<br/>";
echo "Trame : " . $trame;

// On enregistre la trame dans la base de donnée en y ajoutant une ID et la date
connectMysql($trame);

?>