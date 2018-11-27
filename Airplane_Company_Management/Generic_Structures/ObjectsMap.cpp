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
template <class K, class V>
V ObjectsMap<K, V>::getItem(K key) {
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
template <class K, class V>
bool ObjectsMap<K, V>::contains(K key) {
    return (this->objects.at(key) != nullptr);
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
template <class K, class V>
bool ObjectsMap<K, V>::addItem(K key, V value) {
    // take the current size
    unsigned long size = this->objects.size();

    this->objects.insert(pair<K, V>(key, value));

    // if an item was added, the size would grow by 1.
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
typename map<K, V>::iterator ObjectsMap<K, V>::begin() {
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
typename map<K, V>::iterator ObjectsMap<K, V>::end() {
    return this->objects.end();
}