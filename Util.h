
#ifndef Util_hpp
#define Util_hpp

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;

class Util{

public:
    Util();
    time_t seconds_since_epoch(struct tm* date, int days);
    string get_string_date(time_t date_seconds);
    string getYearMonthString();


};


#endif

