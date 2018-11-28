//
// Created by alon on 22/11/18.
//

#include <iostream>
#include <list>
#include "Airplane_Company_Management/interface.h"
#include "Airplane_Company_Management/MyImplementation.h"

using namespace std;

int main() {
    auto* myImplementation = new MyImplementation();

    // ---- PLANE 1 ----
    // MODEL
    int p1Model = 747;
    // CREW
    map<Jobs, int> p1crewNeeded;
    p1crewNeeded.insert(make_pair(NAVIGATOR, 1));
    p1crewNeeded.insert(make_pair(PILOT, 2));
    p1crewNeeded.insert(make_pair(FLY_ATTENDANT, 1));
    p1crewNeeded.insert(make_pair(MANAGER, 1));

    map<Classes, int> seats;
    seats.insert(make_pair(FIRST_CLASS, 2));
    seats.insert(make_pair(SECOND_CLASS, 3));


    Plane* p1 = myImplementation->addPlane(p1Model, p1crewNeeded, seats);

    // ---- END PLANE 1 ----

    // ---- CUSTOMER 1 ----
    string fullName = "Alon Vita";
    int priority = 1;

    myImplementation->addCustomer(fullName, priority);
    // ---- END CUSTOMER 1 ----
    // ---- CUSTOMER 2 ----
    fullName = "Evya Shtern";
    priority = 2;

    myImplementation->addCustomer(fullName, priority);
    // ---- END CUSTOMER 2 ----
    // ---- CUSTOMER 3 ----
    fullName = "Ofek Israel";
    priority = 3;

    myImplementation->addCustomer(fullName, priority);
    // ---- END CUSTOMER 3 ----
    // ---- CUSTOMER 4 ----
    fullName = "David Vita";
    priority = 4;

    myImplementation->addCustomer(fullName, priority);
    // ---- END CUSTOMER 4 ----


    // ---- EMPLOYEE 1 ----
    int seniority = 1;
    int bYear = 1993;
    string employerID = "EID1234";
    Jobs job = MANAGER;

    myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 1 ----
    seniority = 2;
    bYear = 1990;
    employerID = "EID0";
    job = FLY_ATTENDANT;

    myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 2 ----
    seniority = 93;
    bYear = 1880;
    employerID = "EID0";
    job = PILOT;

    myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 2 ----

    // ---- EMPLOYEE 3 ----
    seniority = 82;
    bYear = 1900;
    job = PILOT;
    employerID = "EID0";

    myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 3 ----

    // ---- EMPLOYEE 4 ----
    seniority = 50;
    bYear = 1940;
    job = NAVIGATOR;
    employerID = "EID2";

    myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 4 ----

    // ---- TEST DATES ----
    Date d = Date("10-10-1993");
    Date d1 = Date("10-10-1993");
    Date d2 = Date("10-10-1991");
    Date d3 = Date("10-11-1993");

    if(d == d1) cout << "DATE TEST 1 PASSED" << endl;

    if(d > d2) cout << "DATE TEST 2 PASSED" << endl;

    // ---- END TEST DATES ----



    cout << d.getDate();

    myImplementation->addFlight(747, d, "israel", "metula");
}