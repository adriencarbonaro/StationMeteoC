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


//header('Content-Type: text/plain');
 
// Addresse de la Station Météo sur le réseau local
$name = '192.168.1.17';
 
//****************************
// Requete 
//****************************
// ?M car on veut récupérer
// la trame M
//****************************
$envoi  = "GET /?M HTTP/1.1\r\n";
$envoi .= "Host: ".$name."\r\n\r\n"; // On doit finir la requete par \r\n\r\n
 
//******************
// ouverture socket
//******************
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if($socket < 0){
        die('FATAL ERROR: socket_create() : " '.socket_strerror($socket).' "');
}
 
if (socket_connect($socket,gethostbyname($name),80) < 0){
        die('FATAL ERROR: socket_connect()');
}
 
//***************
// Envoi demande
//***************
if(($int = socket_write($socket, $envoi, strlen($envoi))) === false){
        die('FATAL ERROR: socket_write() failed, '.$int.' characters written');
}

 
//******************
// Lecture réponse
//******************
$reception = '';
while($buff = socket_read($socket, 2000)){
   $reception.=$buff;
}
echo $reception;
/*/lecture réponse*/
 
socket_close($socket);

?>