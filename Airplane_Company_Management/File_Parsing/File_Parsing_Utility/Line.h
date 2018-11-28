//
// Created by alon on 28/11/18.
//

#ifndef AP1_LINE_H
#define AP1_LINE_H

#include <string>
#include <iterator>
#include <iostream>

using namespace std;

// SOURCE: https://stackoverflow.com/questions/2291802/is-there-a-c-iterator-that-can-iterate-over-a-file-line-by-line
class Line : string {
public:
    Line(){};

    friend istream & operator>>(istream & is, Line & line)
    {
        return getline(is, line);
    }

    template<class OutIt>
    void read_lines(istream& is, OutIt dest)
    {
        typedef istream_iterator<Line> InIt;
        copy(InIt(is), InIt(), dest);
    }
};

#endif //AP1_LINE_H
