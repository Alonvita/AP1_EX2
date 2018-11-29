//
// Created by alon on 23/11/18.
//

#ifndef AP1_AIRPLANE_H
#define AP1_AIRPLANE_H

#include "interface.h"
#include "MyEmployee.h"
#include <map>

class MyPlane : public Plane {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    MyPlane(Descriptor& desc,
            int modelNumber,
            map<Jobs, int>& crewNeeded,
            int economyClassSize, int firstClassSize);
    ~MyPlane(){};

    /// ---------- GETTERS & SETTERS ----------
    vector<Date>    getBookedDates();
    bool            bookFlightOn(Date);
    void            setBookedDates(vector<Date>);

    // ---- OVERRIDING ----
    string          getID() override;
    map<Jobs, int>  getCrewNeeded() override;
    int             getModelNumber() override;
    int             getMaxFirstClass() override;
    int             getMaxEconomyClass() override;

private:
    Descriptor      descriptor;
    map<Jobs, int>  crewNeeded;
    int             modelNumber;
    vector<Date>    bookedDates;
    int             maxFirstClass;
    int             maxEconomyClass;
};

#endif //AP1_AIRPLANE_H
