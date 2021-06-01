#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>
using namespace std;

#include "GestionMateriel.h"
#include "../Materiel/AirCleaner.h"
#include "../Materiel/Date.h"
#define RAYON 6378.137

GestionMateriel::GestionMateriel(){
  this->MiseEnMemoireCapteur();
  this->MiseEnMemoireAirCleaner();
}

GestionMateriel::~GestionMateriel(){

  for(auto capteur : capteurs){
    delete capteur;
  }
  for(auto cleaner : cleaners){
    delete cleaner;
  }
  


}

void GestionMateriel::MiseEnMemoireAirCleaner()
/*
  Ouverture du fichier cleaners.csv pour récupérer et stocker ses informations
*/
{
  ifstream fic;
  fic.open("Administration/cleaners.csv");

  if(fic){

  }
  else{
        throw runtime_error("Could not open file");
  }
  
  string line;
  int id;
  double latitude;
  double longitude;
  Date* start = nullptr;
  Date* stop = nullptr;

  string delimiter = ";";
  string partOfLine;
  size_t pos = 0;
  int i = 0;

    //Parcours du fichier 
    while(fic.eof() == 0){
        getline(fic,line);

        if(fic.eof() == 0){
          while ((pos = line.find(delimiter)) != std::string::npos) {
            partOfLine = line.substr(0, pos);
            switch(i){
              case 0:
                id = stoi(partOfLine.substr(7,1));
                break;
              case 1:
                latitude = atof(partOfLine.c_str());
                break;
              case 2:
                longitude = atof(partOfLine.c_str());
                break;
              case 3:
                start = new Date(partOfLine);
                break;
              case 4:
                stop = new Date(partOfLine);
                break;

            }
            line.erase(0, pos + delimiter.length());
            i++;
          }

          i  = 0;
          
          cleaners.push_back(new AirCleaner(id,latitude,longitude,start,stop));
        }
    }
    fic.close();
  
}



void GestionMateriel::MiseEnMemoireCapteur()
/*
  Ouverture du fichier sensors.csv pour récupérer et stocker ses informations
*/
{
    ifstream fic;
    fic.open("Administration/sensors.csv");
    
    if(fic){

    }
    else{
        throw runtime_error("Could not open file");
    }

    string line;
    int id;
    double latitude;
    double longitude;

    string delimiter = ";";
    string partOfLine;
    size_t pos = 0;
    int i = 0;

    //Parcours du fichier
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
    fic.close();
}

vector<int> GestionMateriel::ObtenirIdCapteurZone(double lat, double lon, double rayon)
/*
  Renvoie les Id de tous les capteurs présent dans une zone définie par sa locatlisation et un rayon
*/
{
  vector<int> capteurDansLaZone;
  double distanceCapteur;
  double latRadian = lat*0.01745;
  double lonRadian = lon*0.01745;

  //Pour chaque capteur 
  for(vector<Capteur*>::iterator iterateurCapteur = capteurs.begin(); iterateurCapteur != capteurs.end(); iterateurCapteur++)
  {
    
    double latRadian2 = (*iterateurCapteur)->GetLatitude()*0.01745;
    double lonRadian2 = (*iterateurCapteur)->GetLongitude()*0.01745;

    //On calcule la distance entre le capteur et le point de référence 
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


Capteur* GestionMateriel::GetCapteur(int id){
  for(vector<Capteur*>::iterator itr = capteurs.begin(); itr!= capteurs.end(); itr++)
  { 
      if((*itr)->GetSensorId() == id){
        return *itr;
      }
  }


  return nullptr;
}

vector<AirCleaner*> GestionMateriel::GetCleaners(){
    return cleaners;
}

AirCleaner* GestionMateriel::GetAirCleaner(double lat, double lon){
  for(vector<AirCleaner*>::iterator itr = cleaners.begin(); itr!= cleaners.end(); itr++)
  { 
      if((*itr)->GetLatitude() == lat){
        if((*itr)->GetLongitude() == lon){
          return *itr;
        }
      }
  }
  return nullptr;
}

AirCleaner* GestionMateriel::GetAirCleaner(int id){
  for(vector<AirCleaner*>::iterator itr = cleaners.begin(); itr!= cleaners.end(); itr++)
  { 
      if((*itr)->GetIdCleaner() == id){
        return *itr;
      }
  }

  return nullptr;
}