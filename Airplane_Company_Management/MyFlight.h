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
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    MyFlight(Descriptor& desc, int modelNumber,
             list<Reservation *> &reservations, list<Employee *>& employeesList,
             Date date, string& source, string& destination, Plane* plane);
    ~MyFlight(){};

    /// ---------- GETTERS & SETTERS ----------
    //TODO: check if relevant -> bool addBagage(int weight);
    Plane* getPlane();
    bool isFirstClassFullyBooked();
    bool isEconomyClassFullyBooked();
    void addReservation(Reservation*);

    string              getID() override;
    Date                getDate() override;
    string              getSource() override;
    int                 getModelNumber() override;
    string              getDestination() override;
    list<Reservation*>  getReservations() override;
    list<Employee*>     getAssignedCrew() override;

private:
    Plane*              plane;
    string              source;
    Date                flightDate;
    Descriptor          descriptor;
    int                 modelNumber;
    string              destination;
    list<Reservation*>  reservations;
    list<Employee*>     assignedCrew;
    int                 currentBaggageWeight = 0;
};

#endif //AP1_FLIGHT_H