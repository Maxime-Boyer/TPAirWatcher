#include "Mesure.h"
#include <iostream>
using namespace std;

Mesure::Mesure(){

}

Mesure::~Mesure(){
    delete dateMesure;
}

Mesure::Mesure(int sensorId, string attributeId, double v, Date* time){
    this->sensorId = sensorId;
    this->typeMesureId = attributeId;
    this->value = v;
    this->dateMesure = time;
}

int Mesure::GetSensorId(){
    return sensorId;
}

string Mesure::GetTypeMesureId(){
    return typeMesureId;
}

double Mesure::GetValue(){
    return value;
}

Date* Mesure::GetDateMesure(){
    return dateMesure;
}