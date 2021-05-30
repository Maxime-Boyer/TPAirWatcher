/*************************************************************************
                           AirCleaner  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <AirCleaner> (fichier AirCleaner.h) ----------------
#if ! defined ( AIRCLEANER_H )
#define AIRCLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>
#include "Date.h"
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AirCleaner>
//
//
//------------------------------------------------------------------------

class AirCleaner 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
AirCleaner();
AirCleaner(int,double,double,Date *);

AirCleaner( const AirCleaner & unAirCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

//----------------------------------------------------- Destructeur
~AirCleaner();

//----------------------------------------------------- Méthodes publiques
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
int GetIdCleaner();
double GetLatitude();
double GetLongitude();
Date * GetDateInstallation();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int idCleaner;
    Date * dateInstallation;
    double latitude;
    double longitude;
};

//-------------------------------- Autres définitions dépendantes de <AirCleaner>

#endif // AirCleaner_H

