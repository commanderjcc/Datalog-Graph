//
// Created by Josh Christensen on 3/6/23.
//

#ifndef DB_DLPARSER_RELATION_H
#define DB_DLPARSER_RELATION_H
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {
private:
    set<Tuple> tuples;
public:
    const set<Tuple> &getTuples() const;

public:
    string name;
    Scheme scheme;

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) {}

    void addTuple(const Tuple& tuple);

    void addTuples(const set<Tuple>& t);

    string toString() const;

    Relation select(int index, const string& value) const;

    Relation matchSelect(int i1, int i2) const;

    Relation project(const Scheme& projection) const;

    Relation rename(const Scheme& newScheme) const;

//    static Tuple joinIfJoinable(const Scheme& leftS, const Scheme& rightS, const Tuple& leftT, const Tuple& rightT);

    Relation join(const Relation& right);



    Relation();
};


#endif //DB_DLPARSER_RELATION_H
