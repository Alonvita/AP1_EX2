//
// Created by alon on 23/11/18.
//

#include "MyReservation.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * MyReservation(const string& id, Customer* customer, Flight* flight, Classes cls, int maxBaggage).
 *
 * @param const string& rid -- a reservation ID.
 * @param costumer Customer* -- a pointer to the costumer associated with this MyReservation.
 * @param flight Flight* -- a pointer to the flight associated with this MyReservation.
 * @param cls Classes -- the classes of the MyReservation.
 * @param maxBaggage int -- the max baggage for the MyReservation.
 */
MyReservation::MyReservation(const string& rid, Customer* customer, Flight* flight, Classes cls, int maxBaggage) {
    this->descriptor = Descriptor(rid);
    this->costumer = customer;
    this->flight = flight;
    this->classes = cls;
    this->maxBaggage = maxBaggage;
}

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
MyReservation::MyReservation(DescriptorsFactory* factoryPtr, Customer* costumer,
                             Flight *flight, Classes cls, int maxBaggage) {

    // Initialize Descriptor
    this->initializeID(factoryPtr);

    // Initialize the rest of the fields
    this->costumer = costumer;
    this->flight = flight;
    this->classes = cls;
    this->maxBaggage = maxBaggage;
}

/// ---------- INITIALIZATION ----------

/**
 * initializeID(DescriptorsFactory* factoryPtr).
 *
 * @param factoryPtr DescriptorsFactory* -- a pointer to a descriptor factory.
 */
void MyReservation::initializeID(DescriptorsFactory* factoryPtr) {
    this->descriptor = factoryPtr->giveReservationDescriptor();
}

/// ---------- GETTERS & SETTERS ----------
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
Classes MyReservation::getClass() { return this->classes; }

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