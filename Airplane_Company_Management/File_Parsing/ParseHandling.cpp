//
// Created by alon on 27/11/18.
//

#include "ParseHandling.h"
#include "../MyReservation.h"
#include "../MyCustomer.h"
#include "../MyFlight.h"
#include "../MyPlane.h"

///---------- FROM FILE PARSE HANDLING ----------
/**
 * generate(Parse target, const string& searcherID).
 *
 * @param target Parse -- the parse of required item
 * @param searcherID const string& -- the id to search by
 * @return a template <class T>
 */
template <class T>
T ParseHandling::generateSingle(SingleParse target, const string& searcherID) {
    T obj;
    SingleParse searcherType;

    // open the right file, based on what we want to search
    switch (target) {
        case FLIGHT:
            return getFlightByFlightID(searcherID);
        case RESERVATION:
            return getReservationByReservationID(searcherID);
        case CUSTOMER:
            return getCustomerByCustomerID(searcherID);
        case EMPLOYEE:
            // search for a single employee
            return getEmployeeByEmployeeID(searcherID);
        case PLANE:
            // extract searcherType
            searcherType = identifyID(searcherID);

            // get plane by plane ID
            if(searcherType == PLANE) {
                return getPlaneByPlaneID(searcherID);
            }

            // get plane by flight ID
            if(searcherType == FLIGHT) {
                return getPlaneByFlightID(searcherID);
            } else {
                throw runtime_error("Unknown target - searcherID combination.");
            }
        default:
            throw runtime_error("Unknown target type.");
    }

}

/**
 * generateMultiple(MultipleParse target, const string& searcherID).
 *
 * @param target MultipleParse -- an enum representing the type of item to look for.
 * @param searcherID const string& -- id to search by.
 *
 * @return a vector of all occurences in the file
 */
template <class T>
vector<T> ParseHandling::generateMultiple(MultipleParse target, const string& searcherID) {
    SingleParse searcherType;

    switch (target) {
        case RESERVATIONS:
            searcherType = identifyID(searcherID);
            if(searcherType == FLIGHT)
                return generateReservationsByFlightID(searcherID);

            if(searcherType == CUSTOMER)
                return generateReservationsByCustomerID(searcherID);

        case EMPLOYEES:
            return generateEmployeesByFlightID(searcherID);

        case JOBS:
            return parseJobFromString(searcherID);
    }
}

///---------- GENERATE SINGLES FUNCTIONS ----------
/**
 * getReservationFromFile(const string& rid).
 *
 * @param rid const string& -- reservation ID.
 * @return a new Reservation(...) object generated from file for this ID.
 */
Reservation* ParseHandling::getReservationByReservationID(const string &rid) {
    if(!fileExists(RESERVATIONS_FP))
        return nullptr;

    // Local Variables
    ifstream file(RESERVATIONS_FP);
    vector<string> vec;

    string l;
    // for each line
    while(getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if the ID of the reservation is equal to this reservation
        if(strcmp(splitLine.at(0).c_str(), rid.c_str()) == 0) {
            // get relevant Customer and Flight, parse Class and convert maxBaggage to int.
            MyCustomer* customer = ((MyCustomer*)getCustomerByCustomerID(splitLine.at(1)));
            MyFlight* flight = ((MyFlight*)getPlaneByFlightID(splitLine.at(2)));
            Classes cls = parseStringToClass(splitLine.at(3));
            int maxBaggage = stoi(splitLine.at(4));


            // create a new reservation and return
            Descriptor desc = Descriptor(rid);
            return new MyReservation(desc, customer, flight, cls, maxBaggage);
        }
    }
}

/**
 * getCustomerByCustomerID(const string& cid).
 *
 * @param cid const string& -- a reference to a customer ID.
 * @return a Customer ptr.
 */
Customer* ParseHandling::getCustomerByCustomerID(const string& cid) {
    if(!fileExists(CUSTOMER_FP))
        return nullptr;

    // Local Variables
    Line line;
    ifstream file(CUSTOMER_FP);
    vector<string> vec;

    string l;
    // for each line
    while(getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // create a new Customer
        Descriptor desc = Descriptor(cid);

        // add all reservations found associated with this customer
        list<Reservation*> rList = this->generateReservationsByCustomerID(cid);

        // get full name
        stringstream fullName;
        fullName << splitLine.at(1);
        fullName << SPACE;
        fullName << splitLine.at(2);

        string name = fullName.str();

        auto customer = new MyCustomer(desc, name, stoi(splitLine.at(3)), rList);
    }
}

/**
 * getPlaneByFlightID(const string &fid).
 *
 * @param fid const string& -- a reference to a constant string flight ID
 * @return a a Plane ptr that is associated with this flight.
 */
Plane* ParseHandling::getPlaneByFlightID(const string &fid) {
    if(!fileExists(FLIGHTS_FP))
        return nullptr;

    // Local Variables
    ifstream file(FLIGHTS_FP);
    vector<string> vec;
    string pid;

    string l;
    // for each line
    while(getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if fid == this flights's id...
        if(strcmp(splitLine.at(0).c_str(), fid.c_str()) == 0) {
            // take the plane ID
            pid = splitLine.at(1);
            break; // found -> break
        }
    }

    // no such flight was found -> return nullptr
    if(pid.empty())
        return nullptr;

    // otherwise, get get the plane with it's ID
    return getPlaneByPlaneID(pid);
}

/**
 * getPlaneByPlaneID(const string &pid).
 *
 * @param pid const sting& -- const reference to a plane ID
 * @return a new instance of the relevant plane parsed from the file, or nullptr if doesn't exist
 */
Plane* ParseHandling::getPlaneByPlaneID(const string &pid) {
    if(!fileExists(PLANES_FP))
        return nullptr;

    // Local Variables
    ifstream planesFile(PLANES_FP);
    vector<string> vec;

    string l;
    // for each line
    while(getline(planesFile, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if ID was found
        if(strcmp(pid.c_str(), splitLine.at(0).c_str()) == 0) {
            int modelNumber = stoi(splitLine.at(1));
            // parse the crew needed for this model
            map<Jobs, int> crewNeeded = parseCrewNeededForPlane(modelNumber);
            int maxFirst = stoi(splitLine.at(2)); // get max first size
            int maxEconomy = stoi(splitLine.at(3)); // get max economy size

            Descriptor desc = Descriptor(pid);
            return new MyPlane(desc, modelNumber, crewNeeded, maxEconomy, maxFirst);
        }
    }

    // no ID matching the required ID was found -> return nullptr.
    return nullptr;
}

/**
 * getEmployeeByEmployeeID(const string &eid).
 *
 * @param eid const string& -- a reference to an employee ID.
 * @return an Employee ptr or nullptr if none exists.
 */
Employee* ParseHandling::getEmployeeByEmployeeID(const string &eid) {
    if(!fileExists(EMPLOYEE_FP))
        return nullptr;

    // Local Variables
    ifstream file(EMPLOYEE_FP);
    vector<string> vec;

    string l;
    // for each line
    while(getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if employee found
        if(strcmp(splitLine.at(0).c_str(), eid.c_str()) == 0) {
            // Gather relevant information
            Jobs jobTitle = this->parseJobFromString(splitLine.at(1)); // Parse Job
            int seniority = stoi(splitLine.at(2)); // Seniority
            int bYear = stoi(splitLine.at(3)); // Birth Year

            // get employee or pur nullptr
            Employee* employer =
                    strcmp(splitLine.at(4).c_str(), "NONE") == 0 ? nullptr :
                    getEmployeeByEmployeeID(splitLine.at(4)); // Look for Employer

            // return a new instance of the relevant employee
            Descriptor desc = Descriptor(eid);
            return new MyEmployee(desc, jobTitle, employer, seniority, bYear);
        }
    }

    // none was found - return null ptr
    return nullptr;
}

/**
 * getFlightByFlightID(const string &fid).
 *
 * @param fid const string& -- a constant reference to a Flight ID.
 * @return a new Flight generated from the files.
 */
Flight* ParseHandling::getFlightByFlightID(const string &fid) {
    if(!fileExists(FLIGHTS_FP))
        return nullptr;

    // Local Variables
    ifstream flightsF(FLIGHTS_FP);
    vector<string> vec;
    list<Employee *> employeesForThisFlight;

    string l;
    // for each line
    while (getline(flightsF, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if Flight ID was found
        if (strcmp(fid.c_str(), splitLine.at(0).c_str()) == 0) {
            // generate relevant information
            Descriptor desc = Descriptor(fid); // FLIGHT ID
            string pid = splitLine.at(1); // PLANE ID -> get plane below
            int modelNum = stoi(splitLine.at(2)); // MODEL NUMBER
            Date date = splitLine.at(3);     // FLIGHT DATE
            string src = splitLine.at(4);    // SOURCE
            string dest = splitLine.at(5);   // DESTINATION

            list<Reservation*> rList = generateReservationsByFlightID(fid);
            list<Employee*> eList = generateEmployeesByFlightID(fid);
            Plane* p = getPlaneByFlightID(fid);

            if(p == nullptr)
                throw runtime_error("There is no plane associated with this flight.");

            return new MyFlight(desc, modelNum, rList, eList, date, src, dest, p);
        }
    }

    // no flight was found -> return nullptr;
    return nullptr;
}

///---------- GENERATE MULTIPLE FUNCTIONS ----------

/**
 * generateEmployeesByFlightID(const string &fid).
 *
 * @param fid const string& -- a constant reference to a Flight ID.
 * @return a list of employees associated to this flight.
 */
list<Employee*> ParseHandling::generateEmployeesByFlightID(const string &fid) {
    // Local Variables
    ifstream planesFile(ASSIGNMENTS_FILE);
    vector<string> vec;
    list<Employee *> employeesForThisFlight;

    string l;
    // for each line
    while (getline(planesFile, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // if Flight ID was found
        if (strcmp(fid.c_str(), splitLine.at(0).c_str()) == 0) {
            // generate the employee from the employees file
            Employee *tempE = getEmployeeByEmployeeID(splitLine.at(1));

            employeesForThisFlight.push_back(tempE);
        }
    }

    // return the generated list.
    return employeesForThisFlight;
}

/**
 * generateReservationsByCustomerID(const string &cid).
 *
 * @param cid const string& -- a constant reference to a Customer ID.
 * @return a list of reservations associated to this cutomer.
 */
list<Reservation*> ParseHandling::generateReservationsByCustomerID(const string &cid) {
    // Local Variables
    ifstream planesFile(RESERVATIONS_FP);
    vector<string> vec;
    list<Reservation*> reservationsForCustomer;

    string l;
    // for each line
    while (getline(planesFile, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // check if the Customer ID on this reservation is equal to cid
        string cidForRes = splitLine.at(1);
        if (strcmp(cid.c_str(), cidForRes.c_str()) == 0) {
            // if so, get all relevant information
            Descriptor desc = Descriptor(splitLine.at(0));
            Customer* customer = getCustomerByCustomerID(cid);
            Flight* flight = getFlightByFlightID(splitLine.at(2));
            Classes cls = parseStringToClass(splitLine.at(3));
            int maxBaggage = stoi(splitLine.at(4));

            // create the new class and push it into the list
            reservationsForCustomer.push_back(
                    new MyReservation(desc, customer,flight, cls, maxBaggage));
        }
    }
}

/**
 * generateReservationsByFlightID(const string &fid).
 *
 * @param fid cost string& -- a constant reference to a Flight ID.
 * @return a list of reservations associated with this flight.
 */
list<Reservation*> ParseHandling::generateReservationsByFlightID(const string &fid) {
    // Local Variables
    ifstream planesFile(RESERVATIONS_FP);
    vector<string> vec;
    list<Reservation *> reservationsForFlight;

    string l;
    // for each line
    while (getline(planesFile, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // check if the Flight ID on this reservation is equal to fid
        string cidForRes = splitLine.at(2);
        if (strcmp(fid.c_str(), cidForRes.c_str()) == 0) {
            // if so, gather all relevant information
            // if so, get all relevant information
            Descriptor desc = Descriptor(splitLine.at(0));
            Customer *customer = getCustomerByCustomerID(splitLine.at(1));
            Flight *flight = getFlightByFlightID(fid);
            Classes cls = parseStringToClass(splitLine.at(3));
            int maxBaggage = stoi(splitLine.at(4));

            // create the new class and push it into the list
            reservationsForFlight.push_back(
                    new MyReservation(desc, customer, flight, cls, maxBaggage));
        }
    }
}

/**
 * parseCrewNeededForPlane(int modelID).
 *
 * @param modelID int -- the model of the plane
 * @return
 */
map<Jobs, int> ParseHandling::parseCrewNeededForPlane(int model) {
    // Local Variables
    ifstream file(MODELS_FP);
    vector<string> vec;

    // initialize crewNeeded map
    map<Jobs, int> crewNeeded;

    auto it = vec.begin();

    string l;
    // for each line
    while(getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());
        // MODEL
        if (strcmp(splitLine.at(0).c_str(), "MODEL") == 0) {
            // check number
            if(stoi(splitLine.at(1)) == model) {
                // get next line
                // iterate over all lines that hold JOB [NUMBER] (until meeting the next MODEL)
                while(getline(file, l)) {

                    // get the iss of the current row
                    istringstream iss1(l);

                    // split to vector
                    vector<string> splitEmpLine(
                            istream_iterator<string>{iss1},
                            istream_iterator<string>());

                    // reached next MODEL -> break
                    if(strcmp(splitEmpLine.at(0).c_str(), "MODEL") == 0)
                        break;

                    // parse the Job and convert the amount of assignedCrew needed for the job
                    Jobs parsedJob = parseJobFromString(splitEmpLine.at(0));
                    int employeesNeeded = stoi(splitEmpLine.at(1));

                    // add new entry to the map
                    crewNeeded.insert(make_pair(parsedJob, employeesNeeded));
                }
                // reaching here means that a crew was filled in the map - return it
                return crewNeeded;
            }
        }
    }

    // map will be empty should we reach here
    throw runtime_error("This model does not exist in our system.");
}


///---------- PARSE TO FILE ----------
/**
 * parseEmployeesToFile(map<Jobs, map<string, Employee *>> employeesMap).
 *
 * @param employeesMap map<Jobs, map<string, Employee *>> -- map of employees
 */
void ParseHandling::parseEmployeesToFile(map<Jobs, map<string, Employee *>> employeesMap) {

    for (pair<Jobs, map<string, Employee *>> p : employeesMap) {
        Jobs job = p.first;
        for (pair<string, Employee *> p2 : p.second) {
            // check if employee exists already
            if(existsByID(p2.first, EMPLOYEE_FP))
                continue;

            stringstream ss;
            // get all relevant detains for this employee
            string id = p2.first;

            // get employer
            Employee *employer = p2.second->getEmployer();
            // employerID
            string employerID = (employer != nullptr) ? employer->getID() : "NONE";

            int seniority = p2.second->getSeniority();
            int bYear = p2.second->getBirthYear();

            ss << id; // ID
            ss << SPACE;
            ss << parseJobToString(job); // JOB TITLE
            ss << SPACE;
            ss << seniority; // SENIORITY
            ss << SPACE;
            ss << bYear; // BIRTH YEAR
            ss << SPACE;
            ss << employerID; // EMLOYER ID
            ss << endl;

            writeStrToFile(ss.str(), EMPLOYEE_FP);
            ss.clear();
        }
    }
}

/**
 * parseCustomersToFile(map<string, Customer *> customersMap).
 *
 * @param customersMap map<string, Customer *> -- customers map.
 */
void ParseHandling::parseCustomersToFile(map<string, Customer *> customersMap) {

    for(pair<string, Customer*> p : customersMap) {
        // check if customer exists already
        if(existsByID(p.first, CUSTOMER_FP))
            continue;

        stringstream ss;
        ss << p.first; // ID
        ss << SPACE;
        ss << p.second->getFullName(); // FULL_NAME
        ss << SPACE;
        ss << p.second->getPriority(); // PRIORITY
        ss << endl; // ENDLINE

        writeStrToFile(ss.str(), CUSTOMER_FP);
    }
}

/**
 * parseFlightsToFile(map<string, Flight *> flightsMap).
 *
 * @param flightsMap map<string, Flight *> -- a flights map.
 */
void ParseHandling::parseFlightsToFile(map<string, Flight *> flightsMap) {

    for(pair<string, Flight*> p : flightsMap) {
        stringstream ssFlight;
        stringstream ssAssign;

        // check if employee exists already
        if(existsByID(p.first, FLIGHTS_FP))
            continue;

        ssFlight << p.first; // ID
        ssFlight << SPACE;
        ssFlight << ((MyFlight*)p.second)->getPlane()->getID(); // PLANE ID
        ssFlight << SPACE;
        ssFlight << p.second->getModelNumber(); // MODEL NUMBER
        ssFlight << SPACE;
        ssFlight << p.second->getDate().getDate(); // DATE TO STRING
        ssFlight << SPACE;
        ssFlight << p.second->getSource();
        ssFlight << SPACE;
        ssFlight << p.second->getDestination();
        ssFlight << endl;

        for(Employee* emp : p.second->getAssignedCrew()) {
            ssAssign << p.first; // PLANE ID
            ssAssign << SPACE;
            ssAssign << emp->getID(); // EMPLOYEE ID
            ssAssign << endl;
        }

        writeStrToFile(ssAssign.str(), ASSIGNMENTS_FILE); // write employees to Assignments.txt
        writeStrToFile(ssFlight.str(), FLIGHTS_FP); // write flight to Flights.txt
        ssAssign.clear(); // TODO: CHECK THAT ACTUALLY CLEARS THE SS
    }
}

/**
 * parsePlanesToFile(map<int, map<string, Plane *>> planesMap).
 *
 * @param planesMap map<int, map<string, Plane *>> -- planes map.
 */
void ParseHandling::parsePlanesToFile(map<int, map<string, Plane *>> planesMap) {

    for (pair<int, map<string, Plane*>> mapP : planesMap) {
        for(pair<string, Plane*> p : mapP.second) {
            // check if employee exists already
            if(existsByID(p.first, PLANES_FP))
                continue;

            stringstream ss;
            ss << p.first; // ID
            ss << SPACE;
            ss << p.second->getModelNumber(); // MODEL NUMBER
            ss << SPACE;
            ss << p.second->getMaxFirstClass(); // MAX FIRST
            ss << SPACE;
            ss << p.second->getMaxEconomyClass(); // MAX ECONOMY
            ss << endl;

            // if model doesn't exist -> write it.
            if(!modelAlreadyExists(p.second->getModelNumber())) {
                stringstream ssJob;
                ssJob << "MODEL";
                ssJob << SPACE;
                ssJob << p.second->getModelNumber();
                ssJob << endl;
                for (pair<Jobs, int> job : p.second->getCrewNeeded()) {
                    ssJob << parseJobToString(job.first);
                    ssJob << SPACE;
                    ssJob << job.second;
                    ssJob << endl;
                }
                // write crew needed
                writeStrToFile(ssJob.str(), MODELS_FP);
            }

            parseDatesVectorToFile(p.second->getID(),
                    ((MyPlane*)p.second)->getBookedDates());

            // wire plane
            writeStrToFile(ss.str(), PLANES_FP);
        }
    }
}

/**
 * parseReservationsToFile(map<string, Reservation *> reservationsMap).
 *
 * @param reservationsMap map<string, Reservation *> -- reservations map.
 */
void ParseHandling::parseReservationsToFile(map<string, Reservation *> reservationsMap) {

    for(pair<string, Reservation *> p : reservationsMap) {
        stringstream ss;
        // check if employee exists already
        if(existsByID(p.first, RESERVATIONS_FP))
            continue;

        ss << p.first; // ID
        ss << SPACE;
        ss << p.second->getCustomer()->getID(); // CUSTOMER ID
        ss << SPACE;
        ss << p.second->getFlight()->getID(); // FLIGHT ID
        ss << SPACE;
        ss << parseClassToStr(p.second->getClass());// CLASS
        ss << SPACE;
        ss << p.second->getMaxBaggage(); // MAX BAGGAGE
        ss << endl;

        writeStrToFile(ss.str(), RESERVATIONS_FP);
    }
}

///---------- UTILITY ----------
/**
 * identifyID(const string& id).
 *
 * @param id const string& -- a string representing an ID
 * @return the type of ID, determined by the 3 first digits of it.
 */
SingleParse ParseHandling::identifyID(const string& id) {
    // identifier <- 3 letters from position 0
    string identifier = id.substr(0, 3);

    if(strcmp(identifier.c_str(), PLANE_STR_IDENTIFIER) == 0) {
        return PLANE;
    }

    if(strcmp(identifier.c_str(), CUSTOMER_STR_IDENTIFIER) == 0) {
        return CUSTOMER;
    }

    if(strcmp(identifier.c_str(), FLIGHT_STR_IDENTIFIER) == 0) {
        return FLIGHT;
    }

    if(strcmp(identifier.c_str(), EMPLOYEE_STR_IDENTIFIER) == 0) {
        return EMPLOYEE;
    }

    if(strcmp(identifier.c_str(), RESERVATION_STR_IDENTIFIER) == 0) {
        return RESERVATION;
    }

    throw runtime_error("Unknown ID.");
}

/**
 * parseStringToClass(const string& &cls).
 *
 * @param cls const string& -- a string representing a class
 * @return the relevant Classes (enum) type.
 */
Classes ParseHandling::parseStringToClass(const string& cls) {
    if(strcmp(cls.c_str(), "FIRST_CLASS") == 0)
        return FIRST_CLASS;
    if(strcmp(cls.c_str(), "SECOND_CLASS") == 0)
        return SECOND_CLASS;

    throw runtime_error("Error parsing class from file");
}

/**
 * parseJobFromString(const string& jobStr).
 *
 * @param jobStr cosnt string& -- a constant string.
 * @return the relevant Job from Jobs (enum)
 */
Jobs ParseHandling::parseJobFromString(const string& jobStr) {
    // Jobs: MANAGER, NAVIGATOR, FLY_ATTENDANT, PILOT, OTHER
    if(strcmp(jobStr.c_str(), "MANAGER") == 0)
        return MANAGER;
    if(strcmp(jobStr.c_str(), "PILOT") == 0)
        return PILOT;
    if(strcmp(jobStr.c_str(), "FLY_ATTENDANT") == 0)
        return FLY_ATTENDANT;
    if(strcmp(jobStr.c_str(), "NAVIGATOR") == 0)
        return NAVIGATOR;

    // otherwise - return other
    return OTHER;
}

/**
 * parseJobToString(Jobs job).
 *
 * @param job Jobs -- a job type
 * @return a string representation of the job type
 */
string ParseHandling::parseJobToString(Jobs job) {
    switch(job) {
        case MANAGER:
            return "MANAGER";
        case PILOT:
            return "PILOT";
        case FLY_ATTENDANT:
            return "FLY_ATTENDANT";
        case NAVIGATOR:
            return "NAVIGATOR";
        default:
            return "OTHER";
    }
}

/**
 * writeToFile(stringstream ss, const string& str)
 *
 * @param str const string& -- a constant string to write.
 * @param str string -- the file path.
 */
void ParseHandling::writeStrToFile(const string &str, const string &fp) {
    ofstream outfile;

    if(!fileExists(fp)){
        outfile.open(fp.c_str());
        outfile << str;
        outfile.close();
        return;
    }

    outfile.open(fp, std::ios_base::app);
    outfile << str;
    outfile.close();
}

/**
 * parseClassToStr(Classes cls).
 *
 * @param cls Class -- the class
 * @return a string representation of the class
 */
string ParseHandling::parseClassToStr(Classes cls) {
    switch(cls) {
        case FIRST_CLASS: return "FIRST_CLASS";
        case SECOND_CLASS: return "SECOND_CLASS";
    }
}

/**
 * fileExists(const string& fp)
 *
 * @param fp const string& -- file path.
 * @return bool if file exists, or false otherwise.
 */
bool ParseHandling::fileExists(const string& fp) {
    struct stat buf;
    return (stat(fp.c_str(), &buf) != -1);
}

/**
 * existsByID(const string& id, const string& fp).
 *
 * @param id const string& -- an id
 * @param fp const string& -- a FP
 * @return true if the id exists in the file, or false otherwise.
 */
bool ParseHandling::existsByID(const string& id, const string& fp) {
    if (!fileExists(fp))
        return false;

    // Local Variables
    ifstream file(fp);
    vector<string> vec;

    auto it = vec.begin();

    string l;
    // for each line
    while (getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());
        // MODEL
        if (strcmp(splitLine.at(0).c_str(), id.c_str()) == 0) {
            return true;
        }
    }
    // none was found ->
    return false;
}

/**
 * checkIfModelExists(int modelNumber).
 *
 * @param modelNumber int -- the model number
 * @return true if the model already exists in the MODELS_FP, or false otherwise
 */
bool ParseHandling::modelAlreadyExists(int modelNumber) {
    if (!fileExists(MODELS_FP))
        return false;

    // Local Variables
    ifstream file(MODELS_FP);
    vector<string> vec;

    auto it = vec.begin();

    string l;
    // for each line
    while (getline(file, l)) {
        // get istringstream of the line
        istringstream iss(l);

        // turn it into a vector separated by words
        vector<string> splitLine(istream_iterator<string>{iss},
                                 istream_iterator<string>());

        // skip every like that doesn't start with "MODEL"
        if(strcmp(splitLine.at(0).c_str(), "MODEL") != 0)
            continue;

        // got MODEL -> check number
        string modelNumStr = to_string(modelNumber);
        if(strcmp(splitLine.at(1).c_str(), modelNumStr.c_str()) == 0)
            // if equals -> return true
            return true;
    }
    // didn't find
    return false;
}

/**
 * parseDatesVectorToFile(const string& pid, vector<Date> datesVec).
 *
 * @param pid const string& -- plane ID.
 * @param datesVec vectorCate> -- a vector of dates.
 */
void ParseHandling::parseDatesVectorToFile(const string& pid, vector<Date> datesVec) {
    ofstream outfile;

    // open new or append
    if(!fileExists(PLANES_BOOKING_DATES)) {
        outfile.open(PLANES_BOOKING_DATES);
    } else {
        outfile.open(PLANES_BOOKING_DATES, std::ios_base::app);
    }

    stringstream ss;

    ss << pid;
    ss << endl;

    // for each date
    for(Date d : datesVec) {
        ss << d.getDate();
        ss << endl;
    }

    writeStrToFile(ss.str(), PLANES_BOOKING_DATES);
}