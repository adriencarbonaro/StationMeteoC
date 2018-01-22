# Station Meteo

# Description
Récupération données Station Météo grâce à une carte Raspberry Pi puis envoi vers une base de données.

Envoi de requetes **GET HTTP en PHP** pour récupérer les données de la stations.
Connexion à la base de donnée sur le serveur de la raspberry pi avec LAMP (**L**inux **A**pache **M**ySQL **P**HP).
Sauvegarde des données dans la base de données avec ajout de la date et d'un ID.

La carte Raspberry lance un programme en C lorsqu'elle s'allume.
Ce programme lance lui même le script PHP qui récupère les mesures puis les enregistre dans la base de données.

# Ressources
- Raspberry Pi serveur.
- Station Météo avec SHIELD Ethernet.
- Base de donnée MySQL sur le serveur de la carte Raspberry.

Langages :

- C
- PHP
- MySQL

# Auteur et mise à jour
**Adrien CARBONARO**
*22-01-2018 11:58*