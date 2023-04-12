//
// Created by Josh Christensen on 2/4/23.
//

#ifndef DLPARSER_PARSER_H
#define DLPARSER_PARSER_H
#include "Token.h"
#include <vector>

#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;



public:
    Parser(const vector<Token>& tokens);

    DatalogProgram parse();

    //helper functions
    TokenType tokenType() const;
    Token match(TokenType t);
    void advanceToken();
    void throwError(Token t);

    //Grammar Rules

    // Start Sequence
    DatalogProgram datalogProgram();

    // Global Lists
    std::vector<Predicate> schemeList();
    std::vector<Predicate> factList();
    std::vector<Rule> ruleList();
    std::vector<Predicate> queryList();

    // Premises
    Predicate scheme();
    Predicate fact();
    Rule rule();
    Predicate query();

    // Predicates
    Predicate headPredicate();
    Predicate predicate();

    // Lists
    std::vector<Predicate> predicateList();
    std::vector<Parameter> parameterList();
    std::vector<Parameter> stringList();
    std::vector<Parameter> idList();

    // parameter
    Parameter parameter();
};


#endif //DLPARSER_PARSER_H
