//
// Created by Josh Christensen on 2/6/23.
//

#include "Rule.h"
#include <sstream>

std::string Rule::toString() const {
    std::stringstream out;
    out << head.toString() << " :- ";
    for (auto i = body.begin(); i != body.end(); i++) {
        out << i->toString();

        if (!(i != body.end() && next(i) == body.end())) {
            out << ",";
        }
    }
    out << ".";
    return out.str();
}

Rule::Rule(const Predicate &head, const std::vector<Predicate> &body) : head(head), body(body) {}

Rule::Rule(const Predicate &head) {
    this->head = head;
}

void Rule::addBodyPredicate(const Predicate &p) {
    body.push_back(p);
}

Rule::Rule() = default;
