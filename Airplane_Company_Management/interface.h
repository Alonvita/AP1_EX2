#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <list>
#include <string>

using namespace std;


enum Jobs { MANAGER, NAVIGATOR, FLY_ATTENDANT, PILOT, OTHER };
enum Classes {FIRST_CLASS, SECOND_CLASS};


class ID
{
public:
    virtual string getID() = 0;
};


class Employee;
class Plane;
class Flight;
class Customer;
class Reservation;
class Date;

class Employee : public ID {
public:
    virtual ~Employee(){}

    virtual Jobs        getTitle() = 0;
    virtual Employee*   getEmployer() = 0;
    virtual int         getSeniority() = 0;
    virtual int         getBirthYear() = 0;
};

class Plane : public ID {
public:
    virtual ~Plane(){}

    virtual map<Jobs, int>  getCrewNeeded() = 0;
    virtual int             getModelNumber() = 0;
    virtual int             getMaxFirstClass() = 0;
    virtual int             getMaxEconomyClass() = 0;
};

class Flight : public ID {
public:
    virtual int                 getModelNumber() = 0;
    virtual list<Reservation*>  getReservations() = 0;
    virtual list<Employee*>     getAssignedCrew() = 0;
    virtual Date                getDate() = 0;
    virtual string              getSource() = 0;
    virtual string              getDestination() = 0;
    virtual ~Flight(){}
};


class Customer : public ID {
public:
    virtual ~Customer(){}

    virtual string              getFullName() = 0;
    virtual int                 getPriority() = 0;
    virtual list<Reservation*>  getReservations() = 0;
};


class Reservation : public ID {
public:
    virtual ~Reservation(){}

    virtual Classes     getClass() = 0;
    virtual Flight*     getFlight() = 0;
    virtual Customer*   getCustomer() = 0;
    virtual int         getMaxBaggage() = 0;
};


class Date {
    string date;
public:
    Date(string date);    // format: YYYY-MM-DD

    string getDate(){ return date; }

    bool operator<(const Date& d) const;
    bool operator>(const Date& d) const;
    bool operator==(const Date& d) const;
};


class Ex2 {
public:
    virtual ~Ex2(){}

    /// ---------- GETTERS ----------
    virtual Plane*          getPlane(string id) = 0;
    virtual Flight*         getFlight(string id) = 0;
    virtual Customer*       getCustomer(string id) = 0;
    virtual Employee*       getEmployee(string id) = 0;
    virtual Reservation*    getReservation(string id) = 0;

    /// ---------- SETTERS ----------
    virtual Customer*       addCustomer(string full_name, int priority) = 0;
    virtual Employee*       addEmployee(int seniority, int birth_year,
                                        string employer_id, Jobs title) = 0;
    virtual Plane*          addPlane(int model_number,
                                     map<Jobs, int> crew_needed,
                                     map<Classes, int> max_passangers) = 0;
    virtual Flight*         addFlight(int model_number, Date date,
                                      string source, string destination) = 0;
    virtual Reservation*    addResevation(string customerId, string flightId,
                                          Classes cls, int max_baggage) = 0;

    virtual void exit() = 0;

};

#endif

