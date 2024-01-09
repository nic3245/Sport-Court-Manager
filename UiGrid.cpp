#include <iostream>
#include <cstring>
#include <algorithm>
#include "UiGrid.h"
#include "Court.h"
#include "TimeSlot.h"
#include "UiGrid.h"

using namespace std;

UiGrid::UiGrid(Repository<Court> court_repo,string userName,ROLE role){
    this->court_repo = court_repo;
    this->userName = userName;
    this->role = role;
}


//displays the main menu
void UiGrid::showMainMenu(){
    cout << "\033[2J\033[1;1H";
    cout<<"-----------------------Newton Courts System MAIN MENU-------------------"<<endl;
    cout<<"To return to main menu enter: 0 "<<endl;
    cout<<"To view weekly court availability enter:  1 "<<endl;
    cout<<"To reserve a court enter: 2 "<<endl;
    cout<<"To cancel a reservation enter: 3 "<<endl;
    cout<<"To see your reservations for the week enter: 4 " << endl;
    cout<<"To Exit enter: X "<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
}
//shows the week view of availability of a court
bool UiGrid::showWeek(){
    Util util;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string start_date_string = util.get_string_date(util.seconds_since_epoch(ltm, 0));
    string end_date_string = util.get_string_date(util.seconds_since_epoch(ltm, 6));


    cout<<endl<< "Enter a date from "<< start_date_string << " - " <<end_date_string  <<" (eg: " <<   start_date_string <<  " ) -> ";
    string wish_date;
    cin>>  wish_date;
    vector<Court> courts = this->court_repo.getAll();

    string cort_no;
    cout<<endl<<"Choose a court  Enter 0 for Red Court, 1 for Blue court 2 for green court -> ";
    cin>>cort_no;
    if(cort_no > "2" ||  cort_no < "0"){
        cout<<endl<<"\033[31mInvalid court choice, so system showing the default court - Red Court\033[0m"<<endl;
        cort_no = "0";
    }

    Court red_court   = courts[stoi(cort_no)];


    set<long> epochSeconds =  red_court.get_avilable_days_in_epoch();


    cout<<"--" << util.getYearMonthString()<<"--"<<endl;
    cout<<"--" << red_court.getCourt_name() <<"--"  <<endl;
    vector<TimeSlot> timeSlots = red_court.getDaysTimeSlots(wish_date).getAll();
    cout<<"                          "<<endl;

    for(int j=0; j < timeSlots.size();j++){
        TimeSlot timeSlot = timeSlots[j];
        if(timeSlot.isBooked()){
            cout<<timeSlot.get_lot_number() << " : " << timeSlot.get_slot_startTime()  <<" -> "<< "\033[31m" << timeSlot.get_booking_user() << "\033[0m" <<  " ";
        }else{
            cout<<timeSlot.get_lot_number() << " : " << timeSlot.get_slot_startTime()  <<" -> "<< "\033[32mAvailable\033[0m" <<  " ";
        }
        if(j> 0 && (j+1) % 4 == 0){
            cout <<  timeSlot.get_slot_startTime() ;
            cout<<endl;

        }

    }


    return true;
}

//shows the reservations for a user
bool UiGrid::userReservations(){
    Util util;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string start_date_string = util.get_string_date(util.seconds_since_epoch(ltm, 0));
    string end_date_string = util.get_string_date(util.seconds_since_epoch(ltm, 6));


    vector<Court> courts = this->court_repo.getAll();

    Court red_court   = courts[0];
    Court blue_court   = courts[1];
    Court green_court   = courts[2];


    set<long> epochSeconds =  red_court.get_avilable_days_in_epoch();


    cout<<"                          "<<endl;

    vector<TimeSlot> red_reservations = red_court.getUserTimeSlots(userName).getAll();
    vector<TimeSlot> blue_reservations = blue_court.getUserTimeSlots(userName).getAll();
    vector<TimeSlot> green_reservations = green_court.getUserTimeSlots(userName).getAll();

    cout << "Red Court" << endl;
    for(int j=0; j < red_reservations.size();j++){
        TimeSlot timeSlot = red_reservations[j];
        cout<<timeSlot.get_lot_number() << " : " << timeSlot.get_slot_startTime() << endl;
        if(j> 0 && (j+1) % 4 == 0){
            cout <<  timeSlot.get_slot_startTime() ;
            cout<<endl;
        }
    }

    cout << "Blue Court" << endl;
    for(int j=0; j < blue_reservations.size();j++){
        TimeSlot timeSlot = blue_reservations[j];
        cout<<timeSlot.get_lot_number() << " : " << timeSlot.get_slot_startTime() << endl;
        if(j> 0 && (j+1) % 4 == 0){
            cout <<  timeSlot.get_slot_startTime() ;
            cout<<endl;
        }
    }

    cout << "Green Court" << endl;
    for(int j=0; j < green_reservations.size();j++){
        TimeSlot timeSlot = green_reservations[j];
        cout<<timeSlot.get_lot_number() << " : " << timeSlot.get_slot_startTime() << endl;
        if(j> 0 && (j+1) % 4 == 0){
            cout <<  timeSlot.get_slot_startTime() ;
            cout<<endl;
        }
    }

    return true;
}


//reserves a court
bool UiGrid::reserve(){
    vector<Court> courts = this->court_repo.getAll();
    Util util;



    time_t now = time(0);
    tm *ltm = localtime(&now);
    util.seconds_since_epoch(ltm, 6);
    util.seconds_since_epoch(ltm, 7);

    string start_date_string = util.get_string_date(util.seconds_since_epoch(ltm, 1));
    string end_date_string = util.get_string_date(util.seconds_since_epoch(ltm,6));


    string cort_no;
    cout<<endl<<"Choose a court  Enter 0 for Red Court, 1 for Blue court 2 for green court -> ";
    cin>>cort_no;
    if(cort_no > "2" ||  cort_no < "0"){
        cout<<endl<<"\033[31mInvalid court choice, so system choosing the default court - Red Court\033[0m"<<endl;
        cort_no = "0";
    }

    Court red_court   = courts[stoi(cort_no)];


    string wish_date;
    string slot_time;
    string beforeNoon;
    string name = userName;
    if (role == OFFICIAL) {
	while(true) {
	    cout << "Enter \"open\" for open player or \"member\" for member reservation: " << endl;
	    string choice;
	    cin>>choice;
	    if (choice == "open") {
		name = "Open Play";
		vector<string> times = {"6:0 PM","6:30 PM", "7:0 PM","7:30 PM",  "8:0 PM",  "8:30 PM"};
		for (string time : times) {
		    if (!red_court.reserveSlot(wish_date,time,name)) {
			cout << endl << "There is already something booked during 6-9PM." << endl;
			for (string time : times) {
			    red_court.cancelReservation(wish_date,time,"Open Play",PLAYER);
			}
			return false;
		    }
		}
	    }
	    else if (choice == "member"){
		cout << "What user would you like to reserve for? (You may reserve for yourself, just enter your own). Enter their username: ";
		cin>>name;
		break;		
	    }
	}
    }
    cout<<endl<< "Enter a date from "<< start_date_string << " - " <<  end_date_string  <<" (eg: " <<   start_date_string <<  " ) -> ";
    cin>>wish_date;
    cout<<endl<<"Do you want to pick a slot before noon y/n -> ";
    cin>>beforeNoon;
    cout<<endl<<"Enter the timeslot you wish to reserve (eg: 8:30, 1:0, 12:0, 12:30) -> ";
    cin>>slot_time;
    string key = "";
    if(beforeNoon == "y"){
        key =  slot_time + " " + "AM";
    }else{
        key =  slot_time + " " + "PM";
    }
    for (auto court : courts) {
	if(!court.preReserveValidation(role,key,wish_date, userName)){
            return false;
	}
    }
    if(red_court.reserveSlot(wish_date,key,name)){
        cout<<endl<<"You got the slot -> " << key<<endl;
        red_court.saveToFile();
        this->court_repo.push(red_court);
    }else{
        cout<<endl<<"Failed to book the slot -> " << key<<endl;
    }
}


//cancels a court
bool UiGrid::cancel(){
    vector<Court> courts = this->court_repo.getAll();
    Util util;

    int cort_no;
    cout<<endl<<"Choose a court  Enter 0 for Red Court, 1 for Blue court 2 for green court -> ";
    cin>>cort_no;
    if(cort_no > 2 ||  cort_no < 0){
        cout<<endl<<"Invalid court choice"<<endl;
        return false;
    }

    Court red_court   = courts[cort_no];

    string wish_date;
    string slot_time;
    string beforeNoon;
    cout<<endl<<"Enter the day you wish to cancel the court (eg: 2023-06-24) -> " ;
    cin>>wish_date;
    cout<<endl<<"Is the  slot before noon y/n -> ";
    cin>>beforeNoon;
    cout<<endl<<"Enter the timeslot you wish to cancel (eg: 8:30, 1:0, 12:0, 12:30) -> ";
    cin>>slot_time;
    string key = "";
    if(beforeNoon == "y"){
        key =  slot_time + " " + "AM";
    }else{
        key =  slot_time + " " + "PM";
    }
    if(red_court.cancelReservation(wish_date,key,this->userName,role)){
        cout<<"Cencelled -> " << key<<endl;
        red_court.saveToFile();
        this->court_repo.push(red_court);
    }else{
        cout<<"Failed to cancel the slot -> " << key<<endl;
    }

}


