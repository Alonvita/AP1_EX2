//
// Created by alon_vita on 11/22/18.
//


#ifndef AP1_EX2_EMPLOYEE_H
#define AP1_EX2_EMPLOYEE_H

#include "interface.h"
#include "Descriptors/DescriptorsFactory.h"

class MyEmployee : public Employee {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    MyEmployee(Descriptor&, Jobs, Employee* = nullptr, int = 0, int = 0);
    ~MyEmployee() override;

    /// ---------- GETTERS & SETTERS ----------
    string      getID() override;
    int         getSeniority() override;
    int         getBirthYear() override;
    Jobs        getTitle() override;
    Employee*   getEmployer() override;

private:
    /// ---------- PRIVATE MEMBERS ----------
    Jobs        jobs;
    Employee*   employer;
    int         seniority;
    int         birthYear;
    Descriptor  descriptor;
};

#endif //AP1_EX2_EMPLOYEE_H