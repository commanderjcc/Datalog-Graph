#include <iostream>
#include <fstream>

#include "Scanner.h"
#include "Token.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Node.h"
#include "Graph.h"

#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs(argv[1]);

    string content( (istreambuf_iterator<char>(ifs) ),
                    (istreambuf_iterator<char>()    ) );
    Scanner s = Scanner(content, false);
    s.scan();

    Parser p = Parser(s.tokens);

    try {
        DatalogProgram d = p.parse();

        Interpreter i = Interpreter(d);

        i.evaluateAllRules();

        i.evaluateAllQueries();

    } catch (Token &t) {
        cout << "Failure!" << endl;
        cout << "  " << t.toString() << endl;
    }


//    pair<string,vector<string>> ruleNames[] = {
//            { "A", { "B", "C" } },
//            { "B", { "A", "D" } },
//            { "B", { "B" } },
//            { "E", { "F", "G" } },
//            { "E", { "E", "F" } },
//    };
//
//    vector<Rule> rules;
//
//    for (auto& rulePair : ruleNames) {
//        string headName = rulePair.first;
//        Rule rule = Rule(Predicate(headName));
//        vector<string> bodyNames = rulePair.second;
//        for (auto& bodyName : bodyNames)
//            rule.addBodyPredicate(Predicate(bodyName));
//        rules.push_back(rule);
//    }
//
//    pair<Graph, Graph> graphs = Interpreter::makeGraph(rules);
//    cout << graphs.first.toString() << endl;
//    Graph dfsGraph = graphs.first.DFS(0, vector<int> { 0, 1, 2, 3, 4 });
//    cout << endl << dfsGraph.toString();
//    Graph dfsGraph2 = graphs.second.DFS(0, vector<int> { 0, 1, 2, 3, 4 });
//    Graph df3Graph3 = graphs.second.DFS(3, vector<int> { 0, 1, 2, 3, 4 });
//    Graph df4Graph4 = graphs.second.DFS(4, vector<int> { 0, 1, 2, 3, 4 });
//    cout << endl << dfsGraph2.toString();

    return 0;
}
