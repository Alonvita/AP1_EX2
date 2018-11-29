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
    auto it = this->flightsMap.find(id);

    if(it != this->flightsMap.end())
        return it->second;

    // else - try getting it from the file
    Flight* f = this->parseHandling.getFlightByFlightID(id);
    uploadFlight(f);
    return f;
}

/**
 * getCustomer(string id).
 *
 * @param id string -- a customer ID.
 * @return a pointer to the customer associated with this ID, or nullptr.
 */
Customer* MyImplementation::getCustomer(string id) {
    auto it = customersMap.find(id);

    if(it != customersMap.end())
        return it->second;

    Customer* cust = parseHandling.getCustomerByCustomerID(id);
    // UPLOAD
    uploadCustomer(cust);
    return cust;
}

/**
 * getPlane(string id).
 *
 * @param id string -- a plane ID.
 * @return a pointer to the plane associated with this ID, or nullptr;
 */
Plane* MyImplementation::getPlane(string id) {
    // for every model
    for(PAIR_FROM_PLANE_MAP p : availablePlanesTable) {
        // find look for the plane
        auto it = p.second.find(id);

        // if found -> return the Plane*
        if (it != p.second.end())
            return it->second;

    }

    // otherwise try loading from file
    Plane* plane = this->parseHandling.getPlaneByPlaneID(id);

    uploadPlane(plane);

    // return the plane
    return plane;
}

/**
 * getEmployee(string id).
 *
 * @param id string -- an employee ID.
 * @return a pointer to the employee associated with this ID, or nullptr;
 */
Employee* MyImplementation::getEmployee(string id) {
    // iterate over the items in the employeesMap per Job
    for(pair<Jobs, map<string,Employee*>> p : this->employeesMap) {

        // check if there's an employee with this ID in the maps
        map<string,Employee*> empsMap = p.second;

        auto it = empsMap.find(id);

        if(it != empsMap.end()) {
            return it->second;
        }
    }

    Employee* emp = parseHandling.getEmployeeByEmployeeID(id);
    // upload employee
    uploadEmployee(emp);
    return emp;
}

/**
 * getReservation(string id).
 *
 * @param id string -- a reservation ID.
 * @return a pointer to the reservation associated with this ID, or nullptr;
 */
Reservation* MyImplementation::getReservation(string id) {
    auto it = reservationsMap.find(id);

    if(it != reservationsMap.end())
        return it->second;

    Reservation* res = parseHandling.getReservationByReservationID(id);
    uploadReservation(res);

    return res;
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
    Descriptor desc = this->factory->giveCustomerDescriptor();
    Customer* newCustomer = new MyCustomer(desc, full_name, priority, reservations);

    this->customersMap.insert(make_pair(newCustomer->getID(), newCustomer));

    return newCustomer;
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
    Descriptor desc = this->factory->giveEmployeeDescriptor();
    Employee* newEmployee = new MyEmployee(desc, title, employer,seniority, birth_year);

    // make a pair
    string empID = newEmployee->getID();
    pair<string, Employee*> p = make_pair(empID, newEmployee);

    Jobs jobTitle = newEmployee->getTitle(); // local variable for the job title

    // check if map already contains a key of the same Job title
    auto it = this->employeesMap.find(jobTitle);
    if(it != this->employeesMap.end()) {
        // get the map
        map<string, Employee*> p1 = it->second;

        string tempID = newEmployee->getID();
        (it->second).insert(make_pair(tempID, newEmployee));

        return newEmployee;
    }

    // otherwise, create a new temp map
    map<string, Employee*> newMap;
    string tempID = newEmployee->getID();
    newMap.insert(make_pair(tempID, newEmployee)); // add ID->Employee

    // create new entry for Job->newMp
    this->employeesMap.insert(make_pair(jobTitle, newMap));

    return newEmployee;
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
    // search for an available plane
    Plane* plane = this->findAvailablePlaneInSystem(model_number, date);

    // in case no plane was found - throw an exception and return nullptr
    if(plane == nullptr) {
        throw runtime_error("There are no planes available for this flight. Try a different date or model...");
    }

    // --- GENERATE CREW ---
    map<Jobs, int> crewNeeded = plane->getCrewNeeded(); // local variable - needed crew for plane
    list<Employee*> employees = findCrewForFlight(crewNeeded, date); // get the crew
    if(employees.empty())
        throw runtime_error("Cannot find crew for this flight.");
    // --- GENERATE CREW ---

    // create a flight with an empty reservation list
    Descriptor desc = this->factory->giveFlightDescriptor();

    list<Reservation*> reservations;

    // --- GENERATE RESERVATIONS ---
    //reservations = generateReservationsForFlight(desc.getID());
    // --- GENERATE RESERVATIONS ---


    // add all reservations to the flight's reservations list
    Flight* newFlight = new MyFlight(desc, model_number, reservations, employees, date, source, destination, plane);

    // Add the new object to the flights list
    this->flightsMap.insert(make_pair(newFlight->getID(), newFlight));

    return newFlight;
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
    auto it = availablePlanesTable.find(model_number);

    // if exists ->
    if(it != availablePlanesTable.end()) {
        // get descriptor
        Descriptor desc = this->factory->givePlaneDescriptor();

        // create plane instance
        Plane* p = new MyPlane(desc, model_number, crew_needed, max_economy, max_first);

        // insert to the map<string, Plane*>
        it->second.insert(make_pair(p->getID(), p));

        return p;
    }

    // MODEL DOESN'T EXIST YET

    // get descriptor
    Descriptor desc = this->factory->givePlaneDescriptor();

    // create a new Plane
    Plane* newPlane = new MyPlane(desc, model_number, crew_needed, max_economy, max_first);

    // create the map
    map<string, Plane*> mapForModel;
    mapForModel.insert(make_pair(newPlane->getID(), newPlane));

    // push a new entry to the map<int, map<string, Plane*>>
    this->availablePlanesTable.insert(make_pair(model_number, mapForModel));

    return newPlane;
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

    // check if first class is full
    if(cls == FIRST_CLASS) {
        if (((MyFlight *) f)->isFirstClassFullyBooked())
            throw runtime_error("Flight's First Class is fully booked.");
    }

    // check if second class is full
    if(cls == SECOND_CLASS) {
        if (((MyFlight *) f)->isEconomyClassFullyBooked())
            throw runtime_error("Flight's Economy Class is fully booked.");
    }

    // create a new reservation
    Descriptor desc = this->factory->giveReservationDescriptor();
    Reservation* newReservation = new MyReservation(desc, customer, f, cls, max_baggage);

    // update Flight with the new reservation
    ((MyFlight*)f)->addReservation(newReservation);

    // update Customer with the new reservation
    ((MyCustomer*) customer)->addReservation(newReservation);

    this->reservationsMap.insert(make_pair(newReservation->getID(), newReservation));
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
    // look if there's an available vector for this model
    auto it = this->availablePlanesTable.find(model_number);
    if (it == this->availablePlanesTable.end())
        return nullptr;

    // for every plane in the vector found
    for (STRING_PLANE_MAP_PAIR spPair : it->second) {
        // false by default
        bool booked = false;

        //check if date is taken
        for (const Date &bookedDate : ((MyPlane*)spPair.second)->getBookedDates()) {
            // the date is booked -> mark as booked
            if (bookedDate == date)
                booked = true;
        }

        // not booked -> return the plane
        if (!booked) {
            MyPlane* mPlane = ((MyPlane*)spPair.second);
            // book the date
            mPlane->bookFlightOn(date);
            // return
            return mPlane;
        }
    }

    // No available planes were found, or model doesn't exist in the system
    return nullptr;
}

/**
 * findCrewForPlane(vector<Jobs> jobs).
 *
 * @param crewNeeded vector<Jobs, int> -- a vector of all the jobs needed
 *                                          to fill this plane with and the
 *                                          number of members for each job.
 * @param date Date -- the date that this crew is needed on.
 * @return a boolean true if a crew was found or false otherwise,
 *          followed by a list of Employees available as a crew for the plane.
 */
list<Employee*> MyImplementation::findCrewForFlight(map<Jobs, int> crewNeeded, Date date) {
    // Local Variables
    list<Employee*> crew;
    int sum = 0;

    // sum the amount of crew members needed
    for(pair<Jobs, int> job : crewNeeded) {
        sum += job.second;
    }

    // for every job needs to be found
    for(pair<Jobs, int> j : crewNeeded) {
        int membersFound = 0;
        int membersNeeded = j.second;

        auto it = this->employeesMap.find(j.first);
        if(it == this->employeesMap.end()) {
            // employee for job doesn't exist yet - return an empty list
            crew.clear();
            return crew;
        }

        // reaching here means that the job was found.
        // take the map for the job from the employeesMap
        map<string, Employee*> employeesPerJob = this->employeesMap.at(j.first);

        // for each pair in the map
        for(pair<string, Employee*> pair : employeesPerJob) {
            // if the employee is available on the date, add it to the vector
            if(isEmployeeAvailableOn(pair.first, date)) {
                crew.push_back(pair.second);

                // TODO: check if the ++ is on the right side:
                // TODO: need to increase BEFORE checking equality
                if(membersFound++ == membersNeeded) {
                    break; // enough members were found - break and look for next job
                }
            }
        }
    }

    // not enough members were found - clear vector to return an empty one
    if(crew.size() != sum) {
        crew.clear();
    }

    return crew;
}

/**
 * isEmployeeAvailableOn(Date date).
 *
 * @param date Date.
 * @return
 */
bool MyImplementation::isEmployeeAvailableOn(string& eid, Date date) {
    // get the flights that this employee is assigned ti
    vector<Flight*> flightsForEmployee = getFlightsForEmployee(eid);

    // no flights were found - that means that the employee must be available
    if(flightsForEmployee.empty()) {
        return true;
    }

    // flights were found -> for each flight found...
    for(Flight* f : flightsForEmployee) {
        // if the given date is equal to the flight date
        if((f->getDate() == date))
          return false; // return false -> employee is busy on the given date
    }

    // date was not found on the flights for this employee -> available on the given date
    return true;
}

/**
 * getFlightsForEmployee(string eid).
 *
 * @param eid string -- an employee id
 * @return a vector with all the flights associated to this employee.
 */
vector<Flight*> MyImplementation::getFlightsForEmployee(string& eid) {
    // Local Variables
    vector<Flight*> flightsAssociatedToEmployee;

    // foe every flight in the system
    for(pair<string, Flight*> flights : this->flightsMap) {
        // for every employee in the crew, check if he is assigned to this flight
        for(Employee* employee : flights.second->getAssignedCrew()) {
            // if one of the assignedCrew is this employee
            if(strcmp(employee->getID().c_str(), eid.c_str()) == 0) {
                // add it to the flight
                flightsAssociatedToEmployee.push_back(flights.second);
                break;
            }
        }
    }

    // TODO: need to check from file as well!

    // return the flights associated with the employee
    return flightsAssociatedToEmployee;
}

/**
 * generateReservationsForFlight(string fid).
 *
 * @param fid string -- a flight ID.
 * @return a list of reservations for this flight.
 */
list<Reservation*> MyImplementation::generateReservationsForFlight(string fid) {
    // local variables
    list<Reservation*> reservationsForFlight; // return value

    // for each reservation in the map
    for(pair<string, Reservation*> pair : this->reservationsMap) {
        // if the ID of the flight for this reservation equals to the fid
        if(strcmp(pair.second->getFlight()->getID().c_str(), fid.c_str())) {
            reservationsForFlight.push_back(pair.second); // add to reservation list
        }
    }

    // TODO: need to check from file as well!
    return reservationsForFlight;
}

/// ---------- "UPLOAD" FROM FILES ----------

/**
 * uploadFlight(Flight *).
 */
void MyImplementation::uploadFlight(Flight *f) {
    if(f == nullptr)
        return;

    this->flightsMap.insert(make_pair(f->getID(), f));
}

/**
 * uploadCustomer(Customer *).
 */
void MyImplementation::uploadCustomer(Customer * cust) {
    if(cust == nullptr)
        return;

    this->customersMap.insert(make_pair(cust->getID(), cust));
}

/**
 * uploadReservation(Reservation *)
 */
void MyImplementation::uploadReservation(Reservation * r) {
    if(r == nullptr)
        return;

    // add reservation
    this->reservationsMap.insert(make_pair(r->getID(), r));
}

/**
 * uploadEmployee(Employee *).
 */
void MyImplementation::uploadEmployee(Employee * emp) {
    if(emp == nullptr)
        return;

    //check if job exists
    auto it = this->employeesMap.find(emp->getTitle());

    // if exists -> add it under the job title
    if(it != this->employeesMap.end()) {
        it->second.insert(make_pair(emp->getID(), emp));
        return;
    }

    // otherwise, create a new map and put it nder the title
    map<string, Employee*> empMap;
    empMap.insert(make_pair(emp->getID(), emp));

    this->employeesMap.insert(make_pair(emp->getTitle(), empMap));
}

/**
 * uploadPlane(Plane *).
 */
void MyImplementation::uploadPlane(Plane * p) {
    if(p == nullptr)
        return;

    // check if model already exists
    auto it = this->availablePlanesTable.find(p->getModelNumber());

    // model exists -> add plane under model number
    if(it != this->availablePlanesTable.end()) {
        it->second.insert(make_pair(p->getID(), p));
        return;
    }

    // otherwise, create a new map and insert it under model number
    map<string, Plane*> newMap;
    newMap.insert(make_pair(p->getID(), p));

    this->availablePlanesTable.insert(make_pair(p->getModelNumber(), newMap));
}

/// ---------- EXIT ----------

/**
 * exit().
 */
void MyImplementation::exit() {
    parseHandling.parseFlightsToFile(flightsMap);
    parseHandling.parseEmployeesToFile(employeesMap);
    parseHandling.parseCustomersToFile(customersMap);
    parseHandling.parsePlanesToFile(availablePlanesTable);
    parseHandling.parseReservationsToFile(reservationsMap);
}