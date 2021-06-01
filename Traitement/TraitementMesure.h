/*************************************************************************
                           TraitementMesure  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TraitementMesure> (fichier TraitementMesure.h) ----------------
#if ! defined ( TRAITEMENTMESURE_H )
#define TRAITEMENTMESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include "../Materiel/AirCleaner.h"
#include "../Materiel/Capteur.h"
#include "../Materiel/Mesure.h"
#include "../Administration/GestionMesure.h"
#include "../Administration/GestionMateriel.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TraitementMesure>
//
//
//------------------------------------------------------------------------

class TraitementMesure
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateur

//----------------------------------------------------- Constructeurs

//----------------------------------------------------- Destructeur

//----------------------------------------------------- Méthodes publiques
    TraitementMesure();
    ~TraitementMesure();
    void CourbeAirCleaner(AirCleaner * cleaner, int rayon, GestionMesure * objetGestionMesure,  GestionMateriel * objetGestionMateriel);
    int CalculQualiteAirZone(double latitude, double longitude, int rayon, Date * date, GestionMesure * objetGestionMesure,  GestionMateriel * objetGestionMateriel, vector<int>);
//------------------------------------------------------------------ PRIVE


      
protected:
//----------------------------------------------------- Méthodes protégées
        
        
//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <TraitementMesure>

#endif // TRAITEMENTMESURE_H

