# Contexte
Dans le cadre de la matière Génie Logiciel et modélisation UML des 3IF de l'INSA de Lyon, nous implémentons deux fonctionalités principales du sujet AirWatcher. Notre équipe est composée de Louis Tricot, Loann Largeron, Nathan Sadoun, Maxime Boyer et Julien Bouvier.
Voici donc notre TP 3IF INSA Lyon nommé Air Watcher.

# Sujet
L'objectif est de collecter, traiter et gérer les données générées par des capteurs de qualité de l'air. Il est aussi demandé de traiter et gérer ces capteurs ainsi que des AirCleaners installés sur le territoire.

# Fonctions implémentées
Nous avons choisis d'implémenter les fonctionnalités suivantes :
- Identifier capteur défaillant
- Observer l'impact d'un air cleaner
    - qui utilise le calcul de la qualité de l'air sur une zone circulaire

# Exigences minimales
Pour lancer le programme, il vous faut une distribution basée sous UNIX. Soit une version de Linux ou Ubuntu par exemple ou bien une machine virtuelle ou une WSL ubuntu adaptée disponible sous windows.
Assurez-vous aussi d'avoir le compilateur gcc d'installé. Si ce n'est pas le cas, lancer les lignes suivantes à partir d'un terminal :
    sudo apt install gcc
Puis entrez votre mot de passe.
Aucun autre logiciel ou paquet n'est nécessaire.

# Lancement de l'application
Pour lancer les parties implémentées de AirWatcher, il faut lancer le makefile principal. Pour se faire, il faut lancer un terminal à partir du répertoire principal puis exécuter les lignes suivantes :
    make
    ./main

Pensez à vérifier que le paramètre EXE du makefile soit de cette forme :
    EXE = main

# Tests
Pour lancer la batterie de tests, exécutez le makefile du répertoir Tests. Vous pourrez voir le nombre de tests lancés, le nombre de tests réussis (passés) et le nombre de test échoués. Ces informations seront aussi affichées pour chaque tests.
Pensez à vérifier que le paramètre EXE du makefile soit de cette forme :
    EXE = tester
Pour se faire ouvrez un terminal à partir du répertoire principal puis exécutez les lignes suivantes dans un terminal de commandes :
    make
    ./tester

