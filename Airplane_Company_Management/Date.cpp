//
// Created by alon on 23/11/18.
//

#include <cstring>
#include "interface.h"
#include "Utility/OperatorsHandling.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------
/**
 * MyDate(string MyDate).
 *
 * @param MyDate string -- format: YYYY-MM-DD
 *
 */
Date::Date(string date) {
    this->date = date;
}

/// ---------- OPERATORS OVERLOADING ----------

/**
 * operator<(const MyDate &d) const.
 *
 * @param d const MyDate& -- a constant reference to a MyDate object.
 * @return true if this MyDate is lesser than other MyDate
 */
bool Date::operator<(const Date &d) const {
    Date dDate = d;
    Date thisDate = *this;

    return (operatorsHandler(thisDate, dDate) == LT);
}

/**
 * operator>(const MyDate &d) const.
 *
 * @param d const MyDate& -- a constant reference to a MyDate object.
 * @return true if this MyDate is greater than other MyDate
 */
bool Date::operator>(const Date &d) const {
    Date dDate = d;
    Date thisDate = *this;

    return (operatorsHandler(thisDate, dDate) == GT);
}

/**
 * operator==(const MyDate &d) const.
 *
 * @param d const MyDate& -- a constant reference to a MyDate object.
 * @return true if this MyDate is equal to other MyDate
 */
bool Date::operator==(const Date &d) const {
    Date dDate = d;
    Date thisDate = *this;

    return (operatorsHandler(thisDate, dDate) == EQUALS);
}