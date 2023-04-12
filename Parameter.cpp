//
// Created by Josh Christensen on 2/7/23.
//

#include "Parameter.h"

Parameter::Parameter(ParameterType type, const std::string &value) : type(type), value(value) {

}

Parameter::Parameter(): type(ERROR), value("") {}

bool Parameter::isConstant() const {
    return type == CONSTANT;
}
