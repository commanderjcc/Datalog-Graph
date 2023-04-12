//
// Created by Josh Christensen on 3/6/23.
//

#ifndef DB_DLPARSER_TUPLE_H
#define DB_DLPARSER_TUPLE_H
#include <string>
#include <vector>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:
    Tuple();

    Tuple(vector<string> values) : vector<string>(values) { }

    static bool joinable(const Scheme& leftS, const Scheme& rightS, const Tuple& leftT, const Tuple& rightT);

    string toString(const Scheme& scheme) const;
};


#endif //DB_DLPARSER_TUPLE_H
