//
// Created by alon on 25/11/18.
//

#include "MyImplementation.h"

/// ---------- CONSTRUCTORS -  DESTRUCTORS ----------
/**
 * MyImplementation().
 */
MyImplementation::MyImplementation() {
    this->factory = new DescriptorsFactory();
}

/// ---------- GETTERS ----------

/**
 * getFlight(string id).
 *
 * @param id string -- a flight ID.
 * @return a pointer to the flight associated with this ID, or nullptr;
 */
Flight* MyImplementation::getFlight(string id) {
    return (this->flightsMap.getItem(id));
    // TODO: need to check the files too
}

/**
 * getCustomer(string id).
 *
 * @param id string -- a customer ID.
 * @return a pointer to the customer associated with this ID, or nullptr;
 */
Customer* MyImplementation::getCustomer(string id) {
    return (this->customersMap.getItem(id));
    // TODO: need to check the files too
}

/**
 * getPlane(string id).
 *
 * @param id string -- a plane ID.
 * @return a pointer to the plane associated with this ID, or nullptr;
 */
Plane* MyImplementation::getPlane(string id) {
    // find a plane
    MyPlane* plane = (MyPlane*) this->planesMap.getItem(id);

    // TODO: need to check the files too
    return plane;
}

/**
 * getEmployee(string id).
 *
 * @param id string -- an employee ID.
 * @return a pointer to the employee associated with this ID, or nullptr;
 */
Employee* MyImplementation::getEmployee(string id) {
    return this->employeesMap.getItem(id);

    // TODO: need to check the files too
}

/**
 * getReservation(string id).
 *
 * @param id string -- a reservation ID.
 * @return a pointer to the reservation associated with this ID, or nullptr;
 */
Reservation* MyImplementation::getReservation(string id) {
    return (this->reservationsMap.getItem(id));

    // TODO: need to check the files too
}

/// ---------- SETTERS ----------
/**
 * addCustomer(string full_name, int priority).
 *
 * @param full_name stine -- the customer's name.
 * @param priority int -- the customer's priority
 *
 * @return a new customer ptr.
 */
Customer* MyImplementation::addCustomer(string full_name, int priority) {
    list<Reservation*> reservations;

    // create a new object
    Customer* newCustomer = new MyCustomer(this->factory, full_name, priority, reservations);

    this->customersMap.addItem(newCustomer->getID(), newCustomer);
}

/**
 * addEmployee(int seniority, int birth_year, string employer_id, Jobs title).
 *
 * @param seniority int -- the seniority of the employee.
 * @param birth_year int -- the year of birth of the employee.
 * @param employer_id string -- the ID of the employer.
 * @param title Job -- the job title of this employee.
 *
 * @return a new employee ptr.
 */
Employee* MyImplementation::addEmployee(int seniority, int birth_year, string employer_id, Jobs title) {
    // fetch the employer
    Employee* employer = this->getEmployee(employer_id);

    // create a new MyEmployee object
    Employee* newEmployee = new MyEmployee(this->factory, title, employer,seniority, birth_year);

    // make a pair
    pair<string, Employee*> p = make_pair(newEmployee->getID(), newEmployee);

    // check if Job description already exists

    // TODO: check if the map inside the map is actually a good idea -
    // TODO: the insertion made here is wrong because it doesn't check if the Job title already exists
    // TODO: in the map
    map<string, Employee*> tempMap;
    tempMap.insert(p);

    this->employeesMap.addItem(newEmployee->getTitle(), tempMap);
}

/**
 * addFlight(int model_number, Date date, string source, string destination).
 *
 * @param model_number int -- the model number of the airplane for this flight.
 * @param date Date -- the date of the flight.
 * @param source string -- source of the flight.
 * @param destination string -- destination of the flight
 *
 * @return a new Flight ptr.
 */
Flight* MyImplementation::addFlight(int model_number, Date date, string source, string destination) {
    list<Reservation*> reservations; // TODO: fill with reservations for this flight (?)
    list<Employee*> employees; // TODO: fill this with employees

    // search for an available plane
    Plane* plane = this->findAvailablePlaneInSystem(model_number, date);

    // in case no plane was found - throw an exception and return nullptr
    if(plane == nullptr) {
        throw runtime_error("There are no planes available for this flight. Try a different date or model...");
    }

    // TODO: After finding a plane, we will have to check the crew needed for this Plane and look
    // TODO:  for the crew members in the employees list. Should no crew be available, throw

    // An available plane was found -> create the flight.
    Flight* newFlight =
            new MyFlight(this->factory, model_number,
                         reservations, employees, date,
                         source, destination, plane);

    // Add the new object to the flights list
    this->flightsMap.addItem(newFlight->getID(), newFlight);
}

/**
 * addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers).
 *
 * @param model_number int -- the model of the plane.
 * @param crew_needed map<Jobs,int> -- a map of all the job titles and number of employees for each job
 *                                      needed for this plane.
 * @param max_passangers map<Classes, int> -- the number of max passengers for each class.
 *
 * @return a new Plane ptr.
 */
Plane* MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed, map<Classes, int> max_passangers) {
    // Local Variables
    int max_first = max_passangers.at(FIRST_CLASS);
    int max_economy = max_passangers.at(SECOND_CLASS);

    // search if the plane model is already in the system
    for(pair<int, int> p : this->availablePlanesCounter) {
        if(p.first == model_number) {
            // if so - increase the counter
            this->availablePlanesCounter.at(model_number)++;
        }
    }

    // otherwise, create a new Plane* and a new map entry

    // create a new instance of the object
    Plane* newPlane = new MyPlane(this->factory, model_number, crew_needed, max_economy, max_first);

    // map entry for counter + 1
    this->availablePlanesCounter.insert(pair<int, int>(model_number, 1));

    // add the new object to the planes list
    this->planesMap.addItem(newPlane->getID(), newPlane);
}

/**
 * addResevation(string customerId, string flightId, Classes cls, int max_baggage).
 *
 * @param customerId string -- the customer ID which this reservation is referes to.
 * @param flightId string -- the flight ID which this reservation is referes to.
 * @param cls Classes -- the classes ordered with this reservation.
 * @param max_baggage int -- the max baggage weight allowed in this reservation.
 *
 * @return a new Reservation ptr.
 */
Reservation* MyImplementation::addResevation(string customerId, string flightId, Classes cls, int max_baggage) {
    // get customer
    Customer* customer = this->getCustomer(customerId);
    // check exists
    if(customer == nullptr)
        throw runtime_error("Customer doesn't exist.");

    // get flight
    Flight* f = this->getFlight(flightId);
    // check exists
    if(f == nullptr)
        throw runtime_error("Flight doesn't exist.");

    // create a new reservation
    Reservation* newReservation = new MyReservation(this->factory,
                                                    customer,
                                                    f, cls, max_baggage);

    // update Flight with the new reservation
    ((MyFlight*)f)->addReservation(newReservation);

    // update Customer with the new reservation
    ((MyCustomer*) customer)->addReservation(newReservation);

    this->reservationsMap.addItem(newReservation->getID(), newReservation);
}

/// ---------- UTILITY FUNCTIONS ----------

/**
 * findAvailablePlaneInSystem(int model_number, Date date).
 *
 * @param model_number int -- a model number.
 * @param date Date -- a date
 * @return Plane ptr if an available plane was found for this date.
 */
Plane* MyImplementation::findAvailablePlaneInSystem(int model_number, Date date) {
    bool booked = false;

    // look if there's an available plane for this model number
    if(this->availablePlanesCounter.find(model_number) == this->availablePlanesCounter.end())
        return nullptr;

    // iterate over the map
    for(pair<string, Plane*> p : this->planesMap) {
        MyPlane* plane = ((MyPlane *) p.second);

        // check every plane model
        if (plane->getModelNumber() == model_number) {
            // plane was found -> check the dates
            for (const Date& bookedDate : plane->getBookedDates()) {
                // the date is booked -> mark as booked
                if (bookedDate == date)
                    booked = true;
            }

            // if not booked, return the plane
            if (!booked)
                return plane;
        }
    }

    // No available planes were found, or model doesn't exist in the system
    return nullptr;
}

/**
 * findCrewForPlane(vector<Jobs> jobs).
 *
 * @param jobs vector<Jobs> -- a vector of all the jobs needed to fill this plane with.
 * @return a boolean true if a crew was found or false otherwise,
 *          followed by a list of Employees available as a crew for the plane.
 */
 template <class T>
vector<T> MyImplementation::findCrewForPlane(vector<Jobs> jobs) {
    // Local Variables
    vector<T> crew;

    // push default as crew not found
    crew.push_back(false);

    for(Jobs j : jobs) {
        Employee* employee =
    }
}

/// ---------- EXIT ----------

void MyImplementation::exit() {}