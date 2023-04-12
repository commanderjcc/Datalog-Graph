//
// Created by Josh Christensen on 2/4/23.
//

#include "Parser.h"

#include <iostream>

TokenType Parser::tokenType() const {
    return tokens.at(0).getType();
}
void Parser::advanceToken() {
    tokens.erase(tokens.begin());
}
void  Parser::throwError(Token t) {
    throw t;
}

Parser::Parser(const vector<Token> &tokens) : tokens(tokens) {

}

Token Parser::match(TokenType t) {
//    cout << "match: " << t << endl;
    Token token = tokens.at(0);
    if (tokenType() == t) {
        advanceToken();
    } else {
        throwError(token);
    }
    return token;
}

DatalogProgram Parser::datalogProgram() {
    if (tokenType() == SCHEMES) {
        match(SCHEMES);
        match(COLON);
        Predicate s = scheme();
        vector<Predicate> sList = schemeList();
        sList.insert(sList.begin(), s);
        match(FACTS);
        match(COLON);
        vector<Predicate> fList = factList();
        match(RULES);
        match(COLON);
        vector<Rule> rList = ruleList();
        match(QUERIES);
        match(COLON);
        Predicate q = query();
        vector<Predicate> qList = queryList();
        qList.insert(qList.begin(), q);
        match(EoF);
        return DatalogProgram(sList, fList, qList, rList);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}


//TODO change all of the vectors to Linked Lists. They'd be faster.
std::vector<Predicate> Parser::schemeList() {
    if (tokenType() == ID) {
        Predicate s = scheme();
        vector<Predicate> sList = schemeList();
        sList.insert(sList.begin(), s);
        return sList;
    } else {
        // lambda
        return {};
    }
}

std::vector<Predicate> Parser::factList() {
    if (tokenType() == ID) {
        Predicate f = fact();
        vector<Predicate> fList = factList();
        fList.insert(fList.begin(), f);
        return fList;
    } else {
        // lambda
        return {};
    }
}

std::vector<Rule> Parser::ruleList() {
    if (tokenType() == ID) {
        Rule r = rule();
        vector<Rule> rList = ruleList();
        rList.insert(rList.begin(), r);
        return rList;
    } else {
        // lambda
        return {};
    }
}

std::vector<Predicate> Parser::queryList() {
    if (tokenType() == ID) {
        Predicate q = query();
        vector<Predicate> qList = queryList();
        qList.insert(qList.begin(), q);
        return qList;
    } else {
        // lambda
        return {};
    }
}

Predicate Parser::scheme() {
    if (tokenType() == ID) {
        Token name = match(ID);
        match(LEFT_PAREN);
        Token t = match(ID);
        vector<Parameter> ids = idList();
        ids.insert(ids.begin(), Parameter(IDENTIFIER, t.getVal()));
        match(RIGHT_PAREN);
        return Predicate(name.getVal(), ids);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

Predicate Parser::fact() {
    if (tokenType() == ID) {
        Token name = match(ID);
        match(LEFT_PAREN);
        Token t = match(STRING);
        vector<Parameter> strings = stringList();
        strings.insert(strings.begin(), Parameter(CONSTANT, t.getVal()));
        match(RIGHT_PAREN);
        match(PERIOD);
        return Predicate(name.getVal(), strings);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

Rule Parser::rule() {
    if (tokenType() == ID) {
        Predicate head = headPredicate();
        match(COLON_DASH);
        Predicate p = predicate();
        vector<Predicate> pList = predicateList();
        pList.insert(pList.begin(), p);
        match(PERIOD);
        return Rule(head, pList);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

Predicate Parser::query() {
    if (tokenType() == ID) {
        Predicate p = predicate();
        match(Q_MARK);
        return p;
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

Predicate Parser::headPredicate() {
    if (tokenType() == ID) {
        Token name = match(ID);
        match(LEFT_PAREN);
        Token t = match(ID);
        vector<Parameter> ids = idList();
        ids.insert(ids.begin(), Parameter(IDENTIFIER, t.getVal()));
        match(RIGHT_PAREN);
        return Predicate(name.getVal(), ids);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

Predicate Parser::predicate() {
    if (tokenType() == ID) {
        Token name = match(ID);
        match(LEFT_PAREN);
        Parameter p = parameter();
        vector<Parameter> pList = parameterList();
        pList.insert(pList.begin(), p);
        match(RIGHT_PAREN);
        return Predicate(name.getVal(), pList);
    } else {
        throwError(tokens.at(0));
        return {};
    }
}

std::vector<Predicate> Parser::predicateList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        Predicate p = predicate();
        vector<Predicate> pList = predicateList();
        pList.insert(pList.begin(), p);
        return pList;
    } else {
        // lambda
        return {};
    }
}

std::vector<Parameter> Parser::parameterList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        Parameter p = parameter();
        vector<Parameter> pList = parameterList();
        pList.insert(pList.begin(), p);
        return pList;
    } else {
        // lambda
        return {};
    }
}

std::vector<Parameter> Parser::stringList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        Token t = match(STRING);
        vector<Parameter> strings = stringList();
        strings.insert(strings.begin(), Parameter(CONSTANT, t.getVal()));
        return strings;
    } else {
        // lambda
        return {};
    }
}

std::vector<Parameter> Parser::idList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        Token t = match(ID);
        vector<Parameter> ids = idList();
        ids.insert(ids.begin(), Parameter(IDENTIFIER, t.getVal()));
        return ids;
    } else {
        // lambda
        return {};
    }
}

Parameter Parser::parameter() {
    if (tokenType() == STRING) {
        Token t = match(STRING);
        return Parameter(CONSTANT, t.getVal());
    } else if (tokenType() == ID) {
        Token t = match(ID);
        return Parameter(IDENTIFIER, t.getVal());
    } else {
        throwError(tokens.at(0));
        return Parameter();
    }
}

DatalogProgram Parser::parse() {
    DatalogProgram d;
    d = datalogProgram();
//    cout << "Success!" << endl;
    return d;
}
