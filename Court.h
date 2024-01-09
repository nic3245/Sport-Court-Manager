
#ifndef Court_hpp
#define Court_hpp

#include <iostream>
#include <set>
#include "Repository.h"
#include "TimeSlot.h"
#include "Role.h"




using namespace std;

class Court {


public:
    string court_name;
    Repository<TimeSlot> timeslot_repo;
    Repository<TimeSlot> cancel_timeslot_repo;
    set<long> days_epoch_set;
    void init();




//methods for Court
public:
    Court(string name);
    string getCourt_name();
    void saveToFile();
    bool is_slots_initiliazed_previously();
    Repository<TimeSlot> loadFromFile();
    Repository<TimeSlot> getTimeSlots();
    set<string> get_avilable_days();
    set<long> get_avilable_days_in_epoch();
    Repository<TimeSlot> getDaysTimeSlots(string date_string);
    bool reserveSlot(string date_key,string slot_time,string user_id);
    bool cancelReservation(string date_key,string slot_time,string loggedin_user_id,ROLE role);
    bool preReserveValidation(ROLE actor,string key,string day, string userName);
    bool slideSevenDayWindow();
    Repository<TimeSlot> getUserTimeSlots(string userName);


    bool operator==(const Court& other)  {
        return court_name == other.court_name  ;
    }

    bool requestForCancel();
    bool viewCancelRequests();


};

#endif /* Court_hpp */

