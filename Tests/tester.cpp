/*************************************************************************
                           tester.cpp  -  description
                             -------------------
    début                : 04.05.2021
    copyright            : (C) 2021 par Julien BOUVIER
    e-mail               : julien.bouvier@insa-lyon.fr
*************************************************************************/


/************************************************************* INCLUDES */

#include <iostream>
#include <ctime>
#include "../Traitement/TraitementMesure.h"

using namespace std;

/********************************************************* DECLARATIONS */

bool tCalculQualiteAirZoneValide(time_t date);
bool tCalculQualiteAirZoneNonCouverte(time_t date);
bool tCalculQualiteAirZoneInvalide(time_t date);
bool tImpactAirCleaner();


/*********************************************************** CONSTANTES */


/***************************************************************** MAIN */

int main(int argc, char* argv[])
{
    int nbTests = 0;
    int nbPasse = 0;
    int nbEchoue = 0;

    cout << "##### LANCEMENT DES TESTS #####" << endl;

    // 
    struct tm* dateF;
    dateF->tm_year = 2020;
    dateF->tm_mon = 01;
    dateF->tm_mday = 01;
    dateF->tm_hour = 12;
    dateF->tm_min = 00;

    time_t date = mktime(dateF);

    cout << "# Calcul qualite de l'air dans un rayon" << endl;
    nbTests++;
    cout << "- Test "<<nbTests<<" : Zone couverte ->";
    if(tCalculQualiteAirZoneValide(date))
    {
        cout << "# passe" << endl;
        nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        nbEchoue++;
    }
    
    nbTests++;
    cout << "- Test "<<nbTests<<" : Zone non couverte" << endl;
    if(tCalculQualiteAirZoneNonCouverte(date))
    {
        cout << "# passe" << endl;
        nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        nbEchoue++;
    }

    nbTests++;
    cout << "- Test "<<nbTests<<" : Zone innexistante" << endl;
    if(tCalculQualiteAirZoneInvalide(date))
    {
        cout << "# passe" << endl;
        nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        nbEchoue++;
    }

    //
    cout << "# Calcul de l'impact d'un air cleaner" << endl;
    nbTests++;
    cout << "- Test "<<nbTests<<" : Air Cleaner existant ->";
    if(tImpactAirCleaner())
    {
        cout << "# passe" << endl;
        nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        nbEchoue++;
    }
    
    nbTests++;
    cout << "- Test "<<nbTests<<" : Air Cleaner inexistant" << endl;
    if(tImpactAirCleaner())
    {
        cout << "# passe" << endl;
        nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        nbEchoue++;
    }

    // RESUME DES TESTS
    cout << "##### FIN DES TESTS #####" << endl;
    cout << "Nombres de tests effectues : " << nbTests << endl;
    cout << "Nombres de tests reussis : " << nbPasse << endl;
    cout << "Nombres de tests echoues : " << nbEchoue << endl;

    return 0;
}


/********************************************************* DEFINITIONS */

bool tCalculQualiteAirZoneValide(time_t date)
{
    TraitementMesure traitement;

    /************* MODIFIER LES VALEURS POUR LES FAIRES CORRESPONDRE AVEC LES DATAS ***/
    if(traitement.CalculQualiteAirZone(50, 50, 10, date) == 22)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

bool tCalculQualiteAirZoneNonCouverte(time_t date)
{
    TraitementMesure traitement;
    /************* MODIFIER LES VALEURS POUR LES FAIRES CORRESPONDRE AVEC LES DATAS ***/
    if(traitement.CalculQualiteAirZone(90, 90, 10, date) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

bool tCalculQualiteAirInvalide(time_t date)
{
    TraitementMesure traitement;   
    /************* MODIFIER LES VALEURS POUR LES FAIRES CORRESPONDRE AVEC LES DATAS ***/
    if(traitement.CalculQualiteAirZone(200, 200, 10, date) == -1)
    {
        return true;
    }
    else
    {
        return false;
    }    
}

bool tImpactAirCleaner()
{
    return false;
}