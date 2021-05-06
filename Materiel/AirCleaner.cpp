#include "AirCleaner.h"

AirCleaner::AirCleaner(){

}

AirCleaner::~AirCleaner(){

}

AirCleaner::AirCleaner(int id,double lat,double lon ,time_t instal){
    this->idCleaner = id;
    this->latitude = lat;
    this->longitude = lon;
    this->dateInstallation = instal;
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
time_t AirCleaner::GetDateInstallation(){
    return dateInstallation;
}