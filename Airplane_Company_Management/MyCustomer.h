//
// Created by alon on 23/11/18.
//

#include "list"
#include "interface.h"
#include "Descriptors/DescriptorsFactory.h"

#ifndef AP1_CUSTOMER_H
#define AP1_CUSTOMER_H

/// Forward Declarations
class Reservation;

class MyCustomer : public Customer {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    MyCustomer(Descriptor& desc,
               string& fullName, int priority,
               list<Reservation *> &reservations);
    ~MyCustomer(){};

    /// ---------- GETTERS & SETTERS ----------
    void addReservation(Reservation*);

    string              getID() override;
    int                 getPriority() override;
    string              getFullName() override;
    list<Reservation*>  getReservations() override;

private:
    Descriptor          descriptor;
    string              fullName;
    int                 priority;
    list<Reservation*>  reservationsList;
};

#endif //AP1_CUSTOMER_H