/*************************************************************************
                           GestionMesure  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <GestionMesure> (fichier GestionMesure.h) ----------------
#if ! defined ( GESTIONMESURE_H )
#define GESTIONMESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include "../Materiel/Mesure.h"
#include <vector>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GestionMesure>
//
//
//------------------------------------------------------------------------

class GestionMesure 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
GestionMesure();

GestionMesure ( const GestionMesure & unGestionMesure );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

//----------------------------------------------------- Destructeur
~GestionMesure();

//----------------------------------------------------- Méthodes publiques
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
Mesure* ObtenirDonneCapteurActuelle(int sensorId);

void MiseEnMemoireMesures();

vector<Mesure*> GetMesures(int sensorId);


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<vector<Mesure*>> mesures;
};

//-------------------------------- Autres définitions dépendantes de <GestionMesure>

#endif // GestionMesure_H

