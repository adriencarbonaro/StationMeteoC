# Station Meteo

# Description
Récupération données Station Météo grâce à une carte Raspberry Pi puis envoi vers une base de données.

Un programme en **C** crée une connexion vers le serveur contenue sur la carte RPi, et appelle le fichier *index.php*.
Le programme C tourne à l'infinie à une cadence d'un appelle toutes les 5 minutes.

Le script PHP crée une requete vers la Station Météo pour récupérer les données.
Ìl les envoie ensuite sur une base de donnée contenue elle aussi sur la carte RPi.

Connexion à la base de donnée sur le serveur de la raspberry pi avec LAMP (**L**inux **A**pache **M**ySQL **P**HP).
Sauvegarde des données dans la base de données avec ajout de la date et d'un ID.

La carte Raspberry lance le programme en C lorsqu'elle s'allume.

# Programmes
Deux possibilités :

- Programmes en C qui lance le script PHP pour récupérer les trames et les enregistrer : `main.c`, `fonctions.c`, `fonctions.h`, puis `index.php`
- Programmes en PHP pour récupérer les trames et les enregistrer sur la base de données : `index.php`,`fonctions.php`, `bdd/bddconnect.php`.

# Ressources
- Raspberry Pi serveur LAMP.
- Station Météo avec SHIELD Ethernet.
- Base de donnée MySQL sur le serveur de la carte Raspberry.

Langages :

- C
- PHP
- MySQL

# Auteur et mise à jour
**Adrien CARBONARO**

*10-02-2018 23:04*