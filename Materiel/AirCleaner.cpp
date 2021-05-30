#include "AirCleaner.h"

AirCleaner::AirCleaner(){

}

AirCleaner::~AirCleaner(){

}

AirCleaner::AirCleaner(int id,double lat,double lon , Date * instal, Date* desinstal){
    this->idCleaner = id;
    this->latitude = lat;
    this->longitude = lon;
    this->dateInstallation = instal;
    this->dateDesinstallation = desinstal;
}

int AirCleaner::GetIdCleaner(){
    return idCleaner;
}
double AirCleaner::GetLatitude(){
    return latitude;
}
double AirCleaner::GetLongitude(){
    return longitude;
}
Date * AirCleaner::GetDateInstallation(){
    return dateInstallation;
}
Date * AirCleaner::GetDateDesinstallation(){
    return dateDesinstallation;
}
