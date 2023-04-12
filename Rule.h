//
// Created by Josh Christensen on 2/6/23.
//

#ifndef DLPARSER_RULE_H
#define DLPARSER_RULE_H
#include "Predicate.h"
#include <vector>
#include <string>

class Rule {
private:

public:
    Predicate head;
    std::vector<Predicate> body;

    std::string toString() const;

    Rule();

    explicit Rule(const Predicate &head);

    Rule(const Predicate &head, const std::vector<Predicate> &body);

    void addBodyPredicate(const Predicate& p);
};


#endif //DLPARSER_RULE_H
