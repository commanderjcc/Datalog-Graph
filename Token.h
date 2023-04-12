//
// Created by Josh Christensen on 1/19/23.
//

#ifndef DLSCANNER_TOKEN_H
#define DLSCANNER_TOKEN_H

#include <string>
#include <sstream>

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EoF
};

class Token {
private:
    TokenType type;
    std::string value;
    int line;

    static const std::string typeToString(TokenType t);

public:
    Token(TokenType type, std::string value, int line) : type(type), value(value), line(line) {
        // Init
    }

    std::string toString() const;

    TokenType getType() const;

    std::string getVal() const;

    Token();
};


#endif //DLSCANNER_TOKEN_H
