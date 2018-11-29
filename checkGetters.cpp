//
// Created by alon on 29/11/18.
//

#include "checkGetters.h"

int Test2() {
    auto *myImplementation = new MyImplementation();

    string pid0 = "PID0";
    string pid1 = "PID1";

    Plane* plane = myImplementation->getPlane(pid0);
    Plane* plane1 = myImplementation->getPlane(pid1);

    if(strcmp(plane->getID().c_str(), pid0.c_str()) == 0)
        cout << "getPlane worked for: " << plane->getID() << endl;
    if(strcmp(plane1->getID().c_str(), pid0.c_str()) == 0)
        cout << "getPlane worked for: " << plane1->getID() << endl;
}