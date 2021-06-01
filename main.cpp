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
void observerQualiteAir(GestionMateriel* ,GestionMesure*);

/*********************************************************** CONSTANTES */
#define DEBUG false

/***************************************************************** MAIN */

int saisieInteger(){
    string line;
    int choix;

    try{
        cin >> line;
        choix = stoi(line);
        return choix;
    }
    catch(invalid_argument& e){
        cout << "Veuillez entrer un nombre" << endl << endl;
        return -1;
    }
}

double saisieDouble(){
    string line;
    double choix;

    try{
        cin >> line;
        choix = stof(line);
        return choix;
    }
    catch(invalid_argument& e){
        cout << "Veuillez entrer un nombre" << endl << endl;
        return 1000;
    }
}
int main(int argc, char* argv[]){
    string line;
    int choix; 
    bool running = true;

    //instanciation des objets donnant accès aux différentes méthodes necessaires
    GestionMateriel* matosManager = new GestionMateriel();
    GestionMesure* mesureManager = new GestionMesure();

    while(running)
    {
        cout << " #####  BIENVENUE DANS AIR_WATCHER #####" << endl;

        cout << " 1 - Identifier le(s) capteur(s) défaillant(s)" << endl;
        cout << " 2 - Observer l'impact d'un AirCleaner" << endl;
        cout << " 3 - Calcul de la qualité de l'air autour d'une zone" << endl;
        cout << " 4 - Quitter air watcher" << endl;
        cout << " Que voulez-vous faire ? (Entrer 1, 2, 3, 4) : ";
        
        choix = saisieInteger();
        if(choix != -1){
            cout << endl;
            
            switch(choix){
                case 1:
                    identifierCapteurDefaillant(matosManager,mesureManager);
                break;
                case 2 :
                    observerImpactAirCleaner(matosManager,mesureManager);
                break;
                case 3 :
                    observerQualiteAir(matosManager,mesureManager);
                break;
                case 4 :
                    cout << " #####  AU REVOIR ! #####" << endl;
                    running = false;
                break;
                default : 
                    cout << "Veuillez rentrer un chiffre entre 1 et 3" << endl << endl;
                break;
            }
           
        }
    }

    delete matosManager;
    delete mesureManager;

    return 0;
}
/************************************************************ FONCTIONS */

void observerQualiteAir(GestionMateriel* matosManager, GestionMesure* mesureManager){
    cout << " # OBSERVATION QUALITE DE L'AIR ZONE #" << endl;
    
    cout << "Entrez la latitude : " ;
    double latitude = saisieDouble();
    cout << endl; 
    if(latitude == 1000) return;

    cout << "Entrez la longitude : ";
    double longitude = saisieDouble();
    cout << endl;
    if(longitude == 1000) return;

    cout << "Entrez le rayon : ";
    int rayon = saisieDouble();
    cout << endl;
    if(rayon == -1) return;

    cout << "Entrez la date (YYYY-MM-DD) " << endl;
    string date;
    cin >> date;
    date += " 12:00:00";

    TraitementMesure * traitementMesure = new TraitementMesure();
    Date * dateActuelle = new Date(date); 

    vector<int> v;
    int indice = traitementMesure->CalculQualiteAirZone(latitude,longitude,rayon,dateActuelle,mesureManager,matosManager,v);
    cout << "L'indice de l'air dans cette zone vaut : " << indice << endl << endl;

    delete dateActuelle;
    delete traitementMesure;
}
void identifierCapteurDefaillant(GestionMateriel* matosManager, GestionMesure * mesureManager)
{
    int idCapteur;
    int choix;
    int rayon;
    TraitementCapteur* capteurTraitement = nullptr;
    

    cout << " # IDENTIFICATION D'UN CAPTEUR DEFAILLANT #" << endl;

    cout << " 1 - Analyse d'un seul capteur" << endl;
    cout << " 2 - Analyse de l'ensemble des capteurs" << endl;
    cout << " Quel type d'analyse voulez-vous lancer ? (Entrer 1 ou 2) : ";
    choix = saisieInteger();
    if(choix == -1){
        return;
    }
    cout << endl;

    if(choix == 1)
    {
        cout << " ID capteur : ";
        idCapteur = saisieInteger(); 
        if(idCapteur == -1) return;

        cout << " Rayon de comparaison : ";
        rayon = saisieInteger();
        if(rayon == -1) return;

        capteurTraitement = new TraitementCapteur();
        //On s'assure que le capteur demandé existe
        if(matosManager->GetCapteur(idCapteur) != nullptr)
        {
            if(capteurTraitement->identifierCapteurDefaillant(matosManager->GetCapteur(idCapteur), rayon,mesureManager,matosManager))
            {
                cout << " >> Capteur " << idCapteur << " défaillant"<<endl;
            }
            else
            {
                cout << " >> Capteur " << idCapteur << " fonctionnel"<<endl;
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
        rayon = saisieInteger();
        if(rayon == -1) return;

        capteurTraitement = new TraitementCapteur();

        //On va parcourir la liste de tous les capteurs et tester leur défaillance un par un
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
    TraitementMesure* mesureTraitement = nullptr;
    
    cout << " # OBSERVATION IMPACT AIR CLEANER #" << endl;

    cout << " ID AirCleaner : ";
    id = saisieInteger();
    if(id == -1) return;

    cout << " Rayon : ";
    rayon = saisieInteger();
    if(rayon == -1) return;

    mesureTraitement = new TraitementMesure();
    //On s'assure que le capteur demandé existe
    if(matosManager->GetAirCleaner(id) != nullptr)
    {
        //On affiche la courbe de l'évolution de la qualité de l'air dans un rayon autour d'un capteur
        mesureTraitement->CourbeAirCleaner(matosManager->GetAirCleaner(id), rayon, mesureManager,  matosManager);
    }
    else
    {
        cout << " !! AirCleaner inexistant" << endl;
    }

    delete mesureTraitement;
    
}