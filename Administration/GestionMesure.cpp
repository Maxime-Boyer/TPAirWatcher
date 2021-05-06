
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <ctime>
using namespace std;

#include "GestionMesure.h"
#include "../Materiel/Date.h"
#include "../Materiel/Mesure.h"

GestionMesure::GestionMesure(){

}

GestionMesure::~GestionMesure){

}

void GestionMesure::MiseEnMemoireMesures(){
    ifstream fic;
    fic.open("sensors.csv");
    
    Date date;
    int idSensor;
    string idTypeMesure;
    double value;

    if(fic){

    }
    else{
        throw runtime_error("Could not open file");
    }

    

    string delimiter = ";";
    string partOfLine;
    size_t pos = 0;
    int i = 0;

    //Tant que le fichier n'est pas vide
    while(fic.eof() == 0){
        getline(fic,line);
        
        while ((pos = line.find(delimiter)) != std::string::npos) {
          partOfLine = line.substr(0, pos);
          switch(i){
            case 0:
                date = Date(partOfLine);
                break;
            case 1:
                sensorId = stoi(partOfLine.substr(6,2));  
                break;
            case 2:
                idTypeMesure = partOfLine;
                break;
            case 3: 
                value = atof(partOfLine.c_str());
                break;

          }
          line.erase(0, pos + delimiter.length());
          i++;
        }

        i  = 0;
        capteurs.push_back(new Mesure(sensorId,idTypeMesure,value,date));
    }
}

vector<Mesure*> GestionMesure::ObtenirDonneCapteurActuelle(int sensorId)
{
    vector<Mesure*> donneesActuelle;
    for (vector<Mesure*>::iterator iterateurMesure = mesures.begin(); iterateurMesure != mesures.end(); iterateurMesure++)
    {
        if((*iterateurMesure)->GetSensorId() == sensorId)
        {
            donneesActuelle.push_back(*iterateurMesure);
        }
    }
    return donneesActuelle;
}

vector<Mesure*> GestionMesure::GetMesures(){
    return mesures;
}