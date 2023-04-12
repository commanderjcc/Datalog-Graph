//
// Created by Josh Christensen on 1/19/23.
//

#include "Scanner.h"

#include <cctype>
#include <iostream>

Token Scanner::scanToken() {
    char c = input.at(0);
    while(isspace(c)) {
        if (c == '\n') {
            ++curr_line;
        }
        input = input.substr(1);
        if (input.empty()) {
            return Token(EoF, "", curr_line); // if we're ever empty, return the EoF Token
        }

        c = input.at(0);
    }
    input = input.substr(1); //After storing character as c, consume the character
    switch (c) {
        case ',':
            return Token(COMMA, ",", curr_line);
        case '.':
            return Token(PERIOD, ".", curr_line);
        case '?':
            return Token(Q_MARK, "?", curr_line);
        case '(':
            return Token(LEFT_PAREN, "(", curr_line);
        case ')':
            return Token(RIGHT_PAREN, ")", curr_line);
        case ':':
            if (input.at(0) == '-') { // if the next char is a dash
                input = input.substr(1); // consume it as well
                return Token(COLON_DASH, ":-", curr_line); // and return a Colon dash token
            } else {
                return Token(COLON, ":", curr_line); // if it's anything else, return a colon token and leave the input to be consumed later
            }
        case '*':
            return Token(MULTIPLY, "*", curr_line);
        case '+':
            return Token(ADD, "+", curr_line);
        case '\'':
            return consumeString();
        case '#':
            return consumeComment();
        default:
            return consumeIdentifier(c);
    }
}

void Scanner::scan() {
    while (!input.empty()) {
        Token token = scanToken();
        if (!comments) {
            if (token.getType() != COMMENT) {
                tokens.push_back(token);
            }
        } else {
            tokens.push_back(token);
        }
    }
    if (tokens.empty()) {
        tokens.emplace_back(Token(EoF, "", 1));
    }
}

void Scanner::printTokens() {
    for (Token token : tokens) {
        std::cout << token.toString() << std::endl;
    }

    std::cout << "Total Tokens = " << tokens.size() << std::endl;
}

Token Scanner::consumeString() {
    char c = input.at(0);
    std::string val = "'"; // start out with the first ' that was consumed already
    int start_line = curr_line;
    while (c != '\'') {
        if (c == '\n') {
            ++curr_line;
        }

        val.push_back(c); //append char
        input = input.substr(1);

        if (input.empty()) {
            input.push_back(' '); // give the input back one more whitespace to trigger the EOF Token
            return Token(UNDEFINED, val, start_line);
        }



        c = input.at(0);
    }
    val.push_back('\''); //append the final quote
    input = input.substr(1); // consume final quote from input

    return Token(STRING, val, curr_line);
}

Token Scanner::consumeComment() {
    char c = input.at(0);
    std::string val = "#"; // start out with the first # that was consumed already
    while (c != '\n' || input.empty()) {
        val.push_back(c); //append char
        input = input.substr(1);

        c = input.at(0);
    }
    ++curr_line; // we left the loop on a newline or EOF
    input = input.substr(1); // consume the newline

    return Token(COMMENT, val, curr_line - 1);
}

Token Scanner::consumeIdentifier(char start) {
    char c = start;
    std::string val;
    val.push_back(c); // start out with the first char that was consumed already

    if (!isalpha(c)) {
        return Token(UNDEFINED, val, curr_line);
    }

    c = input.at(0);
    while (isalnum(c)) {
        val.push_back(c); //append char
        input = input.substr(1);
        c = input.at(0);
    }

    if (val == "Schemes") {
        return Token(SCHEMES, val, curr_line);
    } else if (val == "Facts") {
        return Token(FACTS, val, curr_line);
    } else if (val == "Rules") {
        return Token(RULES, val, curr_line);
    } else if (val == "Queries") {
        return Token(QUERIES, val, curr_line);
    }

//    if (c == '\n') { // I don't think I need this because the while loop in the scan function will pick it up.
//        ++curr_line;
//    }
//    input = input.substr(1);

    return Token(ID, val, curr_line);
}
