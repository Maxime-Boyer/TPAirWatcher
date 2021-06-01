/*************************************************************************
                           TraitementMesure  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TraitementMesure> (fichier TraitementMesure.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <stdlib.h>
#include "TraitementMesure.h"
#include "../Materiel/Date.h"
#include "../Materiel/Mesure.h"
#include "../Administration/GestionMateriel.h"
#include "../Administration/GestionMesure.h"
#include <vector>
#include <ctime>
#include <cstring>
#include <algorithm>
using namespace std;

//On remplit les tableaux d'indice à partir des valeurs du site 
//https://fr.wikipedia.org/wiki/Indice_de_qualit%C3%A9_de_l%27air#:
//~:text=Il%20existe%20principalement%20deux%20indices,l%27indice%20ATMO&text=pour%20les
//%20agglom%C3%A9rations%20de%20taille,nombre%20plus%20r%C3%A9duit%20de%20polluants.
const int tabIndiceAtmoO3[] = {29, 54, 79, 104, 149, 179, 209, 239, 30};
const int tabIndiceAtmoNo2[] = {29,54,84,109,134,164,199,274,399};
const int tabIndiceAtmoSo2[] = {39,79,119,159,199,249,299,399,499};
const int tabIndiceAtmoPm10[] = {6,13,27,34,41,49,64,79};
//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes
#define DEBUG false
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

TraitementMesure::TraitementMesure(){

}

TraitementMesure::~TraitementMesure(){

}

bool TraitementMesure::CourbeAirCleaner(AirCleaner * cleaner, int rayon, GestionMesure * objetGestionMesure,  GestionMateriel * objetGestionMateriel)
/*
    Affichage d'une courbe montrant l'impact d'un air cleaner sur la qualité de l'air dans une zone.
    Pour calculer l’impact d’un air cleaner : on calcule la qualité de l’air avant son installation 
    et on la compare avec la qualité de l’air actuelle.
*/
{
    if(rayon > 0 && cleaner != nullptr && objetGestionMesure != nullptr && objetGestionMateriel != nullptr){


        vector<int> capteurDansLaZone = objetGestionMateriel->ObtenirIdCapteurZone(cleaner->GetLatitude(),cleaner->GetLongitude(),rayon);
    
        Date * dateDebutCourbe = new Date(cleaner->GetDateInstallation());
        dateDebutCourbe->operator-(7);

        Date * dateBeginGraph = new Date(dateDebutCourbe);
        
        if(DEBUG) cout << "++ Declaration des dates de début OK" << endl;
        /*
        Dans le cas où les datasets sont à jour nous pouvons utiliser les lignes ci dessous.
        Or dans le cas de ce TP, nous sommes bloqués au 31 décembre 2019.
        
        time_t actuel = time(0);
        tm *ltm = localtime(&actuel);
        Date * dateActuelle = new Date(1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        
        */

        Date * dateActuelle = new Date(2019, 12, 31, 12, 00, 00); // Dernière date du fichier soit 31/12/2019 à midi
        Date * dateFinCourbe = nullptr;
        if(DEBUG) cout << "++ Initialisation des dates de fin OK" << endl;
        
        //Si le cleaner est désinstallé la courbe s'arrête 7 jour après sa désinstallation
        if(cleaner->GetDateDesinstallation() != nullptr){
            dateFinCourbe = new Date(cleaner->GetDateDesinstallation());
            dateFinCourbe->operator+(7);
        }
        //Si le cleaner n'est pas désinstallé la courbe s'arrête à la date de la dernière mesure
        else{
            dateFinCourbe = new Date(dateActuelle);
            
        }


        //Initialisation des variables de la courbe
        if(DEBUG) cout << "++ Récupération date de fin OK" << endl;
        int nbDays = dateDebutCourbe->Number_days_between(dateFinCourbe);
        
        int indice = 0;
        int indiceMax = 10;
        //Pour chaque jour on stock son indice
        int ** courbe = new int*[nbDays];

        if(DEBUG) cout << "++ Initialisation des variables 1 OK" << endl;
        for (int i = 0; i < nbDays; i++)
        {
            courbe[i] = new int[indiceMax]{0};
        }

        if(DEBUG) cout << "++ Declaration de la courbe OK" << endl;
        Date * currentDay = new Date(dateBeginGraph);

        //Calcul de la qualité de l'air dans la zone choisie autour du air cleaner pour chaque jour de la courbe
        for(int i = 0; i < nbDays; i++)
        {
            currentDay->operator+(1);
            indice = this->CalculQualiteAirZone(cleaner->GetLatitude(),cleaner->GetLongitude(),rayon,currentDay, objetGestionMesure, objetGestionMateriel,capteurDansLaZone);
            courbe[i][indice-1] = 1;
        }
        if(DEBUG) cout << "++ Remplissage de la courbe OK" << endl;

        //Affichage de la courbe
        //Pas d'algo particulier juste de l'affichage 
        cout << " # Qualité moyenne de l'air de la zone sur le temps de fonctionnement du cleaner" << endl;
        cout << "  ^" << endl;
        cout << "  |" << endl;
        for(int i = 0; i < indiceMax; i++){
            if(indiceMax-i != 10) cout << " ";
            cout << indiceMax-i << "|";
            for(int j = 0; j < nbDays; j++){
                if(courbe[j][indiceMax-i-1] == 1){
                    cout << "*";
                }
                else{
                    cout <<" " ; 
                }
            }
            cout << endl;
        }
  
        cout << " ";
        for(int i = 0; i < nbDays+1;i++){
            cout << "-";
        }
        cout << ">"<<endl;
        cout << endl;


        delete dateDebutCourbe;
        delete dateActuelle;
        delete dateBeginGraph;
        delete dateFinCourbe;
        delete currentDay;
        for (int i = 0; i < nbDays; i++)
        {
            delete[] courbe[i];
        }
        delete[] courbe;
        return true;
    }
    else
    {
        cout << "Paramètres invalides dans la méthode CourbeAirCleaner" << endl;
        return false;
    }

}


int CalculIndice(int moyenneParticule,int max, const int* tabIndice){
/*
    Fonction qui permet de calculer l'indice d'une particule à partir de sa mesure
    -> optimisée pour faire rapidement des tests sur plusieurs intervalles
*/

    if(moyenneParticule >= max){
        return 10;
    }
    else{
        for(int i = 0; i < 9; i++){
            if(moyenneParticule <= tabIndice[i]){
                return i+1;
            }
        }
    }

    return -1;
}

int TraitementMesure::CalculQualiteAirZone(double latitude, double longitude, int rayon, Date * date, GestionMesure * objetGestionMesure,  GestionMateriel * objetGestionMateriel, vector<int> capteurDansLaZone)
/*
    Calcul de la qualité de l'air pour une zone repérée par ses coordonnées et délimitée 
    par un rayon.
*/
{
    if(abs(latitude) < 90 && abs(longitude) < 180)
    {
        double o3 = 0;
        double so2 = 0;
        double no2 = 0;
        double pm10 = 0;
        double nbMesure = 0;
        double indiceO3 = 0;
        double indiceSo2 = 0;
        double indiceNo2 = 0;
        double indicePm10 = 0;

        if(DEBUG) cout << "++ Calcul Qualite Air Zone" << endl;

        //On recupère les capteurs dans la zone si ce n'est pas déjà fait
        if(capteurDansLaZone.size() == 0)
        capteurDansLaZone = objetGestionMateriel->ObtenirIdCapteurZone(latitude,longitude,rayon);
        
        if(capteurDansLaZone.size() > 0)
        {   
            if(DEBUG) cout << "++ Avant boucle for sur les capteurs"<< endl;
            for (unsigned int i = 0; i < capteurDansLaZone.size(); i++)
            {
                
                //Pour chaque capteur on récupère les mesures du jour choisi
                if(DEBUG) cout << "++   rentrer boucle for sur les capteurs" << endl;
                vector<Mesure*> mesures = objetGestionMesure->ObtenirDonneCapteurJour(capteurDansLaZone[i], date);
                if(DEBUG) cout << "++   creation vector<mesure*> mesures" << endl;
                nbMesure++;
                
                //On récupère les 4 valeurs qui constituent une mesure journalière
                for (vector<Mesure*>::iterator mesuresIter = mesures.begin(); mesuresIter != mesures.end(); mesuresIter++)
                {
                    if(DEBUG) cout << "++     rentrer for mesure comparaison" << endl;
                    if((*mesuresIter)->GetTypeMesureId().compare("O3") == 0){
                        o3 = o3 + (*mesuresIter)->GetValue();
                    }else if((*mesuresIter)->GetTypeMesureId().compare("SO2") == 0){
                        so2 = so2 + (*mesuresIter)->GetValue();
                    }else if((*mesuresIter)->GetTypeMesureId().compare("NO2") == 0){
                        no2 = no2 + (*mesuresIter)->GetValue();
                    }else if((*mesuresIter)->GetTypeMesureId().compare("PM10") == 0){
                        pm10 = pm10 + (*mesuresIter)->GetValue();
                    }
                }
            }

            //Calcul des moyennes
            o3 = o3/nbMesure;
            so2 = so2/nbMesure;
            no2 = no2/nbMesure;
            pm10 = pm10/nbMesure;

            //Calcul des indices
            indiceO3 = CalculIndice(o3,240,tabIndiceAtmoO3);
            indiceNo2 = CalculIndice(no2,400,tabIndiceAtmoNo2);
            indiceSo2 = CalculIndice(so2,500,tabIndiceAtmoSo2);
            indicePm10 = CalculIndice(pm10,80,tabIndiceAtmoPm10);

            return max(indiceO3,max(indiceNo2,max(indiceSo2,indicePm10)));
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -1;
    }
}
    
//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
    