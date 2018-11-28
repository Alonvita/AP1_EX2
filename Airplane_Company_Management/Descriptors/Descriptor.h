//
// Created by alon on 25/11/18.
//

#ifndef AP1_DESCRIPTOR_H
#define AP1_DESCRIPTOR_H

#include "../interface.h"

class Descriptor : public ID {
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ----------
    Descriptor(const string&);
    Descriptor() = default;
    Descriptor(string&, const string&);

    /// ---------- OVERRIDING ----------
    string  getID() override;

private:
    string ID;
    string identifier;
};

#endif //AP1_DESCRIPTOR_H
