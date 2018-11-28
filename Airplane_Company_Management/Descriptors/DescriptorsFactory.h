//
// Created by alon on 23/11/18.
//

#ifndef AP1_DESCRIPTORSFACTORY_H
#define AP1_DESCRIPTORSFACTORY_H

#include <string>
#include "Descriptor.h"
#include "../Utility/StringsUtility.h"

using namespace std;

#define PLANE_STR_IDENTIFIER "PID"
#define FLIGHT_STR_IDENTIFIER "FID"
#define CUSTOMER_STR_IDENTIFIER "CID"
#define EMPLOYEE_STR_IDENTIFIER "EID"
#define RESERVATION_STR_IDENTIFIER "RID"

class DescriptorsFactory {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    DescriptorsFactory();

    /// ---------- FACTORY ----------
    Descriptor givePlaneDescriptor();
    Descriptor giveFlightDescriptor();
    Descriptor giveEmployeeDescriptor();
    Descriptor giveCustomerDescriptor();
    Descriptor giveReservationDescriptor();

private:
    string employeeDescriptorCounter;
    string planeDescriptorCounter;
    string flightDescriptorCounter;
    string reservationDescriptorCounter;
    string customerDescriptorCounter;
};

#endif //AP1_DESCRIPTORSFACTORY_H
