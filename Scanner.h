//
// Created by Josh Christensen on 1/19/23.
//

#ifndef DLSCANNER_SCANNER_H
#define DLSCANNER_SCANNER_H

#include "Token.h"
#include <vector>

class Scanner {
private:
    std::string input;
    bool comments = false;
    int curr_line = 1;

    Token consumeString();
    Token consumeComment();
    Token consumeIdentifier(char start);

public:
    Scanner(const std::string &input, bool comments) : input(input), comments(comments) {

    }
    std::vector<Token> tokens;

    Token scanToken();

    void scan();

    void printTokens();
};


#endif //DLSCANNER_SCANNER_H
