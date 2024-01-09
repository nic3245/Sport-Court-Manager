
#include <vector>


#include "Util.h"




Util::Util(){

}
//gets the time
time_t Util::seconds_since_epoch(struct tm* date, int days){
    string date_string = "";
    const time_t ONE_DAY =  24 * 60 * 60 ;
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;
    return date_seconds;
}

//gets the date
string Util::get_string_date(time_t date_seconds){
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", localtime(&date_seconds));
    std::string date_string(buffer);
    return date_string;
}
//gets the month
string Util::getYearMonthString(){
    vector<string> months = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    // Get the current time as a time_t value.
    time_t now = time(nullptr);

    // Get the year and month from the time_t value.
    struct tm *tm = localtime(&now);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon ;
    string monthYear = months[month] + "  " + to_string(year);
    return monthYear;
}









