/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Ensemble> (fichier Ensemble.h) ----------------
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
// Rôle de la classe <Ensemble>
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
    int[][] CourbeAirCleaner(AirCleaner cleaner, int rayon);
    int CalculQualiteAirZone(int Latitude, int Longitude, int rayon, time_t date);
//------------------------------------------------------------------ PRIVE

    int *tabIndiceAtmoO3;
    int *tabIndiceAtmoNo2;
    int *tabIndiceAtmoSo2;
    int *tabIndiceAtmoPm10;

      
protected:
//----------------------------------------------------- Méthodes protégées
        
        
//----------------------------------------------------- Attributs protégés
};

//-------------------------------- Autres définitions dépendantes de <Ensemble>

#endif // TRAITEMENTMESURE_H

