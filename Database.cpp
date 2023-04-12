//
// Created by Josh Christensen on 3/9/23.
//

#include "Database.h"

Database::Database(const std::vector<Predicate>& schemeList, const std::vector<Predicate>& factList) {
    for (const auto &scheme: schemeList) {
        vector<string> headers;
        for (const auto &p: scheme.parameters) {
            headers.push_back(p.value);
        }

        Relation relation = Relation(scheme.name, Scheme(headers));

        for (const auto &fact : factList) {
            if (fact.name == scheme.name) {
                vector<string> values;
                for (const auto &p: fact.parameters) {
                    values.push_back(p.value);
                }
                relation.addTuple({values});
            }
        }

        relations[scheme.name] = relation;
    }
}
