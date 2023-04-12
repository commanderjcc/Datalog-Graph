//
// Created by Josh Christensen on 3/6/23.
//

#include "Relation.h"
#include <sstream>
#include <algorithm>
#include <map>
#include <iostream>


void Relation::addTuple(const Tuple &tuple) {
    tuples.insert(tuple);
}

void Relation::addTuples(const set<Tuple> &t) {
    tuples.insert(t.begin(), t.end());
}

string Relation::toString() const {
    stringstream out;
    for (const auto& tuple : tuples)
        out << "  " << tuple.toString(scheme) << endl;
    return out.str();
}

Relation Relation::select(int index, const string &value) const {
    Relation result(name, scheme);
      for (const auto &item: tuples) {
          if (item.at(index) == value) {
              result.tuples.insert(item);
          }
      }
    return result;
}

Relation Relation::matchSelect(int i1, int i2) const {
    Relation result(name, scheme);
    for (const auto &item: tuples) {
        if (item.at(i1) == item.at(i2)) {
            result.tuples.insert(item);
        }
    }
    return result;
}

Relation Relation::project(const Scheme& projection) const {
    Relation result(name, projection);
    vector<int> mapping;

    // Find the index mapping for the tuples
    for (const auto &newHeader : projection) {
        int i = 0;
        for (const auto &header : scheme) {
            if (newHeader == header) {
                mapping.push_back(i);
            }
            ++i;
        }
    }

    // Apply mapping to each tuple
    for (const auto &tuple : tuples) {
        vector<string> newVals;
        for (const auto &i : mapping) {
            newVals.push_back(tuple.at(i));
        }
        result.addTuple(newVals);
    }

    return result;
}

Relation Relation::rename(const Scheme& newScheme) const {
    Relation result(name, newScheme);
    result.addTuples(tuples);
    return result;
}

const set<Tuple> &Relation::getTuples() const {
    return tuples;
}



Relation Relation::join(const Relation &right) {
    const Relation& left = *this;

    Scheme joinScheme = left.scheme;
    for (unsigned int i = 0; i < right.scheme.size(); i++) {
        // if the right scheme's label is not in the left scheme, add it
        if (find(left.scheme.begin(), left.scheme.end(), right.scheme.at(i)) == left.scheme.end()) {
            joinScheme.push_back(right.scheme.at(i));
        }
    }

    Relation result = Relation("TEMP!", joinScheme); // TODO change name
    for (const Tuple& leftTuple : left.tuples) {
        for (const Tuple& rightTuple : right.tuples) {
            if (Tuple::joinable(left.scheme, right.scheme, leftTuple, rightTuple)) {
                // join tuples
                Tuple resultTuple = leftTuple;
                for (unsigned int i = 0; i < right.scheme.size(); i++) {
                    // if the right scheme's label is not in the left scheme, add it
                    if (find(left.scheme.begin(), left.scheme.end(), right.scheme.at(i)) == left.scheme.end()) {
                        resultTuple.push_back(rightTuple.at(i));
                    }
                }
                result.addTuple(resultTuple);
            }
        }
    }

    return result;
}

//Tuple Relation::joinIfJoinable(const Scheme &leftS, const Scheme &rightS, const Tuple &leftT, const Tuple &rightT) {
//    bool tuplestatus = true;
//    bool colstatus = false;
//    for (unsigned leftIndex = 0; leftIndex < leftS.size(); leftIndex++) {
//        const string& leftName = leftS.at(leftIndex);
//        const string& leftValue = leftT.at(leftIndex);
//        cout << "left name: " << leftName << " value: " << leftValue << endl; //TODO remove
//        for (unsigned rightIndex = 0; rightIndex < rightS.size(); rightIndex++) {
//            const string& rightName = rightS.at(rightIndex);
//            const string& rightValue = rightT.at(rightIndex);
//            cout << "right name: " << rightName << " value: " << rightValue << endl;
//
//            if (leftName == rightName) {
//                colstatus = true;
//                if (leftValue != rightValue) {
//                    tuplestatus = false;
//                }
//            }
//        }
//    }
//
//    //return true;
//    return tuplestatus && colstatus;
//}

Relation::Relation() = default;
