//
// Created by alon on 26/11/18.
//

#include "ObjectsMap.h"

/**
 * getItem(K key).
 *
 * @tparam K template<class K> -- a template of class K.
 * @tparam V template<class V> -- a template of class V.
 * @param key K -- a key of class type K.
 *
 * @return a value of class type V or nullptr if doesn't exist.
 */
template <class K, class V, class J>
V ObjectsMap<K, V, J>::getItem(K key) {
    return this->objects.at(key);
}

/**
 * contains(K key).
 *
 * @tparam K template<class K> -- a template of class K.
 * @tparam V template<class V> -- a template of class V.
 * @param key K -- a key of class type K
 *
 * @return true if the map contains a value to key K.
 */
template <class K, class V, class J>
bool ObjectsMap<K, V, J>::contains(K key) {
    return (this->objects.find(key) != this->objects.end());
}

/**
 * addItem(K key, V value).
 *
 * @tparam K template<class K> -- a template of class K.
 * @tparam V template<class V> -- a template of class V.
 * @param key K -- a key of class type K.
 * @param value V -- a value of class type V.
 *
 * @return true if the item was added successfully to the list.
 *          The success/failure value return is implemented by checking the
 *          container's size for:
 *
 *              size (after insertion) == size (b4 insertion) + 1
 *
 */
template <class K, class V, class J>
bool ObjectsMap<K, V, J>::addItem(K key, V value) {
    // take the current size
    unsigned long size = this->objects.size();

    this->objects.insert(pair<K, V>(key, value));

    // if an item was added, the size would grow by 1.
    return (this->objects.size() == size + 1);
}

/**
 * addItem(pair<K, V> p).
 *
 * @return true if the pair was added successfully, or false otherwise.
 *          implementation is done by checking the container size
 */
template <class K, class V, class J>
bool ObjectsMap<K, V>::addItem(pair<K, V> p) {
   unsigned long size = this->objects.size();

    V& v = this->objects.find(p.first);
    // check if v is a map
    if()

    return (this->objects.size() == size + 1);
}

/**
 * begin().
 *
 * @tparam K template<class K> -- a template of class K.
 * @tparam V template<class V> -- a template of class V.
 * @return a pointer to the beginning of the map
 */
template <class K, class V>
typename multimap<K, V>::iterator ObjectsMap<K, V>::begin() {
    return this->objects.begin();
}

/**
 * end().
 *
 * @tparam K template<class K> -- a template of class K.
 * @tparam V template<class V> -- a template of class V.
 * @return a pointer to the end of the map
 */
template <class K, class V>
typename multimap<K, V>::iterator ObjectsMap<K, V>::end() {
    return this->objects.end();
}

template <class K, class V>
typename multimap<K,V>::iterator ObjectsMap<K, V>::find(K key) {
    return this->objects.find(key);
}