#include "TimeSlot.h"
#include "Util.h"

//Constructor
TimeSlot::TimeSlot(string date_key,string slot_start_time,string booking_user){
    this->date_key = date_key;
    this->slot_start_time = slot_start_time;
    this->booked = false;
    this->booking_user = booking_user;
}

//Check the slot is available
bool TimeSlot::isBooked(){
    return this->booked;
}

//get the time slot number
string TimeSlot::get_lot_number(){
    return this->date_key;
}

//reserve the slot
void TimeSlot::reserve_TimeSlot(){
    this->booked = true;
}

//cancel the reservation
void TimeSlot::cancel_timeSlot(){
    this->booked = false;
}

//get the slot start time
string TimeSlot::get_slot_startTime(){
    return this->slot_start_time;
}

void TimeSlot::set_booking_user(string booking_user){
    this->booking_user = booking_user;
}
string TimeSlot::get_booking_user(){
    return this->booking_user;
}

