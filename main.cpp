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
#include <vector>

#include "Materiel/AirCleaner.h"
#include "Materiel/Capteur.h"
#include "Traitement/TraitementMesure.h"
#include "Traitement/TraitementCapteur.h"
#include "Administration/GestionMateriel.h"

using namespace std;

/********************************************************* DECLARATIONS */
void identifierCapteurDefaillant(GestionMateriel*, GestionMesure*);
void observerImpactAirCleaner(GestionMateriel*, GestionMesure*);

/*********************************************************** CONSTANTES */


/***************************************************************** MAIN */


int main(int argc, char* argv[]){
    int choix;
    bool running = true;

    GestionMateriel* matosManager = new GestionMateriel();
    GestionMesure* mesureManager = new GestionMesure();

    while(running)
        {
        cout << " #####  BIENVENUE DANS AIR_WATCHER #####" << endl;

        cout << " 1 - Identifier les capteur défaillant" << endl;
        cout << " 2 - Observer l'impact d'un AirCleaner" << endl;
        cout << " autre - Quitter air watcher" << endl;
        cout << " Que voulez-vous faire ? (Entrer 1 ou 2) : ";
        cin >> choix;
        cout << endl;

    
        if(choix == 1)
        {
            identifierCapteurDefaillant(matosManager,mesureManager);
        }
        else if(choix == 2)
        {
            observerImpactAirCleaner(matosManager,mesureManager);
        }
        else if(choix > 2 || choix < 1)
        {
            cout << " #####  AU REVOIR ! #####" << endl;
            running = false;
        }
        else
        {
            cout << " >> Veuillez entrer un chiffre valide (1, 2 ou 3)" << endl;
            choix = 3;
        }
    }
    return 0;
}

/************************************************************ FONCTIONS */

void identifierCapteurDefaillant(GestionMateriel* matosManager, GestionMesure * mesureManager)
{
    int idCapteur;
    int choix;
    int rayon;
    TraitementCapteur* capteurTraitement = new TraitementCapteur();
    

    cout << " # IDENTIFICATION D'UN CAPTEUR DEFAILLANT #" << endl;

    cout << " 1 - Analyse d'un seul capteur" << endl;
    cout << " 2 - Analyse de l'ensemble des capteurs" << endl;
    cout << " QUel type d'analyse voulez-vous lancer ? (Entrer 1 ou 2) : ";
    cin >> choix;
    cout << endl;

    if(choix == 1)
    {
        cout << " ID capteur : ";
        cin >> idCapteur;
        cout << " Rayon de comparaison : ";
        cin >> rayon;
        capteurTraitement->identifierCapteurDefaillant(matosManager->GetCapteur(idCapteur), rayon);
    }
    else if(choix == 2)
    {
        cout << " Rayon de comparaison : ";
        cin >> rayon;
        vector<Capteur*> listeCapteurs(matosManager->GetCapteurs());
        for(vector<Capteur*>::iterator itr = listeCapteurs.begin(); itr!= listeCapteurs.end(); itr++)
        { 
            cout << "++ Incrémentation Capteur anaylé"<<endl;
            if(*itr != nullptr)
            {
                cout << "++ non nullptr capteur analysé; rayon : " << rayon << endl;
                capteurTraitement->identifierCapteurDefaillant(*itr, rayon);
            }
            else{
                cout << "++ nullptr capteur analysé" << endl;
            }
            
        }
    }
    else
    {
        cout << " >> Choix invalide, retour au menu principal" << endl;
    }

    
}

void observerImpactAirCleaner(GestionMateriel* matosManager, GestionMesure* mesureManager)
{
    int rayon;
    int latitude;
    int longitude;
    int id;
    int choix;
    AirCleaner* aircleaner = new AirCleaner(); 
    TraitementMesure* mesureTraitement = new TraitementMesure();
    
    cout << " # OBSERVATION IMPACT AIR CLEANER #" << endl;

    cout << " 1 - ID de l'AirCleaner connu" << endl;
    cout << " 2 - Localisation connue" << endl;
    cout << " Comment voulez-vous identifier l'AirCleaner ? (Entrer 1 ou 2) : ";
    cin >> choix;
    cout << endl;

    

    if(choix == 1)
    {
        cout << " ID AirCleaner : ";
        cin >> id;
        cout << " Rayon : ";
        cin >> rayon;
        if(matosManager->GetAirCleaner(id) != nullptr)
        {
            mesureTraitement->CourbeAirCleaner(matosManager->GetAirCleaner(id), rayon, mesureManager,  matosManager);
        }
        else
        {
            cout << " !! AirCleaner inexistant" << endl;
        }
        
    }
    else if(choix == 2)
    {
        cout << " Latitude : ";
        cin >> latitude;
        cout << " Longitude : ";
        cin >> longitude;
        cout << " Rayon : ";
        cin >> rayon;
        mesureTraitement->CourbeAirCleaner((matosManager->GetAirCleaner(latitude, longitude)), rayon, mesureManager,  matosManager);
    }
    else
    {
        cout << " >> Choix invalide, retour au menu principal" << endl;
    }

    delete(aircleaner);
    delete(mesureManager);
    delete(matosManager); 
    
}