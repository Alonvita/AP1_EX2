//
// Created by alon on 23/11/18.
//

#include "MyCustomer.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS --------

/**
 * MyCustomer(string ID, string fullName, int priority, list<Reservation *> &reservations).
 *
 * @param desc Descriptor& -- a reference to a customer descriptor.
 * @param fullName string -- a string representing the MyCustomer's name.
 * @param priority int -- the priority of this MyCustomer in line.
 * @param reservations list<Reservation *> -- a list of reservations.
 */
MyCustomer::MyCustomer(Descriptor& desc,
                       string& fullName, int priority,
                       list<Reservation *> &reservations) {
    this->descriptor = desc;
    this->fullName = fullName;
    this->priority = priority;
    this->reservationsList = reservations;
}

/// ---------- GETTERS & SETTERS ----------

/**
 * addReservation(Reservation*).
 *
 * @param reservation Reservation* -- a reservation ptr
 */
void MyCustomer::addReservation(Reservation* reservation) {
    this->reservationsList.push_back(reservation);
}

/**
 * getID().
 *
 * @return the ID held by the descriptor.
 */
string MyCustomer::getID() { return this->descriptor.getID(); }

/**
 * getFullName().
 *
 * @return return the name of the MyCustomer.
 */
string MyCustomer::getFullName() { return this->fullName; }

/**
 * getPriority().
 *
 * @return return the priority of this MyCustomer.
 */
int MyCustomer::getPriority() { return this->priority; }

/**
 * getReservations().
 *
 * @return return this list of reservations of the MyCustomer.
 */
list<Reservation *> MyCustomer::getReservations() { return this->reservationsList; }