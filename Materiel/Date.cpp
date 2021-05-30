#include "Date.h"
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

#define ANNEE_BISSEXTILE(A) ((!(A%4) && (A%100)) || !(A%400))
const int days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
    day = stoi(date.substr(8,2));
    month = stoi(date.substr(5,2));
    year = stoi(date.substr(0,4));
    hour = stoi(date.substr(11,2));
    minutes = stoi(date.substr(14,2));
    seconds = stoi(date.substr(17,2));
}

Date::Date(int year, int month, int day, int hour, int minutes, int seconds){
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minutes = minutes;
    this->seconds = seconds;
}

Date::Date(const Date & copyDate){
    this->day = copyDate.day;
    this->month = copyDate.month;
    this->year = copyDate.year;
    this->hour = copyDate.hour;
    this->minutes = copyDate.minutes;
    this->seconds = copyDate.seconds;
}

Date::Date(const Date * copyDate){
    this->day = copyDate->day;
    this->month = copyDate->month;
    this->year = copyDate->year;
    this->hour = copyDate->hour;
    this->minutes = copyDate->minutes;
    this->seconds = copyDate->seconds;
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

Date * Date::operator-(int nbDays)
{
    Date * newDate = new Date(this); 

    //On décide de faire des soustractions seulement sur des jours
    if(newDate->day - nbDays <= 0)
    {
        newDate->month--;
        newDate->day -= nbDays;
        if(newDate->month <= 0){ newDate->month = 12; newDate->year--;}
        newDate->day += nombreJoursParMois(month);
        cout << "pbl appel" << endl;
        cout << "mois : " << newDate->month << endl;
        cout << "jours : " << newDate->day << endl;
        cout << "année : " << newDate->year << endl;
    }
    else{
        newDate->day -= nbDays;
    }
    return newDate;
}

int Date::soustraireDate(Date * date)
{
    if(year != date->year){
        if(month != date->month){
            //if()
        }
    }

    /*int numero_jour( date d ) {
    int  m = (d.mois + 9) % 12;   // jan->10 fev->11 mar->0 ... dec->9
    int  a = d.annee - (m >= 10); // mais soustraire 1 an en jan et fev
    return 1461*a/4 - a/100 + a/400 + (m*306 + 5)/10 + d.jour;
    
    }*/
    
    return abs(day-date->day);
}



Date * Date::operator+(int nbDays)
{
    //On décide de faire des additions seulement sur des jours
    day += nbDays;
    if(day > days_month[month])
    {
        day -= days_month[month];
        month++;
    }
    if(month > 12)
    {
        year++;
        month = 1;
    }
    return this; 
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

int Date::number_days_between(Date * dateSup)
{
	//const int days_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int nb_days = 0;
	int year, month;
	
	nb_days += dateSup->GetDay() - this->GetDay(); // Jours
	
    int d1Year = this->GetYear();
    int d2Year = dateSup->GetYear();
    int d1Month = this->GetMonth();
    int d2Month = dateSup->GetMonth();

	if (d1Year == d2Year) {
		for (month = d1Month ; month < d2Month ; month++)
			nb_days += (ANNEE_BISSEXTILE(d2Year) && month == 2) ? 29 : days_month[month-1];
	} else {
		for (month = d1Month ; month <= 12 ; month++)
			nb_days += (ANNEE_BISSEXTILE(d1Year) && month == 2) ? 29 : days_month[month-1]; // Mois de d1
		for (month = 1 ; month < d2Month ; month++)
			nb_days += (ANNEE_BISSEXTILE(d2Year) && month == 2) ? 29 : days_month[month-1]; // Mois de d2
		for (year = d1Year+1 ; year < d2Year ; year++)
			nb_days += (ANNEE_BISSEXTILE(year)) ? 366 : 365; // Années
	}
	
	return nb_days;
}

/**
int main(){
    Date* d = new Date("03/01/2019  12:00:00");
    cout << d->GetDay() << "/" << d->GetMonth() << "/" << d->GetYear() << " " << d->GetHour() << ":" << d->GetMinutes() << ":" << d->GetSeconds()<< endl;
    Date* d2 = new Date("01/01/2019  12:00:00");
    //int ope4plus = d2->operator+(4);
    Date * d3 = new Date(d2->operator-(1));
    Date* d4 = new Date("18/07/2019  12:00:00");
    //int opeDmoins = d2->soustraireDate(d);
    cout << "on affiche d2 + 4 jours = " << d2->operator+(4) << endl;
    cout << "on affiche d3 = " << d3->GetDay() << " mois " << d3->GetMonth() << " year " << d3->GetYear() << endl;
    cout << "nombre jour entre d et d4 : " << d->number_days_between(d4) << endl;
    delete d;
    delete d2;
    delete d3;
    delete d4;

    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);


    Date * dateActuelle = new Date(1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    cout << dateActuelle->GetDay() << "/" << dateActuelle->GetMonth() << "/" << dateActuelle->GetYear() << " " << dateActuelle->GetHour() << ":" 
    << dateActuelle->GetMinutes() << ":" << dateActuelle->GetSeconds() << endl;
    
    delete dateActuelle;
    return 0;
}
*/