//
// Created by alon on 23/11/18.
//

#include "MyReservation.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * MyReservation(DescriptorsFactory* factoryPtr, Customer *costumer,
                        Flight *flight, Classes classes, int maxBaggage).
 *
 * @param factoryPtr DescriptionFactory -- a pointer to a DescriptionFactory.
 * @param costumer Customer* -- a pointer to the costumer associated with this MyReservation.
 * @param flight Flight* -- a pointer to the flight associated with this MyReservation.
 * @param cls Classes -- the classes of the MyReservation.
 * @param maxBaggage int -- the max baggage for the MyReservation.
 */
MyReservation::MyReservation(Descriptor& desc, Customer* costumer,
                             Flight *flight, Classes cls, int maxBaggage) {

    // Initialize the rest of the fields
    this->descriptor = desc;
    this->costumer = costumer;
    this->flight = flight;
    this->cls = cls;
    this->maxBaggage = maxBaggage;
}

/// ---------- GETTERS & SETTERS ----------
/**
 * associateToFlight(Flight *f).
 *
 * @param f Flight* -- a pointer to a flight.
 */
void MyReservation::associateToFlight(Flight *f) {
    this->flight = f;
}

/**
 * getID().
 *
 * @return the MyReservation's ID.
 */
string MyReservation::getID() { return this->descriptor.getID(); }

/**
 * getClass().
 *
 * @return the classes for this MyReservation
 */
Classes MyReservation::getClass() { return this->cls; }

/**
 * getCustomer().
 *
 * @return the Customers of this MyReservation.
 */
Customer* MyReservation::getCustomer() { return this->costumer; }

/**
 * getFlight().
 *
 * @return the flight associated with this MyReservation.
 */
Flight* MyReservation::getFlight() { return this->flight; }

/**
 * getMaxBaggage().
 *
 * @return return the max baggage weight for the MyReservation
 */
int MyReservation::getMaxBaggage() { return this->maxBaggage; }