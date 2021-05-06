#include "Capteur.h"

Capteur::Capteur(){

}

Capteur::~Capteur(){

}

Capteur::Capteur(int id, double lat, double lon){
    this->sensorId = id;
    this->latitude = lat;
    this->longitude = lon;
}

int Capteur::GetSensorId(){
    return sensorId;
}

double Capteur::GetLatitude(){
    return latitude;
}

double Capteur::GetLongitude(){
    return longitude;
}