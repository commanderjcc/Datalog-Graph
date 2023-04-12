//
// Created by Josh Christensen on 2/7/23.
//

#ifndef DLPARSER_PARAMETER_H
#define DLPARSER_PARAMETER_H
#include <string>


enum ParameterType {
    CONSTANT,
    IDENTIFIER,
    ERROR,
};

class Parameter {
public:
    Parameter();

    Parameter(ParameterType type, const std::string &value);

    ParameterType type;
    std::string value;

    bool isConstant() const;
};


#endif //DLPARSER_PARAMETER_H
