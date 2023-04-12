//
// Created by Josh Christensen on 2/6/23.
//

#include "DatalogProgram.h"
#include <iostream>


std::string DatalogProgram::toString() {
    std::cout << "Schemes(" << schemeList.size() << "):" << std::endl;
    for (Predicate s : schemeList) {
        std::cout << "  " << s.toString() << std::endl;
    }
    std::cout << "Facts(" << factList.size() << "):" << std::endl;
    for (Predicate f : factList) {
        std::cout << "  " << f.toString() << "." << std::endl;
    }
    std::cout << "Rules(" << ruleList.size() << "):" << std::endl;
    for (Rule r : ruleList) {
        std::cout << "  " << r.toString() << std::endl;
    }
    std::cout << "Queries(" << queryList.size() << "):" << std::endl;
    for (Predicate q : queryList) {
        std::cout << "  " << q.toString() << "?" << std::endl;
    }
    std::cout << "Domain(" << domain.size() << "):" << std::endl;
    for (std::string s : domain) {
        std::cout << "  " << s << std::endl;
    }
    return "I'm a datalog program";
}

DatalogProgram::DatalogProgram(const std::vector<Predicate> &schemeList, const std::vector<Predicate> &factList,
                               const std::vector<Predicate> &queryList, const std::vector<Rule> &ruleList) : schemeList(
        schemeList), factList(factList), queryList(queryList), ruleList(ruleList) {
    domain = std::set<std::string>();
    for (const Predicate& p : factList) {
//        domain.insert(p.name);
        for (const Parameter& x : p.parameters) {
            if (x.type == CONSTANT) {
                domain.insert(x.value);
            }
        }
    }
}

DatalogProgram::DatalogProgram(const std::vector<Predicate> &schemeList, const std::vector<Predicate> &factList,
                               const std::vector<Predicate> &queryList, const std::vector<Rule> &ruleList, const std::set<std::string> domain) : schemeList(
        schemeList), factList(factList), queryList(queryList), ruleList(ruleList), domain(domain) {}

const std::vector<Predicate> &DatalogProgram::getSchemeList() const {
    return schemeList;
}

const std::vector<Predicate> &DatalogProgram::getFactList() const {
    return factList;
}

const std::vector<Predicate> &DatalogProgram::getQueryList() const {
    return queryList;
}

const std::vector<Rule> &DatalogProgram::getRuleList() const {
    return ruleList;
}

const std::set<std::string> &DatalogProgram::getDomain() const {
    return domain;
}

DatalogProgram::DatalogProgram() = default;
