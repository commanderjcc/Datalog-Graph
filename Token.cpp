//
// Created by Josh Christensen on 1/19/23.
//

#include "Token.h"

const std::string Token::typeToString(TokenType t) {
    switch (t) {
        case COMMA:
            return "COMMA";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case ID:
            return "ID";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case EoF:
            return "EOF";
        case UNDEFINED:
            return "UNDEFINED";
        default:
            return "ERROR";
    }
}

std::string Token::toString() const {
    std::stringstream out;
    out << "(" << typeToString(type) << "," << "\"" << value << "\"" << "," << line << ")";
    return out.str();
}

TokenType Token::getType() const {
    return type;
}

std::string Token::getVal() const {
    return value;
}

Token::Token() = default;
