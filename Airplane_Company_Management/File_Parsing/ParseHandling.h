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
#include "File_Parsing_Utility/Line.h"
#include "../Descriptors/DescriptorsFactory.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

enum SingleParse { FLIGHT, EMPLOYEE, CUSTOMER, RESERVATION, PLANE };
enum MultipleParse { EMPLOYEES, RESERVATIONS, JOBS };

class ParseHandling {
private:

public:
    ///---------- FROM FILE PARSE HANDLING ----------
    template <class T>
    T generateSingle(SingleParse target, string searcherID);

    template <class T>
    vector<T> generateMultiple(MultipleParse target, string searcherID);

    template <class T>
    vector<T> generateVector(MultipleParse target, string searcherID);

    ///---------- PARSING FROM FILE ----------
    // ---- EMPLOYEE ----
    Employee* getEmployeeByEmployeeID(string eid);
    vector<Employee*> generateEmployeesByFlightID(string fid);

    // ---- RESERVATION ----
    Reservation* getReservationFromFile(string rid);
    vector<Reservation*> generateReservationsByFlightID(string fid);
    vector<Reservation*> generateReservationsByCustomerID(string cid);

    // ---- PLANES ----
    Plane* getPlaneByPlaneID(string pid);
    Plane* getPlaneByFlightID(string fid);
    vector<Jobs> generateJobsByPlaneID(string pid);

    // ---- CUSTOMER ----
    Customer getCustomerByCustomerID(string cid);

    // ---- FLIGHT ----
    Flight* generateFlightByFlightID(string fid);

    ///---------- PARSING TO FILE ----------


    ///---------- UTILITY ----------
    SingleParse identifyID(string& id);
};
#endif //AP1_FROM_FILE_H
