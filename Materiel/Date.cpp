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

Date * Date::operator-(int nbDays)
{
    Date * newDate = new Date(this); 

    //On décide de faire des soustractions seulement sur des jours
    if(newDate->day - nbDays <= 0)
    {
        newDate->month--;
        newDate->day -= nbDays;
        if(newDate->month <= 0){ newDate->month = 12; newDate->year--;}
        newDate->day += days_month[month-1];
    }
    else{
        newDate->day -= nbDays;
    }
    return newDate;
}

Date * Date::operator+(int nbDays)
{
    //On décide de faire des additions seulement sur des jours
    day += nbDays;
    if(day > days_month[month-1])
    {
        day -= days_month[month-1];
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

int Date::Number_days_between(Date * dateSup)
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
			nb_days += days_month[month-1-1]; //(ANNEE_BISSEXTILE(d2Year) && month == 2) ? 29 : 
	} else {
		for (month = d1Month ; month <= 12 ; month++)
			nb_days += days_month[month-1-1]; //(ANNEE_BISSEXTILE(d1Year) && month == 2) ? 29 : 
		for (month = 1 ; month < d2Month ; month++)
			nb_days += days_month[month-1-1]; //(ANNEE_BISSEXTILE(d2Year) && month == 2) ? 29 : 
		for (year = d1Year+1 ; year < d2Year ; year++)
			nb_days += 365; // Années //(ANNEE_BISSEXTILE(year)) ? 366 : 
	}
	
	return nb_days;
}

/*
int main(){
    Date* d = new Date("2019-01-03 12:00:00");
    cout << d->GetDay() << "/" << d->GetMonth() << "/" << d->GetYear() << " " << d->GetHour() << ":" << d->GetMinutes() << ":" << d->GetSeconds()<< endl;
    Date* d2 = new Date("2019-02-28 12:00:00");
    Date * d3 = new Date(d2->operator-(1));
    Date* d4 = new Date("2019-18-07 12:00:00");

    cout << "on affiche d2 + 1 jours = " << d2->operator+(1)->GetDay() << " " << d2->operator+(1)->GetMonth() << endl;
    //cout << "on affiche d3 = " << d3->GetDay() << " mois " << d3->GetMonth() << " year " << d3->GetYear() << endl;
    //cout << "nombre jour entre d et d4 : " << d->Number_days_between(d4) << endl;
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