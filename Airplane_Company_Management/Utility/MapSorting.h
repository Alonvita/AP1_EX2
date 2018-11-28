//
// Created by alon on 28/11/18.
//

#ifndef AP1_MAPSORTING_H
#define AP1_MAPSORTING_H

#include <map>

using namespace std;

template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &p) {
    return pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
multimap<B,A> flip_map(const map<A,B> &src) {
    multimap<B,A> dst;
    transform(src.begin(), src.end(), inserter(dst, dst.begin()), flip_pair<A,B>);
    return dst;
}



#endif //AP1_MAPSORTING_H
