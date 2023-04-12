//
// Created by Josh Christensen on 3/9/23.
//

#ifndef DB_DLPARSER_DATABASE_H
#define DB_DLPARSER_DATABASE_H

#include <vector>
#include <map>
#include "Predicate.h"

#include "Relation.h"

class Database {

public:
    Database(const std::vector<Predicate>& schemeList, const std::vector<Predicate>& factList);

    Database() = default;

    map<string, Relation> relations;
};


#endif //DB_DLPARSER_DATABASE_H
