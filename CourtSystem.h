#ifndef CourtSystem_h
#define CourtSystem_h

#include "Repository.h"
#include "Court.h"


class CourtSystem{
private:
    Repository<Court> court_repo;
    Repository<TimeSlot> timeslot_repo;
    bool init();

    //methods for Court System
public:
    CourtSystem();
    Repository<Court> get_weekly_court_schedule();
    void runCourtSystem(string userName,ROLE role);



};


#endif
