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
#include <string>
#include "../Traitement/TraitementMesure.h"

using namespace std;

/********************************************************* DECLARATIONS */

void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTest);
bool tCalculQualiteAirZoneValide(time_t date);
bool tCalculQualiteAirZoneNonCouverte(time_t date);
bool tCalculQualiteAirZoneInvalide(time_t date);
bool tImpactAirCleaner();


/*********************************************************** CONSTANTES */


/***************************************************************** MAIN */

int main(int argc, char* argv[])
{
    int* nbTests;
    nbTests = (int*)malloc(sizeof(int));
    int* nbPasse;
    nbPasse = (int*)malloc(sizeof(int));
    int* nbEchoue;
    nbEchoue = (int*)malloc(sizeof(int));
    
    *nbTests = 0;
    *nbPasse = 0;
    *nbEchoue = 0;

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
    test(tCalculQualiteAirZoneValide(date), "Zone couverte", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneNonCouverte(date), "Zone non couverte", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneInvalide(date), "Zone innexistante", nbPasse, nbEchoue, nbTests);
    test(tImpactAirCleaner(), "Air cleaner existant", nbPasse, nbEchoue, nbTests);
    test(tImpactAirCleaner(), "Air cleaner inexistant", nbPasse, nbEchoue, nbTests);



    // RESUME DES TESTS
    cout << "##### FIN DES TESTS #####" << endl;
    cout << "Nombres de tests effectues : " << nbTests << endl;
    cout << "Nombres de tests reussis : " << nbPasse << endl;
    cout << "Nombres de tests echoues : " << nbEchoue << endl;

    return 0;
}


void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTests)
{
    *nbTests++;
    cout << "- Test " << *nbTests << " : " << description << " ->";
    if(retour)
    {
        cout << "# passe" << endl;
        *nbPasse++;
    }
    else
    {
        cout << "# echoue" << endl;
        *nbEchoue++;
    }
}

/********************************************************* DEFINITIONS */

bool tCalculQualiteAirZoneValide(time_t date)
{
    TraitementMesure traitement;

    /************* MODIFIER LES VALEURS POUR LES FAIRES CORRESPONDRE AVEC LES DATAS ***/
    if(traitement.CalculQualiteAirZone(44, 0.4, 100, date) == 50)
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
    if(traitement.CalculQualiteAirZone(0.1, 0.1, 2, date) == 0)
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