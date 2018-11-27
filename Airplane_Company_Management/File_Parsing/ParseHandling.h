//
// Created by alon on 25/11/18.
//

#ifndef AP1_FROM_FILE_H
#define AP1_FROM_FILE_H

#define PLANES_FP "../DatabaseFiles/planes.txt"
#define FLIGHTS_FP "../DatabaseFiles/flights.txt"
#define EMPLOYEE_FP "../DatabaseFiles/employees.txt"
#define CUSTOMER_FP "../DatabaseFiles/cusomers.txt"
#define RESERVATIONS_FP "../DatabaseFiles/reservations.txt"

#include "../interface.h"

#include <vector>
using namespace std;

enum Parse { FLIGHT, EMPLOYEE, CUSTOMER, RESERVATION, PLANE };

template <class T>
class ParseHandling {
private:

public:
    ///---------- PARSE HANDLING ----------
    T generate(Parse target, string searcherID);

    ///---------- PARSING FROM FILE ----------
    // ---- EMPLOYEE ----
    Employee* getEmployeeFromFile(string eid);
    vector<Employee*> generateEmployeesByFlightID(string fid);

    // ---- RESERVATION ----
    Reservation* getReservationFromFile(string rid);
    vector<Reservation*> generateReservationsByFlightID(string fid);
    vector<Reservation*> generateReservationsByCustomerID(string cid);

    // ---- RESERVATION ----
    Plane* getPlaneByPlaneID(string pid);
    Plane* getPlaneByFlightID(string fid);
    vector<Jobs> generateJobsByPlaneID(string pid);

    // ---- CUSTOMER ----
    Customer getCustomerByCustomerID(string cid);

    // ---- FLIGHT ----
    Flight* generateFlightByFlightID(string fid);

    ///---------- PARSING TO FILE ----------
};
#endif //AP1_FROM_FILE_H
