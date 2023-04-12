//
// Created by Josh Christensen on 2/6/23.
//

#ifndef DLPARSER_DATALOGPROGRAM_H
#define DLPARSER_DATALOGPROGRAM_H
#include <vector>
#include <set>
#include <string>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
private:
    std::vector<Predicate> schemeList;
    std::vector<Predicate> factList;
    std::vector<Predicate> queryList;
    std::vector<Rule> ruleList;

    std::set<std::string> domain;

public:
    DatalogProgram(const std::vector<Predicate> &schemeList, const std::vector<Predicate> &factList,
                   const std::vector<Predicate> &queryList, const std::vector<Rule> &ruleList);

    DatalogProgram(const std::vector<Predicate> &schemeList, const std::vector<Predicate> &factList,
                   const std::vector<Predicate> &queryList, const std::vector<Rule> &ruleList, const std::set<std::string> domain);

    std::string toString();

    DatalogProgram();

    const std::vector<Predicate> &getSchemeList() const;

    const std::vector<Predicate> &getFactList() const;

    const std::vector<Predicate> &getQueryList() const;

    const std::vector<Rule> &getRuleList() const;

    const std::set<std::string> &getDomain() const;
};


#endif //DLPARSER_DATALOGPROGRAM_H
