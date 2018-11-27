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
    return (this->planesMap.getItem(id));

    // TODO: need to check the files too
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

    this->employeesMap.addItem(newEmployee->getID(), newEmployee);
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
        throw runtime_error("There are no planes available for this flight. Try changing the date or model...");
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

    // create a new instance of the object
    Plane* newPlane = new MyPlane(this->factory, model_number, crew_needed, max_economy, max_first);

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
    Reservation* newReservation = new MyReservation(
                                    this->factory,
                                    this->getCustomer(customerId),
                                    this->getFlight(flightId),
                                    cls, max_baggage);

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

    // iterate over the map
    for(pair<string, Plane*> p : this->planesMap) {
        MyPlane *plane = ((MyPlane *) p.second);

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

/// ---------- EXIT ----------

void MyImplementation::exit() {
}