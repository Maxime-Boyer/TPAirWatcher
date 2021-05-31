#include "AirCleaner.h"

AirCleaner::AirCleaner(){

}

AirCleaner::~AirCleaner(){
    delete dateInstallation;
    delete dateDesinstallation;

}

AirCleaner::AirCleaner(int id,double lat,double lon , Date * instal, Date* desinstal){
    this->idCleaner = id;
    this->latitude = lat;
    this->longitude = lon;
    this->dateInstallation = instal;
    this->dateDesinstallation = desinstal;
}

AirCleaner::AirCleaner( const AirCleaner & unAirCleaner )
{
    this->idCleaner = unAirCleaner.idCleaner;
    this->latitude = unAirCleaner.latitude;
    this->longitude = unAirCleaner.longitude;
    this->dateInstallation = new Date(unAirCleaner.dateInstallation);
    this->dateDesinstallation = new Date(unAirCleaner.dateDesinstallation);
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
