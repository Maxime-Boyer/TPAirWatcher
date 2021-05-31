/*************************************************************************
                           Capteur  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Capteur> (fichier Capteur.h) ----------------
#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Capteur>
//
//
//------------------------------------------------------------------------

class Capteur 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
Capteur();
Capteur(int, double, double);

Capteur ( const Capteur & unCapteur );

//----------------------------------------------------- Destructeur
~Capteur();

//----------------------------------------------------- Méthodes publiques
int GetSensorId();

double GetLatitude();

double GetLongitude();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int sensorId;
    double latitude;
    double longitude;
};

//-------------------------------- Autres définitions dépendantes de <Capteur>

#endif // Capteur_H

