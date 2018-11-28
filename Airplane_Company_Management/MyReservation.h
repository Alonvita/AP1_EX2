//
// Created by alon on 23/11/18.
//



#ifndef AP1_RESERVATION_H
#define AP1_RESERVATION_H

#include "interface.h"
#include "Descriptors/DescriptorsFactory.h"

/// Forward Declarations
class Flight;
class Customer;

class MyReservation : public Reservation {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    MyReservation(const string&, Customer*, Flight*, Classes, int);
    MyReservation(DescriptorsFactory*, Customer*, Flight*, Classes, int);
    ~MyReservation() override;

    /// ---------- INITIALIZATION ----------
    void initializeID(DescriptorsFactory* factoryPtr);

    /// ---------- GETTERS & SETTERS----------
    string      getID() override;
    int         getMaxBaggage() override;
    Classes     getClass() override;
    Flight*     getFlight() override;
    Customer*   getCustomer() override;

private:
    Descriptor  descriptor;
    int         maxBaggage;
    Classes     classes;
    Flight*     flight;
    Customer*   costumer;
};

#endif //AP1_RESERVATION_H
