//
// Created by Josh Christensen on 3/6/23.
//

#include "Tuple.h"
#include <sstream>

string Tuple::toString(const Scheme& scheme) const {
    Tuple tuple = *this;
    stringstream out;

    // Remove last element before running loop
    string tmp = tuple.back();
    tuple.pop_back();
    for (unsigned int i = 0; i < tuple.size(); ++i) {
        out << scheme.at(i) << "=" << tuple.at(i) << ", ";
    }

    //Put last element back without the ending comma
    out << scheme.at(tuple.size()) << "=" << tmp;

    return out.str();
}



bool Tuple::joinable(const Scheme &leftS, const Scheme &rightS, const Tuple &leftT, const Tuple &rightT) {
    bool tuplestatus = true; // true if the tuples are joinable, starts as true and gets set to
                             // false if the values are not the same on a matching column
    for (unsigned leftIndex = 0; leftIndex < leftS.size(); leftIndex++) {
        const string& leftName = leftS.at(leftIndex);
        const string& leftValue = leftT.at(leftIndex);
        for (unsigned rightIndex = 0; rightIndex < rightS.size(); rightIndex++) {
            const string& rightName = rightS.at(rightIndex);
            const string& rightValue = rightT.at(rightIndex);
            if (leftName == rightName) { // if the column names are the same
                if (leftValue != rightValue) { // and if the values are not the same
                    tuplestatus = false;  // then we know that the tuples are not joinable
                }
            }
        }
    }

    return tuplestatus; // true if we never failed a match, false if we did
}

Tuple::Tuple() {

}
