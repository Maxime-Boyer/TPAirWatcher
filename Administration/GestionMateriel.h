/*************************************************************************
                           GestionMateriel  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TGestionMateriel> (fichier GestionMateriel.h) ----------------
#if ! defined ( GESTIONMATERIEL_H )
#define GESTIONMATERIEL_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
using namespace std;

#include "../Materiel/Capteur.h"
#include "../Materiel/AirCleaner.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <GestionMateriel>
//
//
//------------------------------------------------------------------------

class GestionMateriel 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
GestionMateriel();

GestionMateriel ( const GestionMateriel & unGestionMateriel );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //


//----------------------------------------------------- Destructeur
~GestionMateriel();

//----------------------------------------------------- Méthodes publiques
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
vector<int> ObtenirIdCapteurZone(double lat, double lon, double rayon);

vector<Capteur*> GetCapteurs();
vector<AirCleaner*> GetCleaners();
AirCleaner* GetAirCleaner(double lat, double lon);
AirCleaner* GetAirCleaner(int id);


void MiseEnMemoireCapteur();
void MiseEnMemoireAirCleaner();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
vector<Capteur*> capteurs;
vector<AirCleaner*> cleaners;
//----------------------------------------------------- Attributs protégés
   
};

//-------------------------------- Autres définitions dépendantes de <GestionMateriel>

#endif // GestionMateriel_H

