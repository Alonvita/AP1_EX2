//
// Created by alon on 25/11/18.
//

#include "OperatorsHandling.h"

/// ---------- UTILITY FUNCTIONS ----------
/**
 * operatorsHandler(const MyDate& d) const.
 *
 * @param d const MyDate& -- a constant reference to a MyDate object.
 * @return an enum representing the return value of the operation.
 *          EQUALS for equal strings
 *          LT if this.MyDate < d.MyDate
 *          otherwise, GT
 */
OperatorsHandlerResult operatorsHandler(Date& lhs, Date& rhs) {
    string otherDate = rhs.getDate();

    // Check equality
    if(strcmp(otherDate.c_str(), lhs.getDate().c_str()) == 0)
        return EQUALS;

    // Break d MyDate to separate strings
    string otherYear    = otherDate.substr(0, 4);
    string otherMonth   = otherDate.substr(5, 2);
    string otherDay     = otherDate.substr(8, 2);

    // Break this MyDate to separate strings
    string thisYear     = lhs.getDate().substr(0, 4);
    string thisMonth    =  lhs.getDate().substr(5, 2);
    string thisDay      =  lhs.getDate().substr(8, 2);

    // Check year < other year
    if(stoi(thisYear) < stoi(otherYear))
        return LT;

    if(stoi(thisYear) > stoi(otherYear))
        return GT;

    // This year > Other year -> check month
    if(stoi(thisMonth) < stoi(otherMonth))
        return LT;

    if(stoi(thisMonth) > stoi(otherMonth))
        return GT;

    // This year & Month > Other Year & Month -> check day
    return stoi(thisDay) < stoi(otherDay) ? LT : GT;
}