//
// Created by alon on 25/11/18.
//

#include "Descriptor.h"

/// ---------- CONSTRUCTORS - DESTRUCTORS ----------

/**
 * Descriptor(string fullID).
 *
 * @param fullID string -- a full ID
 */
Descriptor::Descriptor(const string& fullID) {
    this->identifier = fullID.substr(0, 3); // from fullID[0] take first 3 chars
    this->ID = fullID.substr(4); // from fullID[4] take the rest
}

/**
 * Descriptor(string& identifier, const string& ID).
 *
 * @param identifier string -- a string representing an identifier.
 * @param ID string -- id.
 */
Descriptor::Descriptor(string& ID, const string& identifier) {
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
