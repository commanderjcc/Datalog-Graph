//
// Created by Josh Christensen on 3/6/23.
//

#ifndef DB_DLPARSER_SCHEME_H
#define DB_DLPARSER_SCHEME_H
#include <string>
#include <vector>

using namespace std;

class Scheme : public vector<string> {

public:

    explicit Scheme(vector<string> headers) : vector<string>(headers) { }
    Scheme() = default;

    static Scheme joinSchemes(const Scheme& left, const Scheme& right);
};


#endif //DB_DLPARSER_SCHEME_H
