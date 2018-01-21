<?php

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

	return socket;
}

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


?>