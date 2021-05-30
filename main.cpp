/*************************************************************************
                           main.cpp  -  description
                             -------------------
    début                : 04.05.2021
    copyright            : (C) 2021 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/


/************************************************************* INCLUDES */

#include <iostream>
#include <ctime>
#include <string>
#include "Materiel/AirCleaner.h"
#include "Traitement/TraitementMesure.h"
#include "Administration/GestionMateriel.h"

using namespace std;

/********************************************************* DECLARATIONS */
void identifierCapteurDefaillant();
void observerImpactAirCleaner();

/*********************************************************** CONSTANTES */


/***************************************************************** MAIN */


int main(int argc, char* argv[]){
    int choix;
    bool running = true;

    while(running)
        {
        cout << " #####  BIENVENUE DANS AIR_WATCHER #####" << endl;

        cout << " 1 - Identifier les capteur défaillant" << endl;
        cout << " 2 - Observer l'impact d'un AirCleaner" << endl;
        cout << " 3 - Quitter air watcher" << endl;
        cout << " Que voulez-vous faire ? (Entrer 1 ou 2) : ";
        cin >> choix;
        cout << endl;

    
        if(choix == 1)
        {
            identifierCapteurDefaillant();
        }
        else if(choix == 2)
        {
            observerImpactAirCleaner();
        }
        else if(choix == 3)
        {
            cout << " #####  AU REVOIR ! #####" << endl;
            running = false;
        }
        else
        {
            cout << " >> Veuillez entrer un chiffre valide (1, 2 ou 3)" << endl;
        }
    }
    return 0;
}

/************************************************************ FONCTIONS */

void identifierCapteurDefaillant()
{
    cout << " # IDENTIFICATION D'UN CAPTEUR DEFAILLANT #" << endl;
    
}

void observerImpactAirCleaner()
{
    int rayon, latitude, longitude, id, choix;
    AirCleaner* aircleaner = new AirCleaner(); 
    TraitementMesure* mesureManager = new TraitementMesure();
    GestionMateriel* matosManager = new GestionMateriel(); 
    
    cout << " # OBSERVATION IMPACT AIR CLEANER #" << endl;

    cout << " 1 - ID de l'AirCleaner connu" << endl;
    cout << " 2 - Localisation connue" << endl;
    cout << " Comment voulez-vou sidentifier l'AirCleaner ? (Entrer 1 ou 2) : ";
    cin >> choix;
    cout << endl;

    

    if(choix == 1)
    {
        cout << " ID AirCleaner : ";
        cin >> id;
        cout << " Rayon : ";
        cin >> rayon;
        //mesureManager.CourbeAirCleaner(matosManager.SearchACById(id), rayon);
        // /!\ Créer la méthode SearchById
    }
    else if(choix == 2)
    {
        cout << " Latitude : ";
        cin >> latitude;
        cout << " Longitude : ";
        cin >> longitude;
        cout << " Rayon : ";
        cin >> rayon;
        //mesureManager.CourbeAirCleaner(matosManager.SearchIdACByLL(latitude,, longitude), rayon);
    }
    else
    {
        cout << " >> Choix invalide, retour au menu principal" << endl;
    }

    delete(aircleaner);
    delete(mesureManager);
    delete(matosManager);

    
    
}