/*************************************************************************
                           TraitementCapteur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TraitementCapteur> (fichier TraitementCapteur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
#include "TraitementCapteur.h"
#include "../Materiel/AirCleaner.h"
#include "../Materiel/Capteur.h"
#include "../Materiel/Mesure.h"
#include "../Administration/GestionMesure.h"
#include "../Administration/GestionMateriel.h"
using namespace std;


//------------------------------------------------------ Include personnel

//----------------------------------------------------------------- Macros

//------------------------------------------------------------- Constantes
#define DEBUG false
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

TraitementCapteur::TraitementCapteur()
{

}

TraitementCapteur::~TraitementCapteur()
{

}

bool TraitementCapteur::identifierCapteurDefaillant(Capteur * capteur, int rayon, GestionMesure* gestionMesure, GestionMateriel* gestionMateriel)
/*
    On définie un capteur comme défaillant lorsque ses mesures s'écartent trop des
    mesures des capteurs à proximité.
    Cette méthode calcul donc, pour chaque substance mesuré par le capteur, un ecart-type
    entre la mesure du capteur et celle des autres capteurs présent dans le rayon passé en paramètre.
    Si cet écart type dépasse un seuil, le capteur est compté comme défaillant
*/
{
    //Vérification des paramètres
    if(capteur != nullptr && rayon > 1)
    {
        if(DEBUG) cout << "++ Methode identifierCapteurDefaillant"<<endl;

        //initialisation des variables de mesures avant de les récupérer dans les fichiers .csv
        double o3CapteurDef = 0;
        double so2CapteurDef = 0;
        double no2CapteurDef = 0;
        double pm10CapteurDef = 0;
        double o3Autre = 0;
        double so2Autre = 0;
        double no2Autre = 0;
        double pm10Autre = 0;
        double nbMesure = 0;        
        
        //récupération des mesures du capteurs à tester
        vector<Mesure*> mesuresAVerifier(gestionMesure->ObtenirDonneCapteurActuelle(capteur->GetSensorId()));
        o3CapteurDef = mesuresAVerifier[0]->GetValue();
        so2CapteurDef = mesuresAVerifier[1]->GetValue();
        no2CapteurDef = mesuresAVerifier[2]->GetValue();
        pm10CapteurDef = mesuresAVerifier[3]->GetValue();

        if(DEBUG) cout << "++ Debut boucle"<<endl;

        //récupération de tous les capteurs dans la zone définie par les coordonée du capteur à tester et délimitée par le rayon en paramètre
        vector <int> capteurDansLaZone (gestionMateriel->ObtenirIdCapteurZone(capteur->GetLatitude(),capteur->GetLongitude(),rayon));
        for (unsigned int i = 0; i < capteurDansLaZone.size(); i++)
        {
            //récupération des mesures des capteurs dans cette zone
            vector <Mesure*> mesures (gestionMesure->ObtenirDonneCapteurActuelle(capteurDansLaZone[i]));
            nbMesure++;
            for(vector<Mesure*>::iterator mesuresIter = mesures.begin(); mesuresIter != mesures.end(); mesuresIter++)
            {
                if((*mesuresIter)->GetTypeMesureId().compare("O3") == 0){
                    o3Autre = o3Autre + (*mesuresIter)->GetValue();
                }else if((*mesuresIter)->GetTypeMesureId().compare("SO2") == 0){
                    so2Autre = so2Autre + (*mesuresIter)->GetValue();
                }else if((*mesuresIter)->GetTypeMesureId().compare("NO2") == 0){
                    no2Autre = no2Autre + (*mesuresIter)->GetValue();
                }else if((*mesuresIter)->GetTypeMesureId().compare("PM10") == 0){
                    pm10Autre = pm10Autre + (*mesuresIter)->GetValue();
                }
            }
        }
        if(DEBUG) cout << "++ Fin boucle"<<endl;

        //calcul des moyennes des mesures dans la zone en écartant la mesure du capteur à comparer
        //et de l'ecart-type pour chaque substance du capteur à tester
        double o3 = (o3Autre - o3CapteurDef)/(nbMesure-1);
        double so2 = (so2Autre - so2CapteurDef)/(nbMesure-1);
        double no2 = (no2Autre - no2CapteurDef)/(nbMesure-1);
        double pm10 = (pm10Autre - pm10CapteurDef)/(nbMesure-1);
        double * ecartType = new double[4];
        ecartType[0] = abs(o3-o3CapteurDef)/o3;
        ecartType[1] = abs(so2-so2CapteurDef)/so2;
        ecartType[2] = abs(no2-no2CapteurDef)/no2;
        ecartType[3] = abs(pm10-pm10CapteurDef)/pm10;

        //Affichage de la défaillance du capteur en fonction d'un seuil choisi
        if(DEBUG) cout << "++ Affichage"<<endl;
        //Choix du seuil arbitraire
        double seuil = 1;
        bool defaillance = false;
        for(int i = 0; i<4; i++)
        {
            if(ecartType[i] > seuil){defaillance = true;}
        }
        
        if(defaillance){
            cout << " !! Le capteur " << capteur->GetSensorId() << " est défaillant" << endl;
        }

        if(DEBUG) cout << "++ Sortie de méthode"<<endl;

        delete [] ecartType;
    
        return defaillance;
    }
    else
    {
        cout << " >> Rayon trop petit ou capteur invalide"<<endl;
    }

    
    
    return 0;
}

//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
    