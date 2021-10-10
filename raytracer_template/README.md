# Projet de lancer de rayon - rendu final

Projet de modélisation 3D traitant du rayTracing

- Source du TD/TD: disponible en annexe en PDF

- Le support de cours : https://moodle.umontpellier.fr/pluginfile.php/957155/mod_resource/content/2/HMIN212-2-Rayon_et_eclairage.pdf

-Pour tout problème d'exécution, merci de me contacter à l'adresse mail suivante: emery.vecchio@gmail.com ## Auteur

* **Émery Bourget-Vecchio** _alias_ [@EmeryBV](https://github.com/EmeryBV)

##Execution
Pour lancer le projet, il suffit de lancer la class main.cpp
Ce fichier contient toutes les méthodes utiles au projet

De base, le projet est calibré pour lancer un rendu avec un phong et des ombres douces, pour avoir les ombres dures, il faut décommenter la partie ombres dure et commenter la partie ombres dures.

De plus, par défaut, le rendu est fait sur des sphères implicites , pour avoir le rendu avec sphère avec maillage, il faut rajouter le chemin qui mène vers les fichiers en .obj ligne 547 et 561.

**Exemple**

sceneObjects.push_back(new Sphere("Glass sphere", vec3(1.0, -1.25, 0.5),0.75));  
to   
sceneObjects.push_back(new Sphere("Glass sphère", vec3(1.0, -1.25, 0.5),0.75,"./mesh/glass_sphere.obj"));

Enfin, de base, l'effet de miroir et de transparence sont activé sur chacune des sphères, pour les désactiver, il suffit de commenter  la partie **MIROIR** ligne 373 et **TRANSPARANCE** ligne 381

##Description des différentes méthodes
Tous les points du sujet sont traités:

- La classe object.h contient les méthodes permettant de détecter les intersections avec les sphères, les plans, et les triangles.
  La méthode d'intersection avec les triangles comprendre également le lissage de phong pour rendre les sphères plus lisses.

La méthode castRay de la class main.cpp est la méthode principale du projet.

Elle permet de:
- faire des ombres dures (**shadowFeeler**) et douces (**shadowFeelerSmooth**) en représentant la lumière sous forme d'une area ronde.
- réaliser un ombrage grâce au modèle de phong à l'aide de la réflexion spéculaire, ambiante et diffuse.
- rendre une surface réfléchississante
- rendre une surface transparente en appliquant un indice de réfraction

__Le programme ne contient pas de méthode pour optimiser la vitesse de rendu__

##Exemple de résultats

Des exemples de rendus se trouve dans le dossier cmake-build-debug/Exemple Rendu. Ce dossier comprend des sous-dossier qui  correspondent à chacune des phases (sauf la 1 car implicite).  
De plus, le dossier art comprend plusieurs rendues esthétiques ou bien des rendus buggé, mais également esthétiques.  

