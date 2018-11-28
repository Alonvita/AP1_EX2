//
// Created by alon on 23/11/18.
//

#include "MyFlight.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * MyFlight(Descriptor& desc, int modelNumber,
               list<Reservation *> &reservations, list<Employee *>& employeesList,
               Date date, string& source, string& destination, Plane* plane).
 *
 * @param Descriptor& desc -- a reference to Flight descriptor.
 * @param modelNumber int -- the model of the Plane for the MyFlight.
 * @param reservations list<Reservations*> -- a list of reservations.
 * @param employeesList list<Employee*> -- a list of employees.
 * @param date Date -- the MyFlight date.
 * @param source string& -- a reference to the string representing the source of the MyFlight.
 * @param destination string& -- a reference to the string representing MyFlight's destination
 */
MyFlight::MyFlight(Descriptor& desc, int modelNumber,
               list<Reservation *> &reservations, list<Employee *>& employeesList,
               Date date, string& source, string& destination, Plane* plane) : flightDate(date) {

    // get the date string
    string dateStr = date.getDate();

    // initialize the rest of the fields
    this->descriptor    = desc;
    this->plane         = plane;
    this->source        = source;
    this->flightDate    = Date(date);
    this->destination   = destination;
    this->modelNumber   = modelNumber;
    this->reservations  = reservations;
    this->assignedCrew     = employeesList;
}

/// ---------- GETTERS & SETTERS ----------

/**
 * isFirstClassFullyBooked().
 *
 * @return true if the flight's first class is fully booked, or false otherwise
 */
bool MyFlight::isFirstClassFullyBooked() {
    int countF = 0;

    for(Reservation* r : this->reservations) {
        if(r->getClass() == FIRST_CLASS)
            ++countF;
    }

    return (countF == this->plane->getMaxFirstClass());
}

/**
 * isEconomyClassFullyBooked().
 *
 * @return true if the flight's economy class is fully booked, or false otherwise
 */
bool MyFlight::isEconomyClassFullyBooked() {
    int countE = 0;

    for(Reservation* r : this->reservations) {
        if(r->getClass() == SECOND_CLASS)
            ++countE;
    }

    return (countE == this->plane->getMaxFirstClass());
}

//TODO: delete if max_baggage doesn't have to be checked for a flight...
//**
// * addBagage(int weight).
// *
// * @param weight int -- the bagage's weight
// * @return true if the new max baggage doesn't exceed the max baggage available for this flight.
// */
//bool MyFlight::addBagage(int weight) {
//    return (weight + currentBaggageWeight )
//}

/**
 * addReservation(Reservation*).
 *
 * @param reservation Reservation* -- a reservation ptr.
 */
void MyFlight::addReservation(Reservation* reservation) {
    this->reservations.push_back(reservation);
    this->currentBaggageWeight += reservation->getMaxBaggage();
}

/**
 * getReservations().
 *
 * @return the list of reservations for this MyFlight.
 */
list<Reservation*> MyFlight::getReservations() { return this->reservations; }

/**
 * getID().
 *
 * @return the ID of this MyFlight.
 */
string MyFlight::getID() { return this->descriptor.getID(); }

/**
 * getDate().
 *
 * @return the date of the MyFlight
 */
Date MyFlight::getDate() { return this->flightDate; }

/**
 * getModelNumber().
 *
 * @return the model of the Plane for the MyFlight.
 */
int MyFlight::getModelNumber() { return this->modelNumber; }

/**
 * getAssignedCrew().
 *
 * @return the list of employees for this MyFlight.
 */
list<Employee*> MyFlight::getAssignedCrew() { return this->assignedCrew; }

/**
 * getDestination().
 *
 * @return the destination of the MyFlight.
 */
string MyFlight::getDestination() { return this->destination; }

/**
 * getSource().
 *
 * @return the MyFlight's source
 */
string MyFlight::getSource() { return this->source; }