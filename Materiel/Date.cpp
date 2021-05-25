#include "Date.h"
#include <iostream>
#include <cmath>
using namespace std;

Date::Date(){

}

Date::~Date(){

}

Date::Date(string date){
    day = stoi(date.substr(0,2));
    month = stoi(date.substr(3,2));
    year = stoi(date.substr(6,4));
    hour = stoi(date.substr(12,2));
    minutes = stoi(date.substr(15,2));
    seconds = stoi(date.substr(18,2));
}

int Date::nombreJoursParMois(int mois)
{
    switch(mois){
        case 1:
            return 31;
        case 2:
            return 28;
        case 3: 
            return 31;
        case 4:
            return 30;
        case 5: 
            return 31;
        case 6:
            return 30;
        case 7: 
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12: 
            return 31;
        default:
            cout << "Erreur lors de l'appel nombre de jours mauvais numéro de mois" << endl;
            return 30;
    }
}

int Date::operator-(int nbDays)
{
    //On décide de faire des soustractions seulement sur des jours
    if(day - nbDays <= 0)
    {
        month--;
        day -= nbDays;
        if(month <= 0){ month = 12; year--;}
        day += nombreJoursParMois(month);
        cout << "pbl appel" << endl;
        cout << "mois : " << month << endl;
        cout << "jours : " << day << endl;
        cout << "année : " << year << endl;
    }
    else{
        day -= nbDays;
    }
    return day;
}

int Date::soustraireDate(Date * date)
{
    //On décide de faire des soustractions seulement sur des jours
    if(day - date->day <= 0)
    {
        month--;
        
        day -= date->day;

        if(month <= 0){ month = 12; year--;}
        day += nombreJoursParMois(month);
        cout << "mois : " << month << endl;
        cout << "jours : " << day << endl;
        cout << "année : " << year << endl;
    }
    else{
        day -= date->day;
    }
    return day;
}

int Date::operator+(int nbDays)
{
    //On décide de faire des additions seulement sur des jours
    day += nbDays;
    if(day > nombreJoursParMois(month))
    {
        day -= nombreJoursParMois(month);
        month++;
    }
    if(month > 12)
    {
        year++;
        month = 1;
    }
    return day; 
}

int Date::GetDay(){
    return day;
}
int Date::GetMonth(){
    return month;
}
int Date::GetYear(){
    return year;
}
int Date::GetHour(){
    return hour;
}
int Date::GetMinutes(){
    return minutes;
}
int Date::GetSeconds(){
    return seconds;
}

int main(){
    Date* d = new Date("03/01/2019  12:00:00");
    cout << d->GetDay() << "/" << d->GetMonth() << "/" << d->GetYear() << " " << d->GetHour() << ":" << d->GetMinutes() << ":" << d->GetSeconds()<< endl;
    Date* d2 = new Date("01/01/2019  12:00:00");
    int ope4plus = d2->operator+(4);
    int ope4moins = d2->operator-(1);
    int opeDmoins = d2->soustraireDate(d);
    cout << "on affiche d2 + 4 jours = " << ope4plus << endl;
    cout << "on affiche d2 - 4 jours = " << ope4moins << endl;
    cout << "on affiche d2 - d = " << opeDmoins << endl;
    //cout << "bonjour";
    return 0;
}