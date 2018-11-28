//
// Created by alon on 23/11/18.
//

#include <list>
#include "interface.h"
#include "MyCustomer.h"
#include "MyEmployee.h"

#ifndef AP1_FLIGHT_H
#define AP1_FLIGHT_H

/// Forward Declarations
class Reservation;

class MyFlight : public Flight {
public:
    /// ---------- CONSTRUCTORS - DESCRUCTORS ----------
    MyFlight(const string&, int, Date, string&, string&, Plane*);
    MyFlight(DescriptorsFactory*, int, list<Employee *>&, Date, string&, string&, Plane*);
    MyFlight(DescriptorsFactory*, int, list<Reservation *> &, list<Employee *>&, Date, string&, string&, Plane*);
    ~MyFlight() override;

    /// ---------- INITIALIZATION ----------
    void initializeID(DescriptorsFactory* factoryPtr);

    /// ---------- GETTERS & SETTERS ----------
    void addReservation(Reservation*);

    string              getID() override;
    int                 getModelNumber() override;
    list<Reservation*>  getReservations() override;
    list<Employee*>     getAssignedCrew() override;
    Date                getDate() override;
    string              getSource() override;
    string              getDestination() override;

private:
    Descriptor          descriptor;
    int                 modelNumber;
    Date                flightDate;
    string              source;
    string              destination;
    Plane*              plane;
    list<Employee*>     employees;
    list<Reservation*>  reservations;
};

#endif //AP1_FLIGHT_H