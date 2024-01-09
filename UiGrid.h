
#ifndef UiGrid_hpp
#define UiGrid_hpp

#include "CourtSystem.h"
#include "UiGrid.h"
#include "Role.h"
//defines the states for a user
enum STATE{
    INPUT,
    WAIT,
    VIEW,
    WEEK,
    DAY,
    RESERVE,
    CANCEL,
    RESERVATIONS,
    END
};




class UiGrid{
private:
    Repository<Court> court_repo;
    string userName;
    ROLE role;

public:
    UiGrid(Repository<Court> court_repo,string userName,ROLE role);
    void showMainMenu();
    bool showWeek();
    bool reserve();
    bool cancel();
    bool userReservations();



};


#endif
