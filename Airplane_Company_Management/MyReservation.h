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
    MyReservation(Descriptor& desc, Customer* costumer,
                  Flight *flight, Classes cls, int maxBaggage);
    ~MyReservation(){};

    /// ---------- GETTERS & SETTERS----------
    string      getID() override;
    int         getMaxBaggage() override;
    Classes     getClass() override;
    Flight*     getFlight() override;
    Customer*   getCustomer() override;
    void        associateToFlight(Flight*);

private:
    Classes     cls;
    Flight*     flight;
    Customer*   costumer;
    Descriptor  descriptor;
    int         maxBaggage;
};

#endif //AP1_RESERVATION_H
