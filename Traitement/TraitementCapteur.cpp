/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Ensemble> (fichier Ensemble.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
#include "TraitementCapteur.h"
using namespace std;


//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Ensemble::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode




double * TraitementCapteur::identifierCapteurDefaillant(Capteur capteur, int rayon)
{
    int o3CapteurDef = 0;
    int so2CapteurDef = 0;
    int no2CapteurDef = 0;
    int pm10CapteurDef = 0;
    int o3Autre = 0;
    int so2Autre = 0;
    int no2Autre = 0;
    int pm10Autre = 0;
    int nbMesure = 0;

    GestionMesure objetGestionMesure;
    GestionMateriel objetGestionMateriel;

    vector <Mesure> mesuresAVerifier (objetGestionMesure.obtenirDonneCapteurActuelle(capteur.GetSensorId()));

    mesuresAVerifier.push_back(o3CapteurDef);
    mesuresAVerifier.push_back(so2CapteurDef);
    mesuresAVerifier.push_back(no2CapteurDef);
    mesuresAVerifier.push_back(pm10CapteurDef);

    vector <int> capteurDansLaZone (objetGestionMateriel.obtenirIdCapteurZone(capteur.GetLatitude(),capteur.GetLongitude(),rayon));
    for (vector<int>::iterator i; i != capteurDansLaZone.end(); i++)
    {
        vector <Mesure> mesures (objetGestionMesure.obtenirDonneCapteurActuelle(capteurDansLaZone[i]));
        nbMesure++;
        for(vector<Mesure>::iterator j; j != mesures.end; j++)
        {
            if(j->GetTypeMesureId() == "O3")
            {
                o3Autre = o3Autre + j->GetValue();
            }
            else if(j->GetTypeMesureId() == "SO2")
            {
                so2Autre = so2Autre + j->GetValue();
            }
            else if(j->GetTypeMesureId() == "SO2")
            {
                no2Autre = no2Autre + j->GetValue();
            }
            else if(j->GetTypeMesureId() == "SO2")
            {
                pm10Autre = pm10Autre + j->GetValue();
            }
        }
    }

    double o3 = (o3Autre-o3CapteurDef)/nbMesure;
    double so2 = (so2Autre-so2CapteurDef)/nbMesure;
    double no2 = (no2Autre-no2CapteurDef)/nbMesure;
    double pm10 = (pm10Autre-pm10CapteurDef)/nbMesure;
    double ecartType [4];
    ecartType[0] = abs(o3-o3CapteurDef)/o3;
    ecartType[1] = abs(so2-so2CapteurDef)/so2;
    ecartType[2] = abs(no2-no2CapteurDef)/no2;
    ecartType[3] = abs(pm10-pm10CapteurDef)/pm10;

    return ecartType;
}//------ Fin de Méthode



//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
    