#include "Date.h"
#include <iostream>
#include <cmath>
using namespace std;

#define ANNEE_BISSEXTILE(A) (!(A%4) && (A%100) || !(A%400))

Date::Date(){

}

Date::~Date(){
    day = 0;
    year = 0;
    hour = 0;
    minutes = 0;
    seconds = 0;
}

Date::Date(string date){
    day = stoi(date.substr(0,2));
    month = stoi(date.substr(3,2));
    year = stoi(date.substr(6,4));
    hour = stoi(date.substr(12,2));
    minutes = stoi(date.substr(15,2));
    seconds = stoi(date.substr(18,2));
}

Date::Date(const Date & copyDate){
    this->day = copyDate.day;
    this->month = copyDate.month;
    this->year = copyDate.year;
    this->hour = copyDate.hour;
    this->minutes = copyDate.minutes;
    this->seconds = copyDate.seconds;
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

Date Date::operator-(int nbDays)
{
    Date newDate = *this;
    //On décide de faire des soustractions seulement sur des jours
    if(newDate.day - nbDays <= 0)
    {
        newDate.month--;
        newDate.day -= nbDays;
        if(newDate.month <= 0){ newDate.month = 12; newDate.year--;}
        newDate.day += nombreJoursParMois(month);
        cout << "pbl appel" << endl;
        cout << "mois : " << newDate.month << endl;
        cout << "jours : " << newDate.day << endl;
        cout << "année : " << newDate.year << endl;
    }
    else{
        newDate.day -= nbDays;
    }
    return newDate;
}

int Date::soustraireDate(Date * date)
{
    if(year != date->year){
        if(month != date->month){
            if()
        }
    }

    int numero_jour( date d ) {
    int  m = (d.mois + 9) % 12;   // jan->10 fev->11 mar->0 ... dec->9
    int  a = d.annee - (m >= 10); // mais soustraire 1 an en jan et fev
    return 1461*a/4 - a/100 + a/400 + (m*306 + 5)/10 + d.jour;
}
    
    return abs(day-date->day);
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

bool Date::equals(Date d){
    if(this->day == d.GetDay() && this->month == d.GetMonth() && this->year == d.GetYear()){
        return true;
    }
    else{
        return false;
    }
}

int nombre_jours( Date d1, Date d2)
{
	const int jours_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int nb_jours = 0;
	int annee, mois;
	
	nb_jours += d2.day - d1.day; // Jours
	
	if (d1.year == d2.year) {
		for (month = d1.month ; month < d2.month ; month++)
			nb_jours += (ANNEE_BISSEXTILE(d2.annee) && month == 2) ? 29 : jours_mois[month-1];
	} else {
		for (mois = d1.mois ; mois <= 12 ; mois++)
			nb_jours += (ANNEE_BISSEXTILE(d1.annee) && mois == 2) ? 29 : jours_mois[mois-1]; // Mois de d1
		for (mois = 1 ; mois < d2.mois ; mois++)
			nb_jours += (ANNEE_BISSEXTILE(d2.annee) && mois == 2) ? 29 : jours_mois[mois-1]; // Mois de d2
		for (annee = d1.annee+1 ; annee < d2.annee ; annee++)
			nb_jours += (ANNEE_BISSEXTILE(annee)) ? 366 : 365; // Années
	}
	
	return nb_jours;
}


int main(){
    Date* d = new Date("03/01/2019  12:00:00");
    cout << d->GetDay() << "/" << d->GetMonth() << "/" << d->GetYear() << " " << d->GetHour() << ":" << d->GetMinutes() << ":" << d->GetSeconds()<< endl;
    Date* d2 = new Date("01/01/2019  12:00:00");
    //int ope4plus = d2->operator+(4);
    Date d3 = d2->operator-(1);
    //int opeDmoins = d2->soustraireDate(d);
    //cout << "on affiche d2 + 4 jours = " << ope4plus << endl;
    cout << "on affiche d3 = " << d3.GetDay() << " mois " << d3.GetMonth() << " year " << d3.GetYear() << endl;
    return 0;
}
