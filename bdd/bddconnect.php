<?php

//***************************************************************//
// Fonction permettant la connection au serveur local et à la DB 
//***************************************************************//
// function connectMysql($trame)
//***************************************************************//
// $trame : la trame à enregistrer
//***************************************************************//

function connectMysql($trame){

    //***************************************************************//
    // INFORMATION DE CONNEXION À LA BASE DE DONNÉES
    //***************************************************************//

    // On définit ici les infos de la base de donées
    // (nom du serveur, nom d'utilisateur, password, nom de la base à laquelle se connecter)
    $servername = "localhost";      // Nom du serveur
    $username   = "phpmyadmin";     // Nom d'utilisateur ("phpmyadmin" ce qui nous permet de se connecter
                                    // à l'inteface web avec notre machine en tapant 192.168.1.163/phpmyadmin)
                                    // avec 192.168.1.163 l'IP de la carte RPi
    $password   = "root";           // Mot de passe de "root"
    $dbname     = "StationMeteo";   // Nom de la base de données MariaDB

    //***************************************************************
    // CONNEXION À LA BASE DE DONNÉES
    //***************************************************************

    // Connection au serveur
    $conn = new mysqli($servername, $username, $password);
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 

     // Crée la DB si elle n'existe pas
    if (!$conn->query("CREATE database IF NOT EXISTS ". $dbname)){
        echo "Error creating database: " . $conn->error; echo "<br>";
    }
     // Connection à la DB 
    if (!$conn->query("USE ". $dbname)){
        echo "Error using database: " . $conn->error; echo "<br>";
    }
    
    //***************************************************************
    // CRÉATION DES TABLES
    //***************************************************************

    // Création de la table TableM si elle n'existe pas déjà
    $sql = "CREATE TABLE IF NOT EXISTS TableM (
    ID smallint UNSIGNED PRIMARY KEY AUTO_INCREMENT,
    Code varchar(1) NOT NULL,
    DateTrame timestamp NOT NULL,
    Donnee varchar(50) NOT NULL
    )";
    
    // Application de la demande SQL
    if(!$conn->query($sql)){
        echo "Table creation failed: (" . $sql . ") " . $conn->error; echo "<br>";
    }

    if(!$conn->query($sql)){
        echo "Table creation failed: (" . $sql . ") " . $conn->error; echo "<br>";
    }
    
    //***************************************************************
    // ENREGISTREMENT DES VALEURS
    //***************************************************************

    // Enregistrement des valeurs de la trame M
    $result= $conn->query("SELECT * FROM TableM");
    $row_cnt = $result->num_rows; 
    echo "Row : " . $row_cnt;

    // On vérifie que l'index soit bien à jour
    // Ex : Si on a 4 trame et qu'on supprime les 3 premières,
    // on remet ici l'index à 1 pour qu'il ajoute une valeur 2 et non 5
    $sql = "ALTER TABLE TableM AUTO_INCREMENT=" . $row_cnt;
    $conn->query($sql);
    

    $sql ="INSERT INTO TableM (Code, Donnee) VALUES ('M', '$trame')";
    
    if(!$conn->query($sql)){
        echo "Table creation failed: (" . $sql . ") " . $conn->error;
    }
    
    
    // On retourne $conn (optionnel)
    return $conn;
}



?>