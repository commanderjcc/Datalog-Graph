//
// Created by Josh Christensen on 4/4/23.
//

#ifndef DL_GRAPH_GRAPH_H
#define DL_GRAPH_GRAPH_H
#include "Node.h"
#include <map>
#include <string>
#include <stack>

using namespace std;

class Graph {
public:

    map<int,Node> nodes;
    vector<int> postOrderStack;

public:

    explicit Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    Graph DFS(int node, vector<int> order);

    vector<Graph> DFSforest(vector<int> order);

    vector<int> getPostOrder();

    string toString();
};


#endif //DL_GRAPH_GRAPH_H
