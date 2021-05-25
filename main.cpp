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

using namespace std;

/********************************************************* DECLARATIONS */
void identifierCapteurDefaillant();
void observerImpactAirCleaner();

/*********************************************************** CONSTANTES */


/***************************************************************** MAIN */


int main(int argc, char* argv[]){
    int choix;

    cout << " #####  BIENVENUE DANS AIR_WATCHER #####" << endl;

    cout << " 1 - Identifier les capteur défaillant" << endl;
    cout << " 2 - Observer l'impact d'un AirCleaner" << endl;
    cout << " Que voulez-vous faire ? (Entrer 1 ou 2) : ";
    cin << choix << endl;

    if(choix == 1)
    {
        identifierCapteurDefaillant();
    }
    else
    {
        observerImpactAirCleaner();
    }
    return 0;
}

/************************************************************ FONCTIONS */

void identifierCapteurDefaillant()
{

}

void observerImpactAirCleaner()
{
    AirCleaner aircleaner; // Réussir à demander le air cleaner
    int rayon;

    cout << " Latitude : ";
    cin << latitude << endl;
    cout << " Longitude : ";
    cin << longitude << endl;
    cout << " Rayon : ";
    cin << rayon << endl;

    courbeAirCleaner(aircleaner, rayon);
}