//
// Created by alon on 27/11/18.
//

#include "ParseHandling.h"

///---------- FROM FILE PARSE HANDLING ----------
/**
 * generate(Parse target, string searcherID).
 *
 * @param target Parse -- the parse of required item
 * @param searcherID string -- the id to search by
 * @return a template <class T>
 */
template <class T>
T ParseHandling::generateSingle(SingleParse target, string searcherID) {
    ofstream file;
    SingleParse searcherType;

    // open the right file, based on what we want to search
    switch (target) {
        case FLIGHT:
            return generateFlightByFlightID(searcherID);

        case RESERVATION:
            return getReservationFromFile(searcherID);

        case CUSTOMER:
            return getCustomerByCustomerID(searcherID);

        case EMPLOYEE:
            // search for a single employee
            return getEmployeeByEmployeeID(searcherID);

        case PLANE:
            // extract searcherType
            searcherType = identifyID(searcherID);

            // get plane by plane ID
            if(searcherType == PLANE) {
                return getPlaneByPlaneID(searcherID);
            }

            // get plane by flight ID
            if(searcherType == FLIGHT) {
                return getPlaneByFlightID(searcherID);
            }

            throw runtime_error("Unknown target - searcherID combination.");

        default:
            throw runtime_error("Unknown target type.");
    }
}

/**
 * generateMultiple(SingleParse target, string searcherID).
 *
 * @param target MultipleParse -- an enum representing the type of item to look for.
 * @param searcherID string -- id to search by.
 *
 * @return a vector of all occurences in the file
 */
template <class T>
vector<T> ParseHandling::generateMultiple(MultipleParse target, string searcherID) {
    SingleParse searcherType;

    switch (target) {
        case RESERVATIONS:
            searcherType = identifyID(searcherID);
            if(searcherType == FLIGHT)
                return generateReservationsByFlightID(searcherID);

            if(searcherType == CUSTOMER)
                return generateReservationsByCustomerID(searcherID);

        case EMPLOYEES:
            return generateEmployeesByFlightID(searcherID);

        case JOBS:
            return generateJobsByPlaneID(searcherID);
    }
}

///---------- UTILITY ----------
/**
 * identifyID(string id).
 *
 * @param id string -- a string representing an ID
 * @return the type of ID, determined by the 3 first digits of it.
 */
SingleParse ParseHandling::identifyID(string& id) {
    // identifier <- 3 letters from position 0
    string identifier = id.substr(0, 3);

    if(strcmp(identifier.c_str(), PLANE_STR_IDENTIFIER) == 0) {
        return PLANE;
    }

    if(strcmp(identifier.c_str(), CUSTOMER_STR_IDENTIFIER) == 0) {
        return CUSTOMER;
    }

    if(strcmp(identifier.c_str(), FLIGHT_STR_IDENTIFIER) == 0) {
        return FLIGHT;
    }

    if(strcmp(identifier.c_str(), EMPLOYEE_STR_IDENTIFIER) == 0) {
        return EMPLOYEE;
    }

    if(strcmp(identifier.c_str(), RESERVATION_STR_IDENTIFIER) == 0) {
        return RESERVATION;
    }

    throw runtime_error("Unknown ID.");
}