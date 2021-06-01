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
#include "Traitement/TraitementMesure.h"
#include "Traitement/TraitementCapteur.h"
#include "Administration/GestionMateriel.h"
#include "Administration/GestionMesure.h"
#include "Materiel/Date.h"
#include "Materiel/AirCleaner.h"

using namespace std;

/********************************************************* DECLARATIONS */

void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTest);
bool tCalculQualiteAirZoneValide(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCalculQualiteAirZoneNonCouverte(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCalculQualiteAirZoneInvalide(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCourbeAirCleanerCorrecte(AirCleaner* c, int rayon,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCourbeAirCleanerIncorrecte(AirCleaner* c, int rayon,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCapteurDefaillant(Capteur * capteur, int rayon,TraitementCapteur * traitement,GestionMesure* mesure, GestionMateriel* materiel);
bool tCapteurNonDefaillant(Capteur * capteur, int rayon,TraitementCapteur * traitement,GestionMesure* mesure, GestionMateriel* materiel);

/*********************************************************** CONSTANTES */

static bool testCourbe = true; 
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

   
    GestionMateriel * gestionMateriel = new GestionMateriel();
    GestionMesure * gestionMesure = new GestionMesure();
    TraitementMesure * traitementMesure = new TraitementMesure();
    TraitementCapteur* traitementCapteur = new TraitementCapteur();

    
    cout << "##### LANCEMENT DES TESTS #####" << endl;

    Date * date = new Date(2019, 03, 01, 12, 00, 00);
    

    test(tCalculQualiteAirZoneValide(date,traitementMesure,gestionMesure, gestionMateriel), "Calcul qualité de l'air dans une zone couverte    ", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneNonCouverte(date,traitementMesure,gestionMesure, gestionMateriel), "Calcul qualité de l'air dans une zone non couverte", nbPasse, nbEchoue, nbTests);
    test(tCalculQualiteAirZoneInvalide(date,traitementMesure,gestionMesure, gestionMateriel), "Calcul qualité de l'air dans une zone innexistante", nbPasse, nbEchoue, nbTests);
    test(tCapteurNonDefaillant(gestionMateriel->GetCapteur(10), 50,traitementCapteur,gestionMesure, gestionMateriel), "Analyse d'un capteur fonctionnel                  ",nbPasse, nbEchoue, nbTests);
    test(tCapteurDefaillant(gestionMateriel->GetCapteur(0), 50,traitementCapteur,gestionMesure, gestionMateriel), "Analyse d'un capteur défaillant                   ",nbPasse, nbEchoue, nbTests);
    test(tCapteurNonDefaillant(gestionMateriel->GetCapteur(150),50,traitementCapteur,gestionMesure, gestionMateriel), "Analyse d'un capteur avec idCapteur = null ou idCapteur > 99", nbPasse, nbEchoue,nbTests);
    test(tCapteurNonDefaillant(gestionMateriel->GetCapteur(10),-5,traitementCapteur,gestionMesure, gestionMateriel),"Analyse d'un capteur r < 1", nbPasse, nbEchoue,nbTests);
    
    if(testCourbe == true){
        test(tCourbeAirCleanerCorrecte(gestionMateriel->GetAirCleaner(1),50,traitementMesure,gestionMesure,gestionMateriel),"Traçage de la courbe du air cleaner 1",nbPasse,nbEchoue,nbTests);
        test(tCourbeAirCleanerIncorrecte(gestionMateriel->GetAirCleaner(2),50,traitementMesure,gestionMesure,gestionMateriel),"Traçage de la courbe du air cleaner 2",nbPasse,nbEchoue,nbTests);
        test(tCourbeAirCleanerIncorrecte(gestionMateriel->GetAirCleaner(1),-1,traitementMesure,gestionMesure,gestionMateriel),"Traçage de la courbe du air cleaner 1 avec un rayon < 0",nbPasse,nbEchoue,nbTests);
    }
    // RESUME DES TESTS
    cout << "##### FIN DES TESTS #####" << endl;
    cout << "Nombres de tests effectues : " << *nbTests << endl;
    cout << "Nombres de tests reussis : " << *nbPasse << endl;
    cout << "Nombres de tests echoues : " << *nbEchoue << endl;

    delete gestionMateriel;
    delete gestionMesure;  
    delete date;
    delete traitementMesure;
    delete traitementCapteur;
    delete nbTests;
    delete nbPasse;
    delete nbEchoue;
    return 0;
}


void test(bool retour, string description, int* nbPasse, int* nbEchoue, int* nbTests)
{
    (*nbTests)++;
    cout << "- Test " << *nbTests << " : " << description << " ->";
    if(retour)
    {
        cout << " v passe" << endl;
        (*nbPasse)++;
    }
    else
    {
        cout << " x echoue" << endl;
        (*nbEchoue)++;
    }
}

/********************************************************* DEFINITIONS */


bool tCourbeAirCleanerCorrecte(AirCleaner* c, int rayon,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel){
    /*
        On ne teste pas les valeurs de la courbe : si les tests sur le calcul de la qualité de l'air sont passés
        alors les bonnes valeurs sont forcément mises dans la courbe 
        si les tests sur le calcul de la qualité de l'air ne sont pas passés, on n'effectue pas ces tests
    */
    if(traitement->CourbeAirCleaner(c,rayon,mesure,materiel) == true){
        return true;
    }
    else{
        return false;
    }
}

bool tCourbeAirCleanerIncorrecte(AirCleaner* c, int rayon,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel){

    if(traitement->CourbeAirCleaner(c,rayon,mesure,materiel) == false){
        return true;
    }
    else{
        return false;
    }
}
bool tCalculQualiteAirZoneValide(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel)
{

    vector<int> v;
    if(traitement->CalculQualiteAirZone(44, 0.4, 100, date, mesure, materiel,v) == 7)
    {
        return true;
    }
    testCourbe = false;
    return false;
}

bool tCalculQualiteAirZoneNonCouverte(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel)
{

    vector<int> v;
    if(traitement->CalculQualiteAirZone(0, 0, 1, date, mesure, materiel,v) == -2)
    {
        return true;
    }
    testCourbe = false;
    return false;   
}

bool tCalculQualiteAirZoneInvalide(Date * date,TraitementMesure * traitement,GestionMesure* mesure, GestionMateriel* materiel)
{

    vector<int> v;
    if(traitement->CalculQualiteAirZone(200, 200, 10, date, mesure, materiel,v) == -1)
    {
        return true;
    }
    else
    {   
        testCourbe = false;
        return false;
    }    
}



bool tCapteurNonDefaillant(Capteur * capteur, int rayon,TraitementCapteur * traitement,GestionMesure* mesure, GestionMateriel* materiel)
{

    if(!(traitement->identifierCapteurDefaillant(capteur, rayon, mesure, materiel)))
    {
        return true;
    }
    return false;
}

bool tCapteurDefaillant(Capteur * capteur, int rayon,TraitementCapteur * traitement,GestionMesure* mesure, GestionMateriel* materiel)
{ 

    if(traitement->identifierCapteurDefaillant(capteur, rayon, mesure, materiel))
    {
        return true;
    }
    return false;
}