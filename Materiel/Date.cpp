#include "Date.h"
#include <iostream>
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

int operator+(Date const& date)
{
    if(date.seconds+ this->seconds > 60)
    {
        
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

int main(){
    Date* d = new Date("03/01/2019  12:00:00");
    cout << d->GetDay() << "/" << d->GetMonth() << "/" << d->GetYear() << " " << d->GetHour() << ":" << d->GetMinutes() << ":" << d->GetSeconds()<< endl;
    return 0;
}