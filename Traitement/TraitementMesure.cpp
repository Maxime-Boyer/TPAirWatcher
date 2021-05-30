/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Ensemble> (fichier Ensemble.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include "TraitementMesure.h"
#include "../Materiel/Date.h"
#include "../Materiel/Mesure.h"
#include "../Administration/GestionMateriel.h"
#include "../Administration/GestionMesure.h"
#include <vector>
#include <ctime>
#include <cstring>
using namespace std;

inline int max_indice( int a , int b , int c, int d) {
    int max = a;
    if(max < b){
        max = b;
    }
    if(max < c){
        max = c;
    }
    if(max < d)
    {
        max = d;
    }
    return max;
}

//------------------------------------------------------ Include personnel


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Ensemble::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


TraitementMesure::TraitementMesure(){
    tabIndiceAtmoO3 = new int[9];
    tabIndiceAtmoNo2 = new int[9];
    tabIndiceAtmoSo2 = new int[9];
    tabIndiceAtmoPm10 = new int[9];

    //On remplit les tableaux d'indice à partir des valeurs du site 
    //https://fr.wikipedia.org/wiki/Indice_de_qualit%C3%A9_de_l%27air#:
    //~:text=Il%20existe%20principalement%20deux%20indices,l%27indice%20ATMO&text=pour%20les
    //%20agglom%C3%A9rations%20de%20taille,nombre%20plus%20r%C3%A9duit%20de%20polluants.
    tabIndiceAtmoO3[0] = 29;
    tabIndiceAtmoO3[1] = 54;
    tabIndiceAtmoO3[2] = 79;
    tabIndiceAtmoO3[3] = 104;
    tabIndiceAtmoO3[4] = 129;
    tabIndiceAtmoO3[5] = 149;
    tabIndiceAtmoO3[6] = 179;
    tabIndiceAtmoO3[7] = 209;
    tabIndiceAtmoO3[8] = 239;

    tabIndiceAtmoNo2[0] = 29;
    tabIndiceAtmoNo2[1] = 54;
    tabIndiceAtmoNo2[2] = 84;
    tabIndiceAtmoNo2[3] = 109;
    tabIndiceAtmoNo2[4] = 134;
    tabIndiceAtmoNo2[5] = 164;
    tabIndiceAtmoNo2[6] = 199;
    tabIndiceAtmoNo2[7] = 274;
    tabIndiceAtmoNo2[8] = 399;

    tabIndiceAtmoSo2[0] = 39;
    tabIndiceAtmoSo2[1] = 79;
    tabIndiceAtmoSo2[2] = 119;
    tabIndiceAtmoSo2[3] = 159;
    tabIndiceAtmoSo2[4] = 199;
    tabIndiceAtmoSo2[5] = 249;
    tabIndiceAtmoSo2[6] = 299;
    tabIndiceAtmoSo2[7] = 399;
    tabIndiceAtmoSo2[8] = 499;

    tabIndiceAtmoPm10[0] = 6;
    tabIndiceAtmoPm10[1] = 13;
    tabIndiceAtmoPm10[2] = 20;
    tabIndiceAtmoPm10[3] = 27;
    tabIndiceAtmoPm10[4] = 34;
    tabIndiceAtmoPm10[5] = 41;
    tabIndiceAtmoPm10[6] = 49;
    tabIndiceAtmoPm10[7] = 64;
    tabIndiceAtmoPm10[8] = 79;

}

TraitementMesure::~TraitementMesure(){
    delete[] tabIndiceAtmoO3;
    delete[] tabIndiceAtmoNo2;
    delete[] tabIndiceAtmoSo2;
    delete[] tabIndiceAtmoPm10;
}

void TraitementMesure::CourbeAirCleaner(AirCleaner cleaner, int rayon){
    if(rayon > 0){

        Date * dateDebutCourbe = new Date(cleaner.GetDateInstallation()->operator-(1));
        Date * dateBeginGraph = new Date(dateDebutCourbe);
        
        cout << "++ Declaration des dates de début OK" << endl;
        /*
        Dans le cas où les datasets sont à jour nous pouvons utiliser les lignes ci dessous.
        Or dans le cas de ce TP, nous sommes bloqués au 31 décembre 2019.
        
        time_t actuel = time(0);
        tm *ltm = localtime(&actuel);
        Date * dateActuelle = new Date(1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        */
        Date * dateActuelle = new Date(2019, 12, 31, 12, 00, 00); // Dernière date du fichier soit 31/12/2019 à midi
        Date * dateFinCourbe;
        cout << "++ Initialisation des dates de fin OK" << endl;
        
        if(cleaner.GetDateDesinstallation() != nullptr){
            dateFinCourbe = new Date(cleaner.GetDateDesinstallation());
        }
        else{
            dateFinCourbe = new Date(dateActuelle);
        }
        cout << "++ Récupération date de fin OK" << endl;

        int nbDays = dateFinCourbe->Number_days_between(dateDebutCourbe);
        int indice = 0;
        int indiceMax = 10;
        int ** courbe = new int*[nbDays];
        cout << "++ Initialisation des variables 1 OK" << endl;
        for (int i = 0; i < nbDays; i++)
        {
            courbe[i] = new int[indiceMax];
        }
        cout << "++ Declaration de la courbe OK" << endl;

        Date * currentDay;

        for(int i = 0; i < nbDays; i++)
        {
            currentDay = dateBeginGraph->operator+(i);
            indice = this->CalculQualiteAirZone(cleaner.GetLatitude(),cleaner.GetLongitude(),rayon,currentDay);
            courbe[i][indice] = 1;
        }
        cout << "++ Remplissage de la courbe OK" << endl;

        cout << " ^" << endl;
        cout << " |" << endl;
        for(int i = 0; i < indiceMax; i++){
            cout << indiceMax-i << "|";
            for(int j = 0; j < nbDays; j++){
                if(courbe[j][indiceMax-i-1] == 1){
                    cout << "*";
                }
                else{
                    cout <<" " ; 
                }
            }
            cout << endl;
        }
  
        cout << " ";
        for(int i = 0; i < nbDays+1;i++){
            cout << "-";
        }
        cout << ">";
    
        delete dateDebutCourbe;
        delete dateActuelle;
        delete dateBeginGraph;
        delete dateFinCourbe;
        for (int i = 0; i < nbDays; i++)
        {
            delete[] courbe[i];
        }
        delete[] courbe;
    }
    else
    {
        cout << "++ IMPOSSIBLE CLEANER NULL OU RAYON NEGATIF" << endl;
    }
    //return void;

}//------ Fin de Méthode


int TraitementMesure::CalculQualiteAirZone(int Latitude, int Longitude, int rayon, Date * date)
{
    int o3 = 0;
    int so2 = 0;
    int no2 = 0;
    int pm10 = 0;
    int nbMesure = 0;
    int indiceO3 = 0;
    int indiceSo2 = 0;
    int indiceNo2 = 0;
    int indicePm10 = 0;

    cout << "++ Calcul Qualite Air Zone" << endl;
    
    GestionMesure * objetGestionMesure = new GestionMesure();
    GestionMateriel * objetGestionMateriel = new GestionMateriel();

    vector<int> capteurDansLaZone = objetGestionMateriel->ObtenirIdCapteurZone(Latitude,Longitude,rayon);
    cout << "++ Avant boucle for sur les capteurs"<< endl;
    for (unsigned int i = 0; i < capteurDansLaZone.size(); i++)
    {
        cout << "++   rentrer boucle for sur les capteurs" << endl;
        vector<Mesure*> mesures = objetGestionMesure->ObtenirDonneCapteurJour(capteurDansLaZone[i], date);
        cout << "++   creation vector<mesure*> mesures" << endl;
        nbMesure++;

        for (vector<Mesure*>::iterator mesuresIter = mesures.begin(); mesuresIter != mesures.end(); mesuresIter++)
        {
            cout << "++     rentrer for mesure comparaison" << endl;
            if((*mesuresIter)->GetTypeMesureId().compare("O3") == 0){
                o3 = o3 + (*mesuresIter)->GetValue();
            }else if((*mesuresIter)->GetTypeMesureId().compare("SO2") == 0){
                 so2 = so2 + (*mesuresIter)->GetValue();
            }else if((*mesuresIter)->GetTypeMesureId().compare("NO2") == 0){
                no2 = no2 + (*mesuresIter)->GetValue();
            }else if((*mesuresIter)->GetTypeMesureId().compare("PM10") == 0){
                pm10 = pm10 + (*mesuresIter)->GetValue();
            }
        }

        /*for (int j = 0; j<4; j++)
        {
            cout << "++     rentrer for mesure comparaison" << endl;
            if(mesures[j]->GetTypeMesureId().compare("O3") == 0){
                o3 = o3 + mesures[j]->GetValue();
            }else if(mesures[j]->GetTypeMesureId().compare("SO2") == 0){
                 so2 = so2 + mesures[j]->GetValue();
            }else if(mesures[j]->GetTypeMesureId().compare("NO2") == 0){
                no2 = no2 + mesures[j]->GetValue();
            }else if(mesures[j]->GetTypeMesureId().compare("PM10") == 0){
                pm10 = pm10 + mesures[j]->GetValue();
            }
        }*/

        cout << "++   sorti boucle comparaison" << endl;
    }
    cout << "++ sorti boucle for sur les capteurs" << endl;
    /*for (vector<int>::iterator capteurZoneIter = capteurDansLaZone.begin(); capteurZoneIter != capteurDansLaZone.end(); capteurZoneIter++)
    {
        vector<Mesure*> mesures = objetGestionMesure->ObtenirDonneCapteurJour(capteurDansLaZone[i], date);
        vector<Mesure> mesures = objetGestionMesure->ObtenirDonneCapteurActuelle(capteurZoneIter);
        nbMesure = nbMesure + 1;
        for (vector<Mesure>::iterator mesuresIter = mesures.begin(); mesuresIter != mesures.end(); mesuresIter++)
        {
            if(mesuresIter->GetTypeMesureId().compare("O3") == 0){
                o3 = o3 + mesuresIter->GetValue();
            }else if(mesuresIter->GetTypeMesureId().compare("SO2") == 0){
                 so2 = so2 + mesuresIter->GetValue();
            }else if(mesuresIter->GetTypeMesureId().compare("NO2") == 0){
                no2 = no2 + mesuresIter->GetValue();
            }else if(mesuresIter->GetTypeMesureId().compare("PM10") == 0){
                pm10 = pm10 + mesuresIter->GetValue();
            }
        }*/
        
    o3 = o3/nbMesure;
    so2 = so2/nbMesure;
    no2 = no2/nbMesure;
    pm10 = pm10/nbMesure;

        
    //Exemple pour l’indice de O3, c’est exactement pareil pour le reste
    for(int i = 0; i < 9; i++)
    {
        if(o3 >= 240){
            indiceO3 = 10;
        }
        if(o3 <= tabIndiceAtmoO3[i])
        {
            indiceO3 = i+1;
        }
        if(no2 >= 400){
            indiceO3 = 10;
        }
        if(no2 <= tabIndiceAtmoNo2[i])
        {
            indiceNo2 = i+1;
        }
        if(so2 >= 500){
            indiceO3 = 10;
        }
        if(so2 <= tabIndiceAtmoSo2[i])
        {
            indiceSo2= i+1;
        }
        if(pm10 >= 80){
            indiceO3 = 10;
        }
        if(pm10 <= tabIndiceAtmoPm10[i])
        {
            indicePm10 = i+1;
        }
    }
    
    return max_indice(indiceO3,indiceNo2,indiceSo2,indicePm10);
}
    


//------------------------------------------------------------------ PRIVE
//----------------------------------------------------- Méthodes protégées
    