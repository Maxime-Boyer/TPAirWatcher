/*************************************************************************
                           Date  -  description
                             -------------------
    début                : 20.10.2020
    copyright            : (C) 2020 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Date> (fichier Date.h) ----------------
#if ! defined ( DATE_H )
#define DATE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Date>
//
//
//------------------------------------------------------------------------

class Date 
{
//----------------------------------------------------------------- PUBLIC

public:

//------------------------------------------------- Surcharge d'opérateurs
    
//----------------------------------------------------- Constructeurs
Date();
Date(string);

Date ( const Date & unDate );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

//----------------------------------------------------- Destructeur
~Date();

//----------------------------------------------------- Méthodes publiques
 // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
int GetDay();
int GetMonth();
int GetYear();
int GetHour();
int GetMinutes();
int GetSeconds();

int operator-(int nbDays);
int soustraireDate(Date * date);
int operator+(int nbDays);
int nombreJoursParMois(int mois);

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int day;
    int month;
    int year;
    int hour;
    int minutes;
    int seconds;
};

//-------------------------------- Autres définitions dépendantes de <Date>

#endif // Date_H

