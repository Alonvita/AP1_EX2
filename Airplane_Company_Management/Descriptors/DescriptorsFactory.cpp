//
// Created by alon on 23/11/18.
//

#include "DescriptorsFactory.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------
/**
 * DescriptorsFactory() Constructor.
 *
 */
DescriptorsFactory::DescriptorsFactory() {
    this->planeDescriptorCounter = "0";
    this->flightDescriptorCounter = "0";
    this->employeeDescriptorCounter = "0";
    this->customerDescriptorCounter = "0";
    this->reservationDescriptorCounter = "0";
}

/// ---------- FACTORY ----------
/**
 * giveEmployeeDescriptor().
 *
 * @return a Descriptor for the employee ID.
 */
Descriptor DescriptorsFactory::giveEmployeeDescriptor() {
    // Create an Employee descriptor with current count
    Descriptor EID = Descriptor(this->employeeDescriptorCounter, EMPLOYEE_STR_IDENTIFIER);

    // counter += 1
    this->employeeDescriptorCounter = findSum(this->employeeDescriptorCounter, "1");

    return EID;
}

/**
 * givePlaneDescriptor().
 *
 * @return a descriptor for the plane ID.
 */
Descriptor DescriptorsFactory::givePlaneDescriptor() {
    // Create a Plane descriptor with current count
    Descriptor PID = Descriptor(this->planeDescriptorCounter, PLANE_STR_IDENTIFIER);

    this->planeDescriptorCounter = findSum(this->planeDescriptorCounter, "1");

    return PID;
}

/**
 * giveReservationDescriptor().
 *
 * @return a descriptor for the reservation ID.
 */
Descriptor DescriptorsFactory::giveReservationDescriptor() {
    Descriptor RID = Descriptor(this->reservationDescriptorCounter, RESERVATION_STR_IDENTIFIER);

    this->reservationDescriptorCounter = findSum(this->reservationDescriptorCounter, "1");

    return RID;
}

/**
 * giveCustomerDescriptor().
 *
 * @return a descriptor for the Customer ID
 */
Descriptor DescriptorsFactory::giveCustomerDescriptor() {
    Descriptor CID = Descriptor(this->customerDescriptorCounter, CUSTOMER_STR_IDENTIFIER);

    this->customerDescriptorCounter = findSum(this->customerDescriptorCounter, "1");

    return CID;
}

/**
 * giveFlightDescriptor().
 *
 * @return a descriptor for the Flight ID.
 */
Descriptor DescriptorsFactory::giveFlightDescriptor() {
    Descriptor FID = Descriptor(this->flightDescriptorCounter, FLIGHT_STR_IDENTIFIER);

    this->flightDescriptorCounter = findSum(this->flightDescriptorCounter, "1");

    return FID;
}