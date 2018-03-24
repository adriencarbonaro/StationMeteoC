<!-- ***********************************************************************************************************-->
<!-- Requete HTTP en PHP - Rev 1.0 -->
<!-- ***********************************************************************************************************-->
<!-- Fichiers :  - requeteStationMeteo.php -->
<!-- ***********************************************************************************************************-->
<!-- Crée une requette vers la station météo -->
<!-- Affiche la réponse (Trame de mesure "M") -->
<!-- Enregistre la trame dans la base de donnée en y ajoutant la date et une ID -->
<!-- ***********************************************************************************************************-->
<!-- Ressources PHP : Sockets -->
<!-- Liens utiles   : https://openclassrooms.com/courses/les-requetes-http   -->
<!-- ***********************************************************************************************************-->
<!-- Rev 0.1 :   - On écrit l'adresse de la station dans le programme directement -->
<!--			 - Aucune interaction avec l'utilisateur car programme automatique -->
<!-- ***********************************************************************************************************-->
<!-- Rev 1.0 :   - On récupère la trame depuis la station météo -->
<!--			 - On enregistre la trame dans la base de données sur le serveur -->
<!-- ***********************************************************************************************************-->
<!-- Auteur      : Adrien CARBONARO -->
<!-- Mise à jour : 21/01/2018 - 15:25 -->
<!-- ***********************************************************************************************************-->

<html>
<body>
<p>Boucle</p>
	<script>


lancerRequete();
setInterval(function(){ lancerRequete(); }, 1000);


function lancerRequete(){
	var requete = new XMLHttpRequest(); // créer un objet de requête

	requete.open("GET", "index.php", true); // On construit la requête
    requete.send(null); // On envoie !
    requete.onreadystatechange = function() { // on attend le retour
        if (requete.readyState == 4) { // Revenu !
            if (requete.status == 200) { // Retour s'est bien passé !
                // fonction d'affichage (ci-dessous)
            	console.log(requete.responseText); 

            }

            else { // Retour s'est mal passé :(
            alert(requete.status, requete.statusText);
        	}
    	}
	};
}
</script>

</body>
</html>
