/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the implementation  for DisjointSets
 */

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
/**
 * constructor of disjointset which set the pointer to the graph
 * and initialize the parent for the further use
 * Para: inputgraph: the graph to take disjointset
 */
DisjointSets::DisjointSets(ActorGraph* inputGraph) {
    this->graph = inputGraph;
    for (auto actor : inputGraph->ActorList) {
        actor.second->parent = nullptr;
    }
}
/**
 * find the root of current node
 * para: findNode: the node to find the root
 * Return: return the root 
 */
ActorNode* DisjointSets::find(ActorNode* findNode) const {
    ActorNode* result = findNode;
    while (result->parent != nullptr) {
        result = result->parent;
    }
    ActorNode* temp = findNode;
    //path compression
    while (temp != result) {
        ActorNode* next = temp->parent;
        temp->parent = result;
        temp = next;
    }
    return result;
}
/**
 * union two node merge their root
 * para: node1 node2 two node two union the set
 */
void DisjointSets::unionSets(ActorNode* node1, ActorNode* node2) {
    ActorNode* root1 = find(node1);
    ActorNode* root2 = find(node2);
    if (root1 == root2) {
        return;
    }
    //merge two root to form a union
    if (root1->ActorName < root2->ActorName) {
        root1->parent = root2;
    } else {
        root2->parent = root1;
    }
}