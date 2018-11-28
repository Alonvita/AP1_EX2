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
    cout << "DEBUG: Plane1 Added: " << p1->getID() << endl;
    Plane* p2 = myImplementation->addPlane(p1Model, p1crewNeeded, seats);
    cout << "DEBUG: Plane2 Added: " << p2->getID() << endl;

    // ---- END PLANE 1 ----

    // ---- CUSTOMER 1 ----
    string fullName = "Alon Vita";
    int priority = 1;

    Customer* c1 = myImplementation->addCustomer(fullName, priority);

    cout << "DEBUG: Customer1 Added: " << c1->getID() << endl;
    // ---- END CUSTOMER 1 ----
    // ---- CUSTOMER 2 ----
    fullName = "Evya Shtern";
    priority = 2;

    Customer* c2 = myImplementation->addCustomer(fullName, priority);

    cout << "DEBUG: Customer2 Added: " << c2->getID() << endl;
    // ---- END CUSTOMER 2 ----
    // ---- CUSTOMER 3 ----
    fullName = "Ofek Israel";
    priority = 3;

    Customer* c3 = myImplementation->addCustomer(fullName, priority);

    cout << "DEBUG: Customer3 Added: " << c3->getID() << endl;
    // ---- END CUSTOMER 3 ----
    // ---- CUSTOMER 4 ----
    fullName = "David Vita";
    priority = 4;

    Customer* c4 = myImplementation->addCustomer(fullName, priority);

    cout << "DEBUG: Customer4 Added: " << c4->getID() <<endl;
    // ---- END CUSTOMER 4 ----

    // ---- EMPLOYEE 0 ----
    int seniority = 1;
    int bYear = 1993;
    string employerID = "EID1234";
    Jobs job = MANAGER;

    Employee* emp0 = myImplementation->addEmployee(seniority, bYear, employerID, job);
    // ---- EMPLOYEE 0 ----

    // ---- EMPLOYEE 1 ----
    seniority = 2;
    bYear = 1990;
    employerID = "EID0";
    job = FLY_ATTENDANT;

    Employee* emp1 = myImplementation->addEmployee(seniority, bYear, employerID, job);
    cout << "DEBUG: Employee1 Added: " << emp1->getID() << endl;
    // ---- EMPLOYEE 1 ----

    // ---- EMPLOYEE 2 ----
    seniority = 93;
    bYear = 1880;
    employerID = "EID0";
    job = PILOT;

    Employee* emp2 = myImplementation->addEmployee(seniority, bYear, employerID, job);
    cout << "DEBUG: Employee2 Added: " << emp2->getID() << endl;
    // ---- EMPLOYEE 2 ----

    // ---- EMPLOYEE 3 ----
    seniority = 82;
    bYear = 1900;
    job = PILOT;
    employerID = "EID0";

    Employee* emp3 = myImplementation->addEmployee(seniority, bYear, employerID, job);
    cout << "DEBUG: Employee3 Added: " << emp3->getID() << endl;
    // ---- EMPLOYEE 3 ----

    // ---- EMPLOYEE 4 ----
    seniority = 50;
    bYear = 1940;
    job = NAVIGATOR;
    employerID = "EID2";

    Employee* emp4 = myImplementation->addEmployee(seniority, bYear, employerID, job);

    cout << "DEBUG: Employee4 Added: " << emp4->getID() << endl;
    // ---- EMPLOYEE 4 ----

    // ---- TEST DATES ----
    Date d = Date("1993-10-10");
    Date d1 = Date("1993-10-10");
    Date d2 = Date("1991-10-10");
    Date d3 = Date("1993-11-10");
    Date d4 = Date("1993-10-11");

    if(d == d1) cout << "DEBUG: DATE TEST 1 PASSED" << endl;
    if(d > d2) cout << "DEBUG: DATE TEST 2 PASSED" << endl;
    if(d < d3) cout << "DEBUG: DATE TEST 3 PASSED" << endl;
    if(d < d4) cout << "DEBUG: DATE TEST 4 PASSED" << endl;

    // ---- END TEST DATES ----

    Flight* f1 = myImplementation->addFlight(747, d, "israel", "metula");
    cout << "DEBUG: Flight Added: " << f1->getID() << endl;

    // ---- EMPLOYEE 5 ----
    seniority = 50;
    bYear = 1940;
    job = NAVIGATOR;
    employerID = "EID2";

    Employee* emp5 = myImplementation->addEmployee(seniority, bYear, employerID, job);

    cout << "DEBUG: Employee4 Added: " << emp5->getID() << endl;
    // ---- EMPLOYEE 5 ----

    // ---- EMPLOYEE 6 ----
    seniority = 50;
    bYear = 1940;
    job = PILOT;
    employerID = "EID2";

    Employee* emp6 = myImplementation->addEmployee(seniority, bYear, employerID, job);

    cout << "DEBUG: Employee4 Added: " << emp6->getID() << endl;
    // ---- EMPLOYEE 6 ----

    // ---- EMPLOYEE 7 ----
    seniority = 50;
    bYear = 1940;
    job = PILOT;
    employerID = "EID2";

    Employee* emp7 = myImplementation->addEmployee(seniority, bYear, employerID, job);

    cout << "DEBUG: Employee4 Added: " << emp7->getID() << endl;
    // ---- EMPLOYEE 7 ----

    // ---- EMPLOYEE 8 ----
    seniority = 50;
    bYear = 1940;
    job = FLY_ATTENDANT;
    employerID = "EID2";

    Employee* emp8 = myImplementation->addEmployee(seniority, bYear, employerID, job);

    cout << "DEBUG: Employee4 Added: " << emp8->getID() << endl;
    // ---- EMPLOYEE 8 ----

    // ---- EMPLOYEE 9 ----
    seniority = 2;
    bYear = 1990;
    employerID = "EID0";
    job = MANAGER;

    Employee* emp9 = myImplementation->addEmployee(seniority, bYear, employerID, job);
    cout << "DEBUG: Employee1 Added: " << emp9->getID() << endl;
    // ---- EMPLOYEE 9 ----

    Flight* f2 = myImplementation->addFlight(747, d, "israel", "metula");
    cout << "DEBUG: Flight Added: " << f2->getID() << endl;
    Flight* f3 = myImplementation->addFlight(747, d, "israel", "metula");
    cout << "DEBUG: Flight Added: " << f3->getID() << endl;

    //myImplementation->addResevation();
}