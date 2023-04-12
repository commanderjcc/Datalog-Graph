//
// Created by Josh Christensen on 2/6/23.
//

#include "Predicate.h"
#include <sstream>

std::string Predicate::toString() const {
    std::stringstream out;
    out << name << "(";
    for (auto i = parameters.begin(); i != parameters.end(); i++) {
        out << i->value;

        if (!(i != parameters.end() && next(i) == parameters.end())) {
            out << ",";
        }
    }
    out << ")";
    return out.str();
}

Predicate::Predicate(const std::string &name, const std::vector<Parameter> &parameters) : name(name),
                                                                                          parameters(parameters) {

}

Predicate::Predicate(): name("ERROR") {}

Predicate::Predicate(const std::string &name): name(name) {

}
