/*************************************************************************
                           TypeMesure  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TypeMesure> (fichier TypeMesure.h) ----------------
#if ! defined ( TYPEMESURE_H )
#define TYPEMESURE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TypeMesure>
//
//
//------------------------------------------------------------------------

class TypeMesure 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
TypeMesure();
TypeMesure(int, string, string);

TypeMesure ( const TypeMesure & unTypeMesure );

//----------------------------------------------------- Destructeur
~TypeMesure();

//----------------------------------------------------- Méthodes publiques
string GetUnit();

string GetDescription();

int GetAttributeId();

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int attributeId;
    string unit;
    string description;
};

//-------------------------------- Autres définitions dépendantes de <TypeMesure>

#endif // TypeMesure_H

