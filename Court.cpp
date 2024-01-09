#include <iomanip>
#include <iomanip>


#include "TimeSlot.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>

#include "Court.h"
#include "Util.h"
#include "Role.h"


using namespace std;

Court::Court(string court_name){
    this->court_name = court_name;
    init();
}

string Court::getCourt_name(){
    return this->court_name;
}
//gets the time
void Court::init(){
    Util util;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 0));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 1));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 2));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 3));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 4));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 5));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 6));
    days_epoch_set.insert(util.seconds_since_epoch(ltm, 7));
    if(this->is_slots_initiliazed_previously()){
        this->loadFromFile();
    }else{
        for (long epoch_time : days_epoch_set) {

            string date_string = util.get_string_date(epoch_time);


            for (int hour = 6; hour <= 23; hour++) {
                for (int minute = 0; minute < 60; minute += 30) {
                    string slot_time_string = "";
                    if(hour < 12){
                        slot_time_string = to_string(hour) + ":" + to_string(minute )+ " AM";
                    }else if (hour == 12){
                        slot_time_string = to_string(hour) + ":" + to_string(minute )+ " PM";
                    }else{
                        slot_time_string = to_string(hour-12) + ":" + to_string(minute )+ " PM";
                    }
                    cout<<date_string<<" "<<slot_time_string<<endl;
                    TimeSlot timeSlot(date_string,slot_time_string,"X");
                    timeslot_repo.push(timeSlot);
                }
            }
        }
    }
}

//writes the time to a file
void Court::saveToFile(){
    ofstream file( this->court_name + "_booking.txt");
    for (TimeSlot timeSlot : this->timeslot_repo.getAll()) {
        file<<timeSlot;
    }
    file.close();
}

//checks to see if the slots were initialized
bool Court::is_slots_initiliazed_previously(){
    std::ifstream infile(this->court_name + "_booking.txt");
    return infile.good();
}
//gets the things from the file
Repository<TimeSlot> Court::loadFromFile(){
    Repository<TimeSlot> repo_timeSlot;
    std::ifstream file( this->court_name + "_booking.txt");
    Util util;
    string s = "";
    string delimiter = "|";

    size_t pos = 0;
    string token;

    while (std::getline(file, s)) {
        int token_position = 1;
        string date_string ;
        string slot_time = "";
        bool   slot_reserved = false;
        string booking_user;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            if(token_position == 1){
                date_string = token;
            }else if(token_position == 2){
                slot_time = token;
            }else if(token_position == 3){
                if(token == "1"){
                    slot_reserved = true;
                }
            }else if(token_position == 4){
                booking_user = token;
            }
            token_position += 1;
            s.erase(0, pos + delimiter.length());
        }
        TimeSlot timeSlot(date_string,slot_time,booking_user);
        if(slot_reserved){
            timeSlot.reserve_TimeSlot();
        }
        timeslot_repo.push(timeSlot);
    }


    file.close();


    slideSevenDayWindow();

    return repo_timeSlot;
}
//gets the avaliable days
set<string> Court::get_avilable_days(){
    Util util;
    set<string> avilable_days;
    for (long epoch_time : days_epoch_set) {
        avilable_days.insert(util.get_string_date(epoch_time));
    }
    return avilable_days;
}

set<long> Court::get_avilable_days_in_epoch(){
    return days_epoch_set;
}

Repository<TimeSlot> Court::getTimeSlots(){
    return timeslot_repo;
}

Repository<TimeSlot> Court::getDaysTimeSlots(string date_string){
    Repository<TimeSlot> daysSlots;
    vector<TimeSlot> sevenDaysSlots = timeslot_repo.getAll();
    for(TimeSlot timeSlot : sevenDaysSlots){
        if(timeSlot.get_lot_number() == date_string){
            daysSlots.push(timeSlot);
        }
    }
    return daysSlots;
}
//reserves a slot
bool Court::reserveSlot(string date_key,string slot_time,string user_id){
    cout<<date_key<< "  " << slot_time;
    for(TimeSlot timeSlot : timeslot_repo.getAll()){

        if(timeSlot.get_lot_number() == date_key &&  timeSlot.get_slot_startTime() == slot_time){

            if(!timeSlot.isBooked()){
                timeSlot.reserve_TimeSlot();
                timeSlot.set_booking_user(user_id);
                timeslot_repo.push(timeSlot);
            }
            return true;
        }
    }
    return false;
}

//cancels a reservation
bool Court::cancelReservation(string date_key,string slot_time,string loggedin_user_id,ROLE role){
//   cout<<slot_user <<" "<<  loggedin_user_id << " " << role;
    if(role == PLAYER ){
        for(TimeSlot timeSlot : timeslot_repo.getAll()){
            if(timeSlot.get_lot_number() == date_key  &&  timeSlot.get_slot_startTime() == slot_time){
                if(timeSlot.isBooked() && loggedin_user_id == timeSlot.get_booking_user() ){
                    timeSlot.cancel_timeSlot();
                    timeSlot.set_booking_user("X");
                    timeslot_repo.push(timeSlot);
                    return true;
                }

            }
        }
    }

    if(role == OFFICIAL  ){
        for(TimeSlot timeSlot : timeslot_repo.getAll()){
            if(timeSlot.get_lot_number() == date_key &&  timeSlot.get_slot_startTime() == slot_time){
                if(timeSlot.isBooked()){
                    timeSlot.cancel_timeSlot();
                    timeSlot.set_booking_user("X");
                    timeslot_repo.push(timeSlot);
                    return true;
                }

            }
        }
    }

    if(role == COACH ){
        for(TimeSlot timeSlot : timeslot_repo.getAll()){
            if(timeSlot.get_lot_number() == date_key && loggedin_user_id == timeSlot.get_booking_user()){
                if(timeSlot.isBooked() && loggedin_user_id == timeSlot.get_booking_user() ){
                    timeSlot.cancel_timeSlot();
                    timeSlot.set_booking_user("X");
                    timeslot_repo.push(timeSlot);
                    return true;
                }

            }
        }
    }

    return false;
}


//checks for the restrictions for reserving
bool Court::preReserveValidation(ROLE actor_role,string key,string day, string userName){

    vector<string> coch_time_slots = {  "9:0 AM","9:30 AM", "10:0 AM","10:30 AM",  "11:0 AM",  "11:30 AM",  "3:0 PM",  "3:30 PM","4:0 PM",  "4:30 PM", "5:0 PM ",   "5:30 PM"} ;

    string slot_start_time = key;
    if(actor_role == COACH){
	// Check if value is in the vector
	auto in = std::find(coch_time_slots.begin(), coch_time_slots.end(), slot_start_time);
    
	if (in == coch_time_slots.end()) {
            cout<<endl<<" Your reservation failed, sessions or lessons only during 9am-12pm and 3-6pm on weekdays "<<endl;
	    return false;
        }

    }else if(actor_role == PLAYER){
        Util util;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string d1 = util.get_string_date(util.seconds_since_epoch(ltm, 0));
        string d2 = util.get_string_date(util.seconds_since_epoch(ltm, 1));

        if(!(d1 == day || d2 == day)){
            cout<<endl<<"Players can only make reservations within 48hrs of request."<<endl;
	    return false;
        }else{
	    vector<TimeSlot> user_times = getUserTimeSlots(userName).getAll();
	    int num_week = 0;
	    for (auto time_slot : user_times) {
		if (day == time_slot.get_lot_number()) {
		    cout << "You have reached your maximum reservations for the day." << endl;
		    return false;
		} else {
		    num_week += 1;
		}
	    }
	    if (num_week > 1) {
		cout << "You have reached your maximum reservations for the week." << endl;
		return false;
	    }
        }
    }

    return true;
}
//allows to reserve for seven days
bool Court::slideSevenDayWindow(){
    Util util;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    util.seconds_since_epoch(ltm, 6);
    util.seconds_since_epoch(ltm, 7);


    string date_string = util.get_string_date(util.seconds_since_epoch(ltm, 7));
    bool is_seventh_day_in_repo = false;
    for (TimeSlot timeSlot : this->timeslot_repo.getAll()) {
        if(timeSlot.get_lot_number() == date_string){
            is_seventh_day_in_repo = true;
        }
    }

    if(!is_seventh_day_in_repo){
        cout<<"No";
        for (int hour = 6; hour <= 23; hour++) {
            for (int minute = 0; minute < 60; minute += 30) {
                string slot_time_string = "";
                if(hour < 12){
                    slot_time_string = to_string(hour) + ":" + to_string(minute )+ " AM";
                }else if (hour == 12){
                    slot_time_string = to_string(hour) + ":" + to_string(minute )+ " PM";
                }else{
                    slot_time_string = to_string(hour-12) + ":" + to_string(minute )+ " PM";
                }
                TimeSlot timeSlot(date_string,slot_time_string,"X");
                timeslot_repo.push(timeSlot);
            }
        }
    }

    saveToFile();
    return true;
}

Repository<TimeSlot> Court::getUserTimeSlots(string userName){
    Repository<TimeSlot> userSlots;
    vector<TimeSlot> sevenDaysSlots = timeslot_repo.getAll();
    for(TimeSlot timeSlot : sevenDaysSlots){
        if(timeSlot.get_booking_user() == userName){
            userSlots.push(timeSlot);
        }
    }
    return userSlots;
}

