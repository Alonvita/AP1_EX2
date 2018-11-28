//
// Created by alon on 25/11/18.
//

#ifndef AP1_FROM_FILE_H
#define AP1_FROM_FILE_H

#define MODELS_FP "../DatabaseFiles/models.txt"
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
    T generateSingle(SingleParse target, const string& searcherID);

    template <class T>
    vector<T> generateMultiple(MultipleParse target, const string& searcherID);

    template <class T>
    vector<T> generateVector(MultipleParse target, const string& searcherID);

    ///---------- PARSING FROM FILE ----------
    // ---- EMPLOYEE ----
    Employee* getEmployeeByEmployeeID(const string& eid);
    vector<Employee*> generateEmployeesByFlightID(const string& fid);

    // ---- RESERVATION ----
    Reservation* getReservationFromFile(const string& rid);
    vector<Reservation*> generateReservationsByFlightID(const string& fid);
    vector<Reservation*> generateReservationsByCustomerID(const string& cid);

    // ---- PLANES ----
    Plane* getPlaneByPlaneID(const string& pid);
    Plane* getPlaneByFlightID(const string& fid);
    vector<Jobs> generateJobsByPlaneID(const string& pid);

    // ---- CUSTOMER ----
    Customer* getCustomerByCustomerID(const string& cid);

    // ---- FLIGHT ----
    Flight* generateFlightByFlightID(const string& fid);

    ///---------- PARSING TO FILE ----------


    ///---------- UTILITY ----------
    SingleParse identifyID(const string& id);
    Jobs parseJobFromString(const string& jobStr);
    Classes parseStringToClass(const string& cls);
    map<Jobs, int> parseCrewNeededForPlane(int modelID);
};
#endif //AP1_FROM_FILE_H
