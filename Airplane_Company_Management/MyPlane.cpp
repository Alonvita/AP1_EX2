//
// Created by alon on 23/11/18.
//

#include "MyPlane.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * MyPlane(Descriptor& desc,
                 int modelNumber,
                 map<Jobs, int>& crewNeeded,
                 int economyClassSize, int firstClassSize).
 *
 * @param desc Descriptor& -- a reference to a plane descriptor.
 * @param ID string -- the id of this specific MyPlane.
 * @param modelNumber int -- the model of the MyPlane.
 * @param crewNeeded map<Jobs, int> -- the jobs required on this airMyPlane.
 * @param economyClassSize int -- the max seats in Economy Class.
 * @param firstClassSize int -- the max seats in First Class.
 */
MyPlane::MyPlane(Descriptor& desc,
                 int modelNumber,
                 map<Jobs, int>& crewNeeded,
                 int economyClassSize, int firstClassSize) {
    /// Initialize the rest of the fields
    this->descriptor = desc;
    this->crewNeeded = crewNeeded;
    this->modelNumber = modelNumber;
    this->maxFirstClass = firstClassSize;
    this->maxEconomyClass = economyClassSize;
}


/// ---------- GETTERS & SETTERS ----------

/**
 * setFlightDate(Date flightDate).
 *
 * @param flightDate Date -- a flight date that this Plane will be used on.
 * @return true if the date was added, or false if it is already booked.
 */
bool MyPlane::bookFlightOn(Date flightDate) {
    for(Date bookedDate : this->bookedDates) {
        if(flightDate == bookedDate)
            return false;
    }

    this->bookedDates.push_back(flightDate);
    return true;
}

/**
 * setBookedDates(vector<Date>).
 */
void MyPlane::setBookedDates(vector<Date> datesVec) {
    this->bookedDates = datesVec;
}

/**
 * getBookedDates().
 *
 * @return a vector<Date> of all the booked dates for this plane
 */
vector<Date> MyPlane::getBookedDates() {
    return this->bookedDates;
}

/**
 * MyPlane::getID();
 *
 * @return the id of this specific MyPlane.
 */
string MyPlane::getID() { return this->descriptor.getID(); }

/**
 * MyPlane::getCrewNeeded().
 *
 * @return all of the jobs needed on this model.
 */
map<Jobs, int> MyPlane::getCrewNeeded() { return this->crewNeeded; }

/**
 * MyPlane::getMaxEconomyClass()
 *
 * @return the max number of passengers in Economy Class for this model.
 */
int MyPlane::getMaxEconomyClass() { return this->maxEconomyClass; }

/**
 * MyPlane::getMaxFirstClass().
 *
 * @return the max number of passengers in First Class for this model.
 */
int MyPlane::getMaxFirstClass() { return this->maxFirstClass; }

/**
 * getModelNumber().
 *
 * @return the model number of this MyPlane.
 */
int MyPlane::getModelNumber() { return this->modelNumber; }