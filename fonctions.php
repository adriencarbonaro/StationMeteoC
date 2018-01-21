<?php

//***************************************************************
// Fonction permettant la création de la requete HTTP
//***************************************************************
// function creerRequete($name)
//***************************************************************
// $name : adresse IP du shield ethernet de la station météo
//***************************************************************
function creerRequete($name){

	//****************************
	// Requete 
	//****************************
	// ?M car on veut récupérer
	// la trame M
	//****************************
	$envoi  = "GET /?M HTTP/1.1\r\n";
	$envoi .= "Host: ".$name."\r\n\r\n"; // On doit finir la requete par \r\n\r\n

	return $envoi;
}

//***************************************************************
// Fonction permettant la création de la socket PHP
//***************************************************************
// function creerSocket($requete, $name)
//***************************************************************
// $requete : le contenu de la requete précédemment crée
// $name    : adresse IP du shield ethernet de la station météo
//***************************************************************
function creerSocket($requete, $name){

	//****************************
	// ouverture socket
	//****************************
	$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
	if($socket < 0){
	        die('FATAL ERROR: socket_create() : " '.socket_strerror($socket).' "');
	}
	 
	if (socket_connect($socket,gethostbyname($name),80) < 0){
	        die('FATAL ERROR: socket_connect()');
	}
	 
	//****************************
	// Envoi demande
	//****************************
	if(($int = socket_write($socket, $requete, strlen($requete))) === false){
	        die('FATAL ERROR: socket_write() failed, '.$int.' characters written');
	}

	return $socket;
}

//********************************************************************************
// Fonction permettant de récupérer la réponse du serveur (shield Arduino)
//********************************************************************************
// function getReponse($socket)
//********************************************************************************
// $socket : socket PHP précédemment crée permettant de se connecter au serveur
//********************************************************************************
function getReponse($socket){
	
	//******************
	// Lecture réponse
	//******************
	$reception = '';
	while($buff = socket_read($socket, 2000)){
	   $reception.=$buff;
	}

	return $reception;
}

//*****************************************************************************************************************
// Fonction permettant d'extraire la trame de la réponse du serveur
//*****************************************************************************************************************
// function extraireTrame($réponse)
//*****************************************************************************************************************
// $réponse : réponse complete du serveur
//*****************************************************************************************************************
// ex :
// Réponse originale : HTTP/1.1 200 OK 
//					   Content-Type: text/html 
//					   Access-Control-Allow-Origin: *
//					   M;108;108;1016;53;
// Trame : M;108;108;1016;53;
//*****************************************************************************************************************
function extraireTrame($réponse){
	
	$trame = strstr($réponse, "M;"); // On récupère la trame et on la sauvegarde
  	return $trame;
}


?>