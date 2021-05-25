#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>
using namespace std;

#include "GestionMateriel.h"
#define RAYON 6378.137

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

        if(fic.eof() == 0){
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
}

vector<int> GestionMateriel::ObtenirIdCapteurZone(double lat, double lon, double rayon)
{
  vector<int> capteurDansLaZone;
  double distanceCapteur;
  double latRadian = lat*0.01745;
  double lonRadian = lon*0.01745;

  for(vector<Capteur*>::iterator iterateurCapteur = capteurs.begin(); iterateurCapteur != capteurs.end(); iterateurCapteur++)
  {
    
    double latRadian2 = (*iterateurCapteur)->GetLatitude()*0.01745;
    double lonRadian2 = (*iterateurCapteur)->GetLongitude()*0.01745;

    distanceCapteur= acos(sin(latRadian)*sin(latRadian2)+cos(latRadian)*cos(latRadian2)*cos(lonRadian2-lonRadian));
    distanceCapteur = RAYON*distanceCapteur;

    if(distanceCapteur < rayon)
      capteurDansLaZone.push_back((*iterateurCapteur)->GetSensorId());
  }
  
  return capteurDansLaZone;
  
}

vector<Capteur*> GestionMateriel::GetCapteurs(){
    return capteurs;
}


int main(){

    GestionMateriel gestion;
    gestion.MiseEnMemoireCapteur();
    
    vector<int> id = gestion.ObtenirIdCapteurZone(44,0.4,100);
    for(vector<int>::iterator iterateurCapteur = id.begin(); iterateurCapteur != id.end(); iterateurCapteur++)
    { 
      cout << *iterateurCapteur << endl;
    }
    return 0;
}