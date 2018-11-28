//
// Created by alon on 23/11/18.
//

#include "MyFlight.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------
/**
 * MyFlight(const string & fid, int modelNumber,
                   Date date, string & source,
                   string & destination, Plane * plane).
 *
 * @param fid const string& -- a string representing flight ID.
 * @param factoryPtr DescriptionFactory -- a pointer to a DescriptionFactory.
 * @param modelNumber int -- the model of the Plane for the MyFlight.
 * @param date Date -- the MyFlight date.
 * @param source string& -- a reference to the string representing the source of the MyFlight.
 * @param destination string& -- a reference to the string representing MyFlight's destination
 */
MyFlight::MyFlight(const string & fid, int modelNumber,
                   Date date, string & source,
                   string & destination, Plane * plane) : flightDate(date) {
    string dateStr = date.getDate();

    // initialize the rest of the fields
    this->descriptor = Descriptor(fid);
    this->plane         = plane;
    this->source        = source;
    this->flightDate    = Date(date);
    this->destination   = destination;
    this->modelNumber   = modelNumber;
    this->reservations  = list<Reservation*>(); // initialize reservation list
    this->employees     = list<Employee*>(); // initialize employee list
}

/**
 * MyFlight(int modelNumber,
               list<Reservation *> &reservations,
               list<Employee *> &employeesList,
               Date date, string& source,
               string& destination).
 *
 * @param factoryPtr DescriptionFactory -- a pointer to a DescriptionFactory.
 * @param modelNumber int -- the model of the Plane for the MyFlight.
 * @param reservations list<Reservations*> -- a list of reservations.
 * @param employeesList list<Employee*> -- a list of employees.
 * @param date Date -- the MyFlight date.
 * @param source string& -- a reference to the string representing the source of the MyFlight.
 * @param destination string& -- a reference to the string representing MyFlight's destination
 */
MyFlight::MyFlight(DescriptorsFactory* factoryPtr, int modelNumber,
               list<Reservation *> &reservations, list<Employee *>& employeesList,
               Date date, string& source, string& destination, Plane* plane) : flightDate(date) {
    // initialize Descriptor
    this->initializeID(factoryPtr);

    // get the date string
    string dateStr = date.getDate();

    // initialize the rest of the fields
    this->plane         = plane;
    this->source        = source;
    this->flightDate    = Date(date);
    this->destination   = destination;
    this->modelNumber   = modelNumber;
    this->reservations  = reservations;
    this->employees     = employeesList;
}

/**
 * MyFlight(int modelNumber,
               list<Employee *> &employeesList,
               Date date, string& source,
               string& destination).
 *
 * @param factoryPtr DescriptionFactory -- a pointer to a DescriptionFactory.
 * @param modelNumber int -- the model of the Plane for the MyFlight.
 * @param employeesList list<Employee*> -- a list of employees.
 * @param date Date -- the MyFlight date.
 * @param source string& -- a reference to the string representing the source of the MyFlight.
 * @param destination string& -- a reference to the string representing MyFlight's destination
 */
MyFlight::MyFlight(DescriptorsFactory* factoryPtr, int modelNumber,
                   list<Employee *> &employeesList, Date date,
                   string &src, string & dest, Plane* plane) : flightDate(date) {
    // initialize Descriptor
    this->initializeID(factoryPtr);

    // get the date string
    string dateStr = date.getDate();

    // initialize the rest of the fields
    this->plane         = plane;
    this->source        = src;
    this->flightDate    = Date(date);
    this->destination   = dest;
    this->modelNumber   = modelNumber;
    this->employees     = employeesList;
    this->reservations = list<Reservation*>();
}

/// ---------- INITIALIZATION ----------

/**
 * initializeID(DescriptorsFactory* factoryPtr).
 *
 * @param factoryPtr DescriptorsFactory* -- a pointer to a descriptor factory.
 */
void MyFlight::initializeID(DescriptorsFactory* factoryPtr) {
    this->descriptor = factoryPtr->giveFlightDescriptor();
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
list<Employee*> MyFlight::getAssignedCrew() { return this->employees; }

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