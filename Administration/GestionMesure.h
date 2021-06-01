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

//----------------------------------------------------- Destructeur
~GestionMesure();

//----------------------------------------------------- Méthodes publiques

vector<Mesure*> ObtenirDonneCapteurActuelle(int sensorId);
vector<Mesure*> ObtenirDonneCapteurJour(int sensorId, Date * date);
vector<vector<Mesure*>> ObtenirDonneCapteurPeriode(int sensorId, Date * start, Date* stop);

void MiseEnMemoireMesures();

vector<vector<Mesure*>> GetMesuresSensor(int sensorId);



//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<vector<vector<Mesure*>>> mesures;
    /*
        Organisation de mesures :
        Un vector pour chaque capteur
        Chaque vector de capteur contient des vectors de 4 mesures qui correspondent
        au 4 mesure d'une journée. 
    */
};

//-------------------------------- Autres définitions dépendantes de <GestionMesure>

#endif // GestionMesure_H

