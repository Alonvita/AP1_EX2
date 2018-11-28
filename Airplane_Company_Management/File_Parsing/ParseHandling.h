//
// Created by alon on 25/11/18.
//

#ifndef AP1_FROM_FILE_H
#define AP1_FROM_FILE_H

#define SPACE " "

#define MODELS_FP "../DatabaseFiles/models.txt"
#define PLANES_FP "../DatabaseFiles/planes.txt"
#define FLIGHTS_FP "../DatabaseFiles/flights.txt"
#define EMPLOYEE_FP "../DatabaseFiles/employees.txt"
#define CUSTOMER_FP "../DatabaseFiles/cusomers.txt"
#define RESERVATIONS_FP "../DatabaseFiles/reservations.txt"
#define ASSIGNMENTS_FILE "../DatabaseFiles/assignments.txt"

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
public:
    ///---------- CONSTRUCTORS - DESTRUCTORS ----------
    ParseHandling(){};
    ~ParseHandling(){};

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
    list<Employee*> generateEmployeesByFlightID(const string& fid);

    // ---- RESERVATION ----
    Reservation* getReservationByReservationID(const string &rid);
    list<Reservation*> generateReservationsByFlightID(const string& fid);
    list<Reservation*> generateReservationsByCustomerID(const string& cid);

    // ---- PLANES ----
    Plane* getPlaneByPlaneID(const string& pid);
    Plane* getPlaneByFlightID(const string& fid);

    // ---- CUSTOMER ----
    Customer* getCustomerByCustomerID(const string& cid);

    // ---- FLIGHT ----
    Flight* getFlightByFlightID(const string &fid);

    ///---------- PARSING TO FILE ----------
    void parseFlightsToFile(map<string, Flight*> flightsMap);
    void parseCustomersToFile(map<string, Customer*> customersMap);
    void parsePlanesToFile(map<int, map<string, Plane *>> planesMap);
    void parseEmployeesToFile(map<Jobs, map<string, Employee*>> employeesMap);
    void parseReservationsToFile(map<string, Reservation*> reservationsMap);


private:
    ///---------- UTILITY ----------
    SingleParse     identifyID(const string&);
    string          parseJobToString(Jobs);
    string          parseClassToStr(Classes cls);
    map<Jobs, int>  parseCrewNeededForPlane(int);
    Jobs            parseJobFromString(const string&);
    Classes         parseStringToClass(const string&);
    void            writeStrToFile(const string &, const string &);
};
#endif //AP1_FROM_FILE_H
