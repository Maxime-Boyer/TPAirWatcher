#include "TypeMesure.h"

TypeMesure::TypeMesure(){

}

TypeMesure::~TypeMesure(){
    
}

TypeMesure::TypeMesure(int id, string unit, string descr){
    this->attributeId = id;
    this->unit = unit;
    this-> description = descr;
}

string TypeMesure::GetUnit(){
    return unit;
}

string TypeMesure::GetDescription(){
    return description;
}

int TypeMesure::GetAttributeId(){
    return attributeId;
}