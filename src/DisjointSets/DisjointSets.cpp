#include "DisjointSets.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "ActorEdge.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"
using namespace std;

DisjointSets::DisjointSets(ActorGraph* inputGraph, int numActors) {
    this->graph = inputGraph;
    for (auto actor : inputGraph->ActorList) {
        actor.second->parent = nullptr;
    }
}

ActorNode* DisjointSets::find(ActorNode* findNode) const {
    ActorNode* temp = findNode;
    while (temp->parent != nullptr) {
        temp = temp->parent;
    }
    return temp;
}

void DisjointSets::unionSets(ActorNode* node1, ActorNode* node2) {
    ActorNode* root1 = find(node1);
    ActorNode* root2 = find(node2);
    if (root1 == root2) {
        return;
    }

    if (root1->ActorName < root2->ActorName) {
        root1->parent = root2;
    } else {
        root2->parent = root1;
    }
}