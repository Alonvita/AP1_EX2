//
// Created by alon on 25/11/18.
//

#ifndef AP1_MYIMPLEMENTATION_H
#define AP1_MYIMPLEMENTATION_H

#include <vector>
#include <list>
#include <cstring>

// ---- Interface ----
#include "interface.h"

// ---- Self Implemented Functions -----
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyReservation.h"
#include "Utility/MapSorting.h"
#include "File_Parsing/ParseHandling.h"
#include "Descriptors/DescriptorsFactory.h"

#define PAIR_FROM_PLANE_MAP pair<int, map<string, Plane*>>
#define STRING_PLANE_MAP_PAIR pair<string, Plane*>

class MyImplementation : public Ex2 {
private:
    ParseHandling parseHandling;

    DescriptorsFactory*                 factory;
    map<string, Flight*>                flightsMap;
    map<string, Customer*>              customersMap;
    map<string, Reservation*>           reservationsMap;
    map<Jobs, map<string, Employee*>>   employeesMap;
    map<int, map<string, Plane*>>       availablePlanesTable;


public:
    MyImplementation();
    // TODO: change destructor to use ToFile for saving data before exit
    ~MyImplementation(){};

    /// ---------- GETTERS ----------
    Plane*          getPlane        (string id) override;
    Flight*         getFlight       (string id) override;
    Customer*       getCustomer     (string id) override;
    Employee*       getEmployee     (string id) override;
    Reservation*    getReservation  (string id) override;

    /// ---------- SETTERS ----------
    Customer* addCustomer(string full_name, int priority) override;
    Employee* addEmployee(int seniority, int birth_year,
                          string employer_id, Jobs title) override;
    Plane* addPlane(int model_number, map<Jobs, int> crew_needed,
                    map<Classes, int> max_passangers) override;
    Flight* addFlight(int model_number, Date date,
                      string source, string destination) override;
    Reservation* addResevation(string customerId, string flightId,
                               Classes cls, int max_baggage) override;

    /// ---------- UTILITY ----------
    bool isEmployeeAvailableOn (string&, Date);
    Plane* findAvailablePlaneInSystem (int, Date);
    vector<Flight*> getFlightsForEmployee (string&);
    list<Employee*> findCrewForFlight (map<Jobs, int>, Date);
    list<Reservation*> generateReservationsForFlight(string fid);

    void exit() override;
};

#endif //AP1_MYIMPLEMENTATION_H
