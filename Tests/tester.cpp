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
#include "../Traitement/TraitementCapteur.h"
#include "../Administration/GestionMateriel.h"
#include "../Administration/GestionMesure.h"
#include "../Materiel/Date.h"

using namespace std;

/********************************************************* DECLARATIONS */

void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTest);
bool tCalculQualiteAirZoneValide(Date * date);
bool tCalculQualiteAirZoneNonCouverte(Date * date);
bool tCalculQualiteAirZoneInvalide(Date * date);
bool tImpactAirCleaner();
bool tCapteurDefaillant(Capteur * capteur, int rayon);
bool tCapteurNonDefaillant(Capteur  *capteur, int rayon);

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

    Date * date = new Date(2019, 03, 01, 12, 00, 00);
    GestionMateriel * objetGestionMateriel = new GestionMateriel;

    cout << "# Calcul qualite de l'air dans un rayon" << endl;
    test(tCalculQualiteAirZoneValide(date), "Zone couverte", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneNonCouverte(date), "Zone non couverte", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneInvalide(date), "Zone innexistante", nbPasse, nbEchoue, nbTests);
    test(tImpactAirCleaner(), "Air cleaner existant", nbPasse, nbEchoue, nbTests);
    test(tImpactAirCleaner(), "Air cleaner inexistant", nbPasse, nbEchoue, nbTests);
    test(tCapteurNonDefaillant(objetGestionMateriel->GetCapteur(10), 50), "Capteur fonctionnel",nbPasse, nbEchoue, nbTests);
    test(tCapteurDefaillant(objetGestionMateriel->GetCapteur(0), 50), "Capteur défaillant",nbPasse, nbEchoue, nbTests);



    // RESUME DES TESTS
    cout << "##### FIN DES TESTS #####" << endl;
    cout << "Nombres de tests effectues : " << *nbTests << endl;
    cout << "Nombres de tests reussis : " << *nbPasse << endl;
    cout << "Nombres de tests echoues : " << *nbEchoue << endl;

    return 0;
}


void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTests)
{
    (*nbTests)++;
    cout << "- Test " << *nbTests << " : " << description << " ->";
    if(retour)
    {
        cout << "# passe" << endl;
        (*nbPasse)++;
    }
    else
    {
        cout << "# echoue" << endl;
        (*nbEchoue)++;
    }
}

/********************************************************* DEFINITIONS */

bool tCalculQualiteAirZoneValide(Date * date)
{
    TraitementMesure* traitement = new TraitementMesure;
    GestionMesure* mesure = new GestionMesure;     
    GestionMateriel* materiel = new GestionMateriel;
    if(traitement->CalculQualiteAirZone(44, 0.4, 100, date, mesure, materiel) == 50)
    {
        return true;
    }
    return false;
}

bool tCalculQualiteAirZoneNonCouverte(Date * date)
{
    TraitementMesure* traitement = new TraitementMesure;
    GestionMesure* mesure = new GestionMesure;     
    GestionMateriel* materiel = new GestionMateriel;
    if(traitement->CalculQualiteAirZone(0.1, 0.1, 2, date, mesure, materiel) == 0)
    {
        return true;
    }
    return false;   
}

bool tCalculQualiteAirZoneInvalide(Date * date)
{
    TraitementMesure* traitement = new TraitementMesure;
    GestionMesure* mesure = new GestionMesure;     
    GestionMateriel* materiel = new GestionMateriel;  
    /************* MODIFIER LES VALEURS POUR LES FAIRES CORRESPONDRE AVEC LES DATAS ***/
    if(traitement->CalculQualiteAirZone(200, 200, 10, date, mesure, materiel) == -1)
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
    // Correspondance de rtour de la fonction
    return false;
}

bool tCapteurNonDefaillant(Capteur * capteur, int rayon)
{
    TraitementCapteur* traitement = new TraitementCapteur;
    if(*(traitement->identifierCapteurDefaillant(capteur, rayon)) < 2)
    {
        return true;
    }
    return false;
}

bool tCapteurDefaillant(Capteur * capteur, int rayon)
{
    TraitementCapteur* traitement = new TraitementCapteur;
    if(*(traitement->identifierCapteurDefaillant(capteur, rayon)) > 2)
    {
        return true;
    }
    return false;
}