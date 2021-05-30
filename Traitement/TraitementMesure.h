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
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    ////
    TraitementMesure();
    ~TraitementMesure();
    int** CourbeAirCleaner(AirCleaner cleaner, int rayon);
    int CalculQualiteAirZone(int Latitude, int Longitude, int rayon, Date * date);
//------------------------------------------------------------------ PRIVE

    int *tabIndiceAtmoO3;
    int *tabIndiceAtmoNo2;
    int *tabIndiceAtmoSo2;
    int *tabIndiceAtmoPm10;

      
protected:
//----------------------------------------------------- Méthodes protégées
        
        
//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <TraitementMesure>

#endif // TRAITEMENTMESURE_H

