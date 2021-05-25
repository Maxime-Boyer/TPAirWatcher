
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

GestionMesure::~GestionMesure(){

}

void GestionMesure::MiseEnMemoireMesures(){
    ifstream fic;
    fic.open("sensors.csv");
    
    Date date;
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
                if(sensorId != actualId){
                    actualId = sensorId;
                    mesures[actualId].push_back(v);
                    vector<Mesure* > v;

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

        i  = 0;
        v.push_back(new Mesure(sensorId,idTypeMesure,value,date));
    }
}

Mesure* GestionMesure::ObtenirDonneCapteurActuelle(int sensorId)
{
    return mesures[sensorId].back();
}

vector<Mesure*> GestionMesure::GetMesures(int sensorId){
    return mesures[sensorId];
}

int main(){
    GestionMesure gestion;
    gestion.MiseEnMemoireMesures();
    Mesure* m = gestion.ObtenirDonneCapteurActuelle(0);
    cout << m->GetValue() << endl;
}