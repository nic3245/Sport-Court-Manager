#include <stdlib.h>

#include "CourtSystem.h"
#include "Court.h"
#include "UiGrid.h"



CourtSystem::CourtSystem(){
    init();
}
//initializes the three courts
bool CourtSystem::init(){
    Court first_court("RED_COURT");
    if(first_court.is_slots_initiliazed_previously()){
        first_court.loadFromFile();
    }else{
        first_court.saveToFile();
    }
    court_repo.push(first_court);


    Court second_court("BLUE_COURT");
    if(second_court.is_slots_initiliazed_previously()){
        second_court.loadFromFile();
    }else{
        second_court.saveToFile();
    }
    court_repo.push(second_court);

    Court third_court("GREEN_COURT");
    if(third_court.is_slots_initiliazed_previously()){
        third_court.loadFromFile();
    }else{
        third_court.saveToFile();
    }
    court_repo.push(third_court);
    return true;
}


Repository<Court> CourtSystem::get_weekly_court_schedule(){
    return court_repo;
}

void CourtSystem::runCourtSystem(string userName,ROLE role){
    CourtSystem courtSystem;
    UiGrid ui(courtSystem.get_weekly_court_schedule(),userName,role);


    STATE state = WAIT;
    ui.showMainMenu();
    string input = "0";
    while(state != END) {
        switch(state){
            case WAIT:
                cin>>input;
                if(input == "0" ){
                    system("cls");
                    ui.showMainMenu();
                    state = INPUT;
                }else if(input == "X"  or input == "x"){
                    exit(0);
                }else  if(input == "1" ){
                    state = WEEK;
                }else  if(input == "2" ){
                    state = RESERVE;
                }else  if(input == "3" ){
                    state = CANCEL;
                }else  if(input == "4" ){
                    state = RESERVATIONS;
                }

                break;

            case INPUT:
                cin>>input;
                state = WAIT;
                break;
            case WEEK:
                ui.showWeek();
                cout << "Remember, enter 0 to return to main menu.";
                state = WAIT;
                break;
            case RESERVE:
                ui.reserve();
                cout << "Remember, enter 0 to return to main menu.";
                state = WAIT;
                break;
            case CANCEL:
                ui.cancel();
                cout << "Remember, enter 0 to return to main menu.";
                state = WAIT;
                break;
	    case RESERVATIONS:
		ui.userReservations();
		cout << "Remember, enter 0 to return to main menu.";
                state = WAIT;
		break;
            default:
                cout<<endl<<"unknown"<<endl;
        }
    }
}

