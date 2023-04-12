//
// Created by Josh Christensen on 3/6/23.
//

#include "Scheme.h"
#include <set>

Scheme Scheme::joinSchemes(const Scheme &left, const Scheme &right) {
    set<string> vals;
    vals.insert(left.begin(), left.end());
    vals.insert(right.begin(), right.end());

    Scheme result;
    result.insert(result.end(), vals.begin(), vals.end());
    return result;
}
