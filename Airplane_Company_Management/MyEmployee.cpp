//
// Created by alon_vita on 11/22/18.
//

#include "MyEmployee.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * MyEmployee(string ID, Job job, MyEmployee* employer = nullptr, int seniority, int birthYear).
 *
 * @param eid const string& -- a reference to a string representing an employee's ID
 * @param ID string -- an ID as string.
 * @param job Job -- a job.
 * @param employer Employer* -- an MyEmployee.
 * @param seniority int -- a seniority.
 * @param birthYear int -- a birth year.
 */
MyEmployee::MyEmployee(const string &eid, Jobs job, Employee *employer, int seniority, int year) {
    this->descriptor = Descriptor(eid);
    this->jobs = job;
    this->employer = employer;
    this->birthYear = birthYear;
    this->seniority = seniority;
}

/**
 * MyEmployee(string ID, Job job, MyEmployee* employer = nullptr, int seniority, int birthYear).
 *
 * @param factoryptr DescriptionFactory* -- a pointer to a DescriptionFactory.
 * @param ID string -- an ID as string.
 * @param job Job -- a job.
 * @param employer Employer* -- an MyEmployee.
 * @param seniority int -- a seniority.
 * @param birthYear int -- a birth year.
 */
MyEmployee::MyEmployee(DescriptorsFactory * factoryPtr, Jobs job,
                       Employee * employer, int seniority, int birthYear) {
    // Initialize Factory
    this->initializeID(factoryPtr);

    // Initialize the rest of the fields
    this->jobs = job;
    this->employer = employer;
    this->birthYear = birthYear;
    this->seniority = seniority;
}


/**
 * ~MyEmployee() Destructor.
 *
 *  Removes this->employer
 */
MyEmployee::~MyEmployee() {
    free(this->employer);
}

/// ---------- INITIALIZATION ----------
/**
 * initializeID(DescriptorsFactory * factory).
 *
 * @param factory DescriptorsFactory* -- a pointer to a descriptors factory
 */
void MyEmployee::initializeID(DescriptorsFactory * factory) {
    this->descriptor = factory->giveCustomerDescriptor();
}

/// ---------- GETTERS & SETTERS ----------
/**
 * MyEmployee::getBirthYear().
 *
 * @return this MyEmployee's birthday.
 */
int MyEmployee::getBirthYear() {
    return this->birthYear;
}

/**
 * MyEmployee::getEmployer().
 *
 * @return a reference to this MyEmployee's employer
 *
 */
Employee* MyEmployee::getEmployer() {
    return this->employer;
}

/**
 * MyEmployee::getID().
 *
 * @return the the ID held by the descriptor for this object.
 */
string MyEmployee::getID() {
    return this->descriptor.getID();
}

/**
 * MyEmployee::getSeniority().
 *
 * @return the seniority of this MyEmployee as int
 */
int MyEmployee::getSeniority() {
    return this->seniority;
}

/**
 * MyEmployee::getTitle().
 *
 * @return this employer's job
 */
Jobs MyEmployee::getTitle() {
    return this->jobs;
}