
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <ctime>
using namespace std;

#include "GestionMesure.h"
#include "../Materiel/Date.h"
#include "../Materiel/Mesure.h"
#include "../Materiel/Capteur.h"

GestionMesure::GestionMesure(){
    this->MiseEnMemoireMesures();
}

GestionMesure::~GestionMesure(){
    for(auto inner : mesures){
        for(auto inner_deep : inner){
            for(auto mesure : inner_deep){
                delete mesure;
            }
        }
    }
}

void GestionMesure::MiseEnMemoireMesures()
/*
  Ouverture du fichier measurements.csv pour récupérer et utiliser ses informations
*/
{
    ifstream fic;
    fic.open("Administration/measurements.csv");
    
    Date * date = nullptr;
    int sensorId;
    string idTypeMesure;
    double value;
    string line;

    if(fic){

    }
    else{
        throw runtime_error("Could not open file");
    }

    

    string delimiter = ";";
    string partOfLine;
    size_t pos = 0;
    int i = 0;

    int actualId = -1;
    Date* actualDate = nullptr;
    int nbDate = -1;

    //Tant que le fichier n'est pas vide
    while(fic.eof() == 0){
        getline(fic,line);
        if(fic.eof() == 0){
            while ((pos = line.find(delimiter)) != std::string::npos) {
            partOfLine = line.substr(0, pos);

            switch(i){
                case 0:
                    date = new Date(partOfLine);
                    break;
                case 1:
                    sensorId = stoi(partOfLine.substr(6,2)); 
                    if(sensorId != actualId){
                        actualId = sensorId;
                        vector<vector<Mesure*>> v;
                        this->mesures.push_back(v);
                        nbDate = -1;
                    }

                    
                    if(actualDate == nullptr || date->equals(*actualDate) == false){
                        if(actualDate != nullptr);
                        delete actualDate;
                        actualDate = new Date(date);
                        nbDate++;
                        vector<Mesure*> v;
                        this->mesures[actualId].push_back(v);
                    }
                    
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

            i = 0;
            mesures[actualId][nbDate].push_back(new Mesure(sensorId,idTypeMesure,value,date));
            }
    }
    delete actualDate; 
}

vector<Mesure*> GestionMesure::ObtenirDonneCapteurActuelle(int sensorId)
{
    return  mesures[sensorId].back();
}

vector<Mesure*> GestionMesure::ObtenirDonneCapteurJour(int sensorId, Date * date){
    vector<vector<Mesure*>> mesuresSensor = mesures[sensorId];
    for(vector<vector<Mesure*>>::iterator itr = mesuresSensor.begin(); itr!= mesuresSensor.end(); itr++){
        if( ((*(itr))[0])->GetDateMesure()->equals(*date)){
            return *(itr);
        }
    }

    vector<Mesure*> v;
    return v;
}

vector<vector<Mesure*>> GestionMesure::ObtenirDonneCapteurPeriode(int sensorId, Date* start, Date* stop){
   vector<vector<Mesure*>> mesuresSensor = mesures[sensorId]; 
   vector<vector<Mesure*>> mesuresToReturn; 
   bool toAdd = false;
   for(vector<vector<Mesure*>>::iterator itr = mesuresSensor.begin(); itr!= mesuresSensor.end(); itr++){
        if( ((*(itr))[0])->GetDateMesure()->equals(*start)){
            toAdd = true;
            mesuresToReturn.push_back(*(itr));
        }
        else if(toAdd){
           mesuresToReturn.push_back(*(itr));  
        }
        else if(((*(itr))[0])->GetDateMesure()->equals(*stop)){
            mesuresToReturn.push_back(*(itr));
            return mesuresToReturn;
        }
    }

    vector<vector<Mesure*>> v;
    return v;
}

vector<vector<Mesure*>> GestionMesure::GetMesures(int sensorId){
    return mesures[sensorId];
}