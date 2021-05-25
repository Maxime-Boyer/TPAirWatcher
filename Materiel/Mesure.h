/*************************************************************************
                           TypeMesure  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TypeMesure> (fichier Mesure.h) ----------------
#if ! defined ( MESURE_H )
#define MESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <ctime>
#include "Date.h"

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Mesure>
//
//
//------------------------------------------------------------------------

class Mesure 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
Mesure();
Mesure(int, string, double, Date *);

Mesure ( const Mesure & unMesure );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //


//----------------------------------------------------- Destructeur
~Mesure();

//----------------------------------------------------- Méthodes publiques
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
int GetSensorId();

string GetTypeMesureId();

double GetValue();

Date * GetDateMesure();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int sensorId;
    string typeMesureId;
    double value;
    Date * dateMesure;
};

//-------------------------------- Autres définitions dépendantes de <Mesure>

#endif // Mesure_H

