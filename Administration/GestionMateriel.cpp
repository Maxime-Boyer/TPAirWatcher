#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
using namespace std;

#include "GestionMateriel.h"
#include "../Materiel/Capteur.h"

GestionMateriel::GestionMateriel(){

}

GestionMateriel::~GestionMateriel(){

}

void GestionMateriel::MiseEnMemoireCapteur(){
    ifstream fic;
    fic.open("sensors.csv");
    
    string line;
    int id;
    double latitude;
    double longitude;

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
              id = stoi(partOfLine.substr(6,2));
              break;
            case 1:
              latitude = atof(partOfLine.c_str());
              break;
            case 2:
              longitude = atof(partOfLine.c_str());
              break;

          }
          line.erase(0, pos + delimiter.length());
          i++;
        }

        i  = 0;
        capteurs.push_back(new Capteur(id,latitude,longitude));
    }
}

vector<int> ObtenirIdCapteurZone(double lat, double lon, int rayon)
{
  
}

vector<Capteur*> GestionMateriel::GetCapteurs(){
    return capteurs;
}

/**
int main(){

    GestionMateriel gestion;
    gestion.MiseEnMemoireCapteur();
    cout << gestion.GetCapteurs().size();
}*/