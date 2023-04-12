//
// Created by Josh Christensen on 4/4/23.
//

#include "Graph.h"
#include <sstream>

string Graph::toString() {
    stringstream ss;
    for (auto& pair: nodes) {
        int nodeID = pair.first;
        Node node = pair.second;

        ss << "R" << nodeID << ":" << node.toString() << endl;
    }


    return ss.str();
}


Graph Graph::DFS(int n, vector<int> order) {
    Node &currentNode = nodes.at(n);
    if (currentNode.visited) {
        return Graph(0);
    } else {
        currentNode.visited = true;
    }

    for (auto it = order.begin(); it != order.end(); it++) {
        if (*it == n) {
            order.erase(it);
            break;
        }
    }

    Graph combinedGraph = Graph(0);
    for (const auto i : order) {
        vector<Graph> subgraphs;
        if (currentNode.adjacentNodeIDs.count(i)) {
            Graph subgraph = DFS(i, order);
            subgraphs.push_back(subgraph);
        }

        for (const auto& subgraph : subgraphs) {
            for (const auto &node: subgraph.nodes) {
                combinedGraph.nodes.insert(node);
            }
        }
    }
    combinedGraph.nodes.insert({n, currentNode});

    postOrderStack.push_back(n);
    combinedGraph.postOrderStack = this->postOrderStack;
    return combinedGraph;
}

vector<Graph> Graph::DFSforest(vector<int> order) {
    vector<Graph> components;
    int c = 0;
    while (!order.empty()) {
        int start = order.front();
        order.erase(order.begin());
        Graph component = DFS(start, order);
        components.push_back(component);
        for (const auto &i : order) {
            if (component.nodes.count(i)) {
                order.erase(find(order.begin(), order.end(), i));
            }
        }
        c = c + 1;
    }

    return components;
}

vector<int> Graph::getPostOrder() {
    vector<int> order;
    for (int i = 0; i < nodes.size(); i++) {
        order.push_back(i);
    }

    vector<Graph> components = DFSforest(order);

    return components.back().postOrderStack;
}
