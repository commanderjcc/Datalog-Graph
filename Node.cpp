//
// Created by Josh Christensen on 4/4/23.
//

#include "Node.h"
#include <sstream>

void Node::addEdge(int nodeID) {
    adjacentNodeIDs.insert(nodeID);
}

string Node::toString() {
    stringstream ss;
    for (int i : adjacentNodeIDs) {
        // if not last element, don't add a comma
        if (i != *adjacentNodeIDs.rbegin()) {
            ss << "R" << i << ",";
        } else {
            ss << "R" << i;
        }
    }

    return ss.str();
}
