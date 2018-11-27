//
// Created by alon on 26/11/18.
//

#ifndef AP1_OBJECTSLIST_H
#define AP1_OBJECTSLIST_H

#include <map>
#include "../File_Parsing/FileParser.h"
#include "../interface.h"

using namespace std;

template <class K, class V>
class ObjectsMap {
private:
    FileParser fp;
    map<K, V> objects;
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ---------
    ObjectsMap() = default;
    ~ObjectsMap() = default;

    /// ---------- GETTERS & SETTERS ---------
    bool    contains    (K);
    V       getItem     (K);
    bool    addItem     (K, V);

    /// ---------- ITERATIONS ---------
    typename map<K, V>::iterator end();
    typename map<K, V>::iterator begin();

};

template class ObjectsMap<string, Plane*>;
template class ObjectsMap<string, Flight*>;
template class ObjectsMap<string, Employee*>;
template class ObjectsMap<string, Customer*>;
template class ObjectsMap<string, Reservation*>;

#endif //AP1_OBJECTSLIST_H
