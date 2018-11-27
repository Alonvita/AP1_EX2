//
// Created by alon on 25/11/18.
//

#include "Descriptor.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------
Descriptor::Descriptor(string& identifier, const string& ID) {
    this->identifier = identifier;
    this->ID = ID;
}

/// ---------- OVERRIDING ----------
/**
 * getID().
 *
 * @return a string concat of the identifier + ID
 */
string Descriptor::getID() {
    string fullID = this->identifier;
    fullID.append(this->ID);

    return fullID;
}
