//
// Created by Josh Christensen on 3/9/23.
//

#include <map>
#include <iostream>
#include "Interpreter.h"

Relation Interpreter::evaluateQuery(const Predicate& predicate) {
    Relation rel = db.relations[predicate.name];
    map<string, int> mapping;
    vector<string> ordering;
    Relation result = Relation(rel);
    int index = 0;
    for (const auto& p : predicate.parameters) {
        if (p.isConstant()) {
            result = result.select(index, p.value);
        } else {
            if (mapping.count(p.value)) {
                int baselineIndex = mapping[p.value];
                result = result.matchSelect(baselineIndex, index);
            } else {
                ordering.push_back(p.value);
                mapping[p.value] = index;
            }
        }
        ++index;
    }

    cout << predicate.toString() << "? ";

    if (result.getTuples().empty()) {
        cout << "No" << endl;
    } else {
        if (!ordering.empty()) {
            Scheme returnScheme = Scheme();
            for (const auto& item : ordering) {
                returnScheme.push_back(rel.scheme.at(mapping[item]));
            }
            result = result.project(returnScheme);
            result = result.rename(Scheme(ordering));

            cout << "Yes(" << result.getTuples().size() << ")" << endl;
            cout << result.toString();
        } else {
            cout << "Yes(" << result.getTuples().size() << ")" << endl;
        }
    }

    return result;
}

void Interpreter::evaluateAllQueries() {
    cout << endl << "Query Evaluation" << endl;
    for (const auto& query : dl.getQueryList()) {
        evaluateQuery(query);
    }
}

Interpreter::Interpreter(const DatalogProgram &dl) : dl(dl) {
    db = Database(dl.getSchemeList(), dl.getFactList());
    // TODO evaluateRules and save them as the new relation

}

Relation Interpreter::evaluateRule(const Rule &r) {
    vector<Relation> relsToJoin;
    for (const Predicate& p : r.body) {
        Relation result = evaluate(p);
        relsToJoin.push_back(result);
    }
    while (relsToJoin.size() > 1) { // while there are more than one relation to join
        Relation last = relsToJoin.back();
        relsToJoin.pop_back();
        Relation secondToLast = relsToJoin.back();
        relsToJoin.pop_back();
        relsToJoin.push_back(secondToLast.join(last)); // join the last two relations
    }

    Relation result = relsToJoin.back();
    Scheme headScheme = Scheme();
    for (const auto& p : r.head.parameters) { // get the scheme for the head
        headScheme.push_back(p.value);
    }

    result = result.project(headScheme); // project the result to match the head

    Relation *existingRelation = &db.relations[r.head.name];
    result = result.rename(existingRelation->scheme); // rename the result to match the existing relation

    Relation newTuples = Relation("newTups", result.scheme);
    for (const auto& t : result.getTuples()) {
        if(existingRelation->getTuples().count(t)) {
            // tuple already exists
            // do nothing
        } else {
            // tuple does not exist
            newTuples.addTuple(t);
        }
    }

    existingRelation->addTuples(newTuples.getTuples()); // add the new tuples to the existing relation
    return newTuples;
}

Relation Interpreter::evaluate(const Predicate &predicate) {
    Relation rel = db.relations[predicate.name];
    map<string, int> mapping;
    vector<string> ordering;
    Relation result = Relation(rel);
    int index = 0;
    for (const auto& p : predicate.parameters) {
        if (p.isConstant()) {
            result = result.select(index, p.value);
        } else {
            if (mapping.count(p.value)) {
                int baselineIndex = mapping[p.value];
                result = result.matchSelect(baselineIndex, index);
            } else {
                ordering.push_back(p.value);
                mapping[p.value] = index;
            }
        }
        ++index;
    }

    if (result.getTuples().empty()) {

    } else {
        if (!ordering.empty()) {
            Scheme returnScheme = Scheme();
            for (const auto& item : ordering) {
                returnScheme.push_back(rel.scheme.at(mapping[item]));
            }
            result = result.project(returnScheme);
            result = result.rename(Scheme(ordering));
        } else {

        }
    }

    return result;
}

void Interpreter::evaluateAllRules() {

    cout << "Dependency Graph" << endl;
    pair<Graph,Graph> graphs = makeGraph(dl.getRuleList());
    Graph forwardGraph = graphs.first;
    cout << forwardGraph.toString() << endl;
    Graph reverseGraph = graphs.second;

    cout << "Rule Evaluation" << endl;
    vector<int> order = reverseGraph.getPostOrder();
    std::reverse(order.begin(), order.end());
    vector<Graph> SCCs = forwardGraph.DFSforest(order);

    for(const auto& SCC : SCCs) {
        int ruleNum = SCC.nodes.begin()->first;
        cout << "SCC: R" << ruleNum << endl;

        vector<Rule> rules;
        for (const auto& [i, node] : SCC.nodes) {
            rules.push_back(dl.getRuleList().at(i));
        }

        bool changed = true;
        int iteration = 0;

        if (rules.size() == 1) {
            Rule& rule = rules.at(0);
            // Check if rule doesn't depend on itself
            bool dependent = false;
            for (const auto& p : rule.body) {
                if (p.name == rule.head.name) {
                    dependent = true;
                    changed = true;
                    break;
                }
            }
            if (!dependent) {
                cout << rule.toString() << endl;
                Relation result = evaluateRule(rule);
                cout << result.toString();

                changed = false;
                iteration = 1;
            }
        }

        while (changed) {
            changed = false;
            for (const auto& rule : rules) {
                unsigned int before = db.relations[rule.head.name].getTuples().size();
                cout << rule.toString() << endl;
                Relation result = evaluateRule(rule);
                cout << result.toString();
                if (before != db.relations[rule.head.name].getTuples().size()) {
                    changed = true;
                }
            }
            ++iteration;
        }
        cout << iteration << " passes: R" << ruleNum << endl;
//        cout << endl << "Schemes populated after " << iteration << " passes through the Rules." << endl << endl;

    }





}

pair<Graph,Graph> Interpreter::makeGraph(const vector<Rule> &rules) {
    Graph graph(rules.size());
    Graph reverseGraph(rules.size());

    for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
        Rule fromRule = rules.at(fromID);
//        cout << "from rule R" << fromID << ": " << fromRule.toString() << endl;

        for (unsigned int pred = 0; pred < fromRule.body.size(); pred++) {
            Predicate bodyPred = fromRule.body.at(pred);
//            cout << "from body predicate: " << bodyPred.toString() << endl;

            for (unsigned toID = 0; toID < rules.size(); toID++) {
                Rule toRule = rules.at(toID);
//                cout << "to rule R" << toID << ": " << toRule.toString() << endl;
                if (toRule.head.name == bodyPred.name) {
                    graph.addEdge(fromID, toID);
                    reverseGraph.addEdge(toID, fromID);
//                    cout << "dependency found: (R" << fromID << ",R" << toID << ")" << endl;
                }
            }
        }
    }
    return {graph, reverseGraph};
}

Relation Interpreter::evaluateSCC(const vector<Rule> &rules) {
    return Relation();
}
