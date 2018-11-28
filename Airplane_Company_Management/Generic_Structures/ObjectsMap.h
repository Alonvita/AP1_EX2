//
// Created by alon on 26/11/18.
//

#ifndef AP1_OBJECTSLIST_H
#define AP1_OBJECTSLIST_H

#include <map>
#include "../File_Parsing/ParseHandling.h"
#include "../interface.h"

using namespace std;

template <class K, class V, class J>
class ObjectsMap {
private:
// ParseHandling<V> fp;
    multimap<K, V> objects;
public:
    /// ---------- CONSTRUCTORS - DESTRUCTORS ---------
    ObjectsMap() = default;
    ~ObjectsMap() = default;

    /// ---------- GETTERS & SETTERS ---------
    V       getItem     (K);
    bool    addItem     (K, V);
    bool    addItem     (pair<K,pair<V, J>>);

    /// ---------- ITERATIONS ---------
    typename multimap<K, V, J>::iterator end();
    typename multimap<K, V, J>::iterator find(K);
    typename multimap<K, V, J>::iterator begin();

};

template class ObjectsMap<string, Plane*>;
template class ObjectsMap<string, Flight*>;
template class ObjectsMap<string, Employee*>;
template class ObjectsMap<string, Customer*>;
template class ObjectsMap<string, Reservation*>;
template class ObjectsMap<Jobs, map<string, Employee*>>;

#endif //AP1_OBJECTSLIST_H