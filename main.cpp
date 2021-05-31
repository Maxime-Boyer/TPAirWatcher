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
#include <stdexcept>
#include <string>


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
#define DEBUG false

/***************************************************************** MAIN */


int main(int argc, char* argv[]){
    string line;
    int choix; 
    bool running = true;

    GestionMateriel* matosManager = new GestionMateriel();
    GestionMesure* mesureManager = new GestionMesure();

    while(running)
    {
        cout << " #####  BIENVENUE DANS AIR_WATCHER #####" << endl;

        cout << " 1 - Identifier le(s) capteur(s) défaillant(s)" << endl;
        cout << " 2 - Observer l'impact d'un AirCleaner" << endl;
        cout << " 3 - Quitter air watcher" << endl;
        cout << " Que voulez-vous faire ? (Entrer 1, 2, 3) : ";
        
        cin >> line;
        try{
            choix = stoi(line);
            cout << endl;

            if(choix == 1)
            {
                identifierCapteurDefaillant(matosManager,mesureManager);
            }
            else if(choix == 2)
            {
                observerImpactAirCleaner(matosManager,mesureManager);
            }
            else if(choix == 3)
            {  
                
                cout << " #####  AU REVOIR ! #####" << endl;
                running = false;
            }
            else{
                cout << "Veuillez rentrer un chiffre entre 1 et 3" << endl << endl;
            }
        }
        catch(invalid_argument& e){
            cout << "Veuillez rentrer un chiffre entre 1 et 3" << endl << endl;
        }
    }

    delete matosManager;
    delete mesureManager;

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
        if(matosManager->GetCapteur(idCapteur) != nullptr)
        {
            if(capteurTraitement->identifierCapteurDefaillant(matosManager->GetCapteur(idCapteur), rayon,mesureManager,matosManager))
            {
                cout << " >> Capteur " << idCapteur << " fonctionnel"<<endl;
            }
            else
            {
                cout << " >> Capteur " << idCapteur << " défaillant"<<endl;
            }
        }
        else
        {
            if(DEBUG) cout << "++ nullptr capteur analysé" << endl;
        }
    }
    else if(choix == 2)
    {
        cout << " Rayon de comparaison : ";
        cin >> rayon;
    
        vector<Capteur*> listeCapteurs(matosManager->GetCapteurs());
        for(vector<Capteur*>::iterator itr = listeCapteurs.begin(); itr!= listeCapteurs.end(); itr++)
        { 
            if(DEBUG) cout << "++ Incrémentation Capteur anaylé"<<endl;
            capteurTraitement->identifierCapteurDefaillant(*itr, rayon,mesureManager,matosManager);
        }
        
    }
    else
    {
        cout << " >> Choix invalide, retour au menu principal" << endl;
    }
    cout << " # Fin de l'analyse" << endl;

    delete capteurTraitement;
    
}

void observerImpactAirCleaner(GestionMateriel* matosManager, GestionMesure* mesureManager)
{
    int rayon;
    int id;
    TraitementMesure* mesureTraitement = new TraitementMesure();
    
    cout << " # OBSERVATION IMPACT AIR CLEANER #" << endl;

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

    delete mesureTraitement;
    
}