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
// type TraitementCapteur::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode




double * TraitementCapteur::identifierCapteurDefaillant(Capteur * capteur, int rayon)
{
    if(capteur != nullptr && rayon > 1)
    {
        if(DEBUG) cout << "++ Methode identifierCapteurDefaillant"<<endl;
        int o3CapteurDef = 0;
        int so2CapteurDef = 0;
        int no2CapteurDef = 0;
        int pm10CapteurDef = 0;
        int o3Autre = 0;
        int so2Autre = 0;
        int no2Autre = 0;
        int pm10Autre = 0;
        int nbMesure = 0;
        
        GestionMesure * objetGestionMesure = new GestionMesure();
        GestionMateriel * objetGestionMateriel = new GestionMateriel();
        
        
        vector<Mesure*> mesuresAVerifier(objetGestionMesure->ObtenirDonneCapteurActuelle(capteur->GetSensorId()));
        o3CapteurDef = mesuresAVerifier[0]->GetValue();
        so2CapteurDef = mesuresAVerifier[1]->GetValue();
        no2CapteurDef = mesuresAVerifier[2]->GetValue();
        pm10CapteurDef = mesuresAVerifier[3]->GetValue();

        if(DEBUG) cout << "++ Debut boucle"<<endl;

        vector <int> capteurDansLaZone (objetGestionMateriel->ObtenirIdCapteurZone(capteur->GetLatitude(),capteur->GetLongitude(),rayon));
        for (unsigned int i = 0; i < capteurDansLaZone.size(); i++)
        {
            vector <Mesure*> mesures (objetGestionMesure->ObtenirDonneCapteurActuelle(capteurDansLaZone[i]));
            nbMesure++;
            for(vector<Mesure*>::iterator mesuresIter = mesures.begin(); mesuresIter != mesures.end(); mesuresIter++)
            //for(int j = 0; j<4; j++)
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

        double o3 = (o3Autre)/nbMesure;//-o3CapteurDef
        double so2 = (so2Autre)/nbMesure;//-so2CapteurDef
        double no2 = (no2Autre)/nbMesure;//-no2CapteurDef
        double pm10 = (pm10Autre)/nbMesure;//-pm10CapteurDef
        double * ecartType = new double[4];
        ecartType[0] = abs(o3-o3CapteurDef)/o3;
        ecartType[1] = abs(so2-so2CapteurDef)/so2;
        ecartType[2] = abs(no2-no2CapteurDef)/no2;
        ecartType[3] = abs(pm10-pm10CapteurDef)/pm10;

        //Affichage de la défaillance du capteur
        if(DEBUG) cout << "++ Affichage"<<endl;
        double seuil = 0.3;
        bool defaillance = false;
        for(int i = 0; i<4; i++)
        {
            if(ecartType[i] > seuil){defaillance = true;}
        }
        if(defaillance){
            cout << " >> Le capteur " << capteur->GetSensorId() << " est défaillant" << endl;
        }
        else{
            if(DEBUG) cout << " >> Le capteur " << capteur->GetSensorId() << " n'est pas défaillant" << endl;
        }

        if(DEBUG) cout << "++ Sortie de méthode"<<endl;

        return ecartType;
    }
    else
    {
        cout << " >> Rayon trop petit ou capteur invalide"<<endl;
        return 0;

    }
}//------ Fin de Méthode

//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
    