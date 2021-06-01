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

void Date::operator-(int nbDays)
{
    //Pour les besoins de l'application, on a besoin de faire des soustractions seulement pour les jours 
    
    if(day - nbDays <= 0)
    {
        month--;
        day -= nbDays;
        if(month <= 0){ month = 12; year--;}
        day += days_month[month-1];
    }
    else{
        day -= nbDays;
    }
}

void Date::operator+(int nbDays)
{
    //Pour les besoins de l'application, on a besoin de faire des additions seulement pour les jours 
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
    /*
        Calcul le nombre de jour entre deux dates 
    */
	int nb_days = 0;
	int year, month;
	
	nb_days += dateSup->GetDay() - this->GetDay();
	
    int d1Year = this->GetYear();
    int d2Year = dateSup->GetYear();
    int d1Month = this->GetMonth();
    int d2Month = dateSup->GetMonth();

	if (d1Year == d2Year) {
		for (month = d1Month ; month < d2Month ; month++){
            nb_days += days_month[month-1];
        } 
	} else {
		for (month = d1Month ; month <= 12 ; month++)
			nb_days +=  days_month[month-1];
		for (month = 1 ; month < d2Month ; month++)
			nb_days += days_month[month-1]; 
		for (year = d1Year+1 ; year < d2Year ; year++)
			nb_days += 365; 
	}
	
    
	return nb_days;
}