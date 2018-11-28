//
// Created by alon on 25/11/18.
//

#ifndef AP1_MYIMPLEMENTATION_H
#define AP1_MYIMPLEMENTATION_H

#include <vector>
#include <list>

// ---- Interface ----
#include "interface.h"

// ---- Self Implemented Functions -----
#include "MyPlane.h"
#include "MyFlight.h"
#include "MyEmployee.h"
#include "MyCustomer.h"
#include "MyReservation.h"
#include "Descriptors/DescriptorsFactory.h"
#include "Generic_Structures/ObjectsMap.h"


class MyImplementation : public Ex2 {
private:
    map<int, int> availablePlanesCounter;

    DescriptorsFactory*               factory;
    map<string, Plane*>               planesMap;
    map<string, Flight*>              flightsMap;
    map<string, Customer*>            customersMap;
    map<Jobs, map<string, Employee*>> employeesMap;
    map<string, Reservation*>         reservationsMap;


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
    bool            isEmployeeAvailableOn           (string&, Date);
    Plane*          findAvailablePlaneInSystem      (int, Date);
    vector<Flight*> getFlightsForEmployee           (string&);
    template <class T> vector<T>   findCrewForFlight               (vector<Jobs>, Date);

    void exit() override;
};

#endif //AP1_MYIMPLEMENTATION_H
