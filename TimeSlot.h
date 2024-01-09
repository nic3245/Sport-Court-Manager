

#ifndef TimeSlot_h
#define TimeSlot_h

#include <iostream>
#include <memory>
#include "Util.h"


using namespace std;
//the members for a Time Slot
class TimeSlot{
public:
    string date_key;
    string slot_start_time;
    bool booked;
    string booking_user;


public:
    TimeSlot(string date_key,string slot_start_time,string booking_user);
    bool isBooked();
    string get_lot_number();
    void reserve_TimeSlot();
    void cancel_timeSlot();
    string get_slot_startTime();
    void set_booking_user(string booking_user);
    string get_booking_user();

    friend std::ostream& operator<<(std::ostream& os,  const TimeSlot& b)    {
        Util util;
        os << b.date_key << "|" << b.slot_start_time  << "|" << b.booked   << "|" << b.booking_user  << "|" << endl;
        return os;
    }

    bool operator==(const TimeSlot& other)  {
        return date_key == other.date_key  && slot_start_time == other.slot_start_time;
    }

};




#endif /* TimeSlot_h */

