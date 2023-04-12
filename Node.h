//
// Created by Josh Christensen on 4/4/23.
//

#ifndef DL_GRAPH_NODE_H
#define DL_GRAPH_NODE_H
#include <set>
#include <string>

using namespace std;

class Node {
public:
    set<int> adjacentNodeIDs;
    bool visited;
    int postOrder;

public:
    void addEdge(int nodeID);

    string toString();
};


#endif //DL_GRAPH_NODE_H
