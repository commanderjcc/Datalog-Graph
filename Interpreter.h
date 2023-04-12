//
// Created by Josh Christensen on 3/9/23.
//

#ifndef DB_DLPARSER_INTERPRETER_H
#define DB_DLPARSER_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram dl;

    Database db = Database();

public:
    explicit Interpreter(const DatalogProgram &dl);

    Relation evaluate(const Predicate& p);

    Relation evaluateRule(const Rule& r);

    Relation evaluateSCC(const vector<Rule>& rules);

    Relation evaluateQuery(const Predicate& p);

    void evaluateAllQueries();

    void evaluateAllRules();

    static pair<Graph,Graph> makeGraph(const vector<Rule>& rules);


};


#endif //DB_DLPARSER_INTERPRETER_H
