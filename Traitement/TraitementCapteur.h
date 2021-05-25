/*************************************************************************
                           TraitementCapteur  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TraitementCapteur> (fichier TraitementCapteur.h) ----------------
#if ! defined ( TRAITEMENTCAPTEUR_H )
#define TRAITEMENTCAPTEUR_H

#include "../Materiel/AirCleaner.h"
#include "../Materiel/Capteur.h"
#include "../Materiel/Mesure.h"
#include "../Administration/GestionMesure.h"
#include "../Administration/GestionMateriel.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TraitementCapteur>
//
//
//------------------------------------------------------------------------

class TraitementCapteur 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
//----------------------------------------------------- Constructeurs

//----------------------------------------------------- Destructeur

//----------------------------------------------------- Méthodes publiques

double * identifierCapteurDefaillant(Capteur capteur, int rayon);
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};


#endif // TRAITEMENTCAPTEUR_H

