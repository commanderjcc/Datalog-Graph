//
// Created by Josh Christensen on 2/6/23.
//

#ifndef DLPARSER_PREDICATE_H
#define DLPARSER_PREDICATE_H
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
public:
    std::string name;
    std::vector<Parameter> parameters;

    Predicate();

    explicit Predicate(const std::string &name);

    Predicate(const std::string &name, const std::vector<Parameter> &parameters);

public:
    std::string toString() const;
};


#endif //DLPARSER_PREDICATE_H
