
#ifndef DISJOINTSETS_HPP
#define DISJOINTSETS_HPP

#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>;
#include "ActorEdge.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;
class DisjointSets {
  public:
    ActorGraph* graph;

    DisjointSets(ActorGraph* inputGraph, int numActors);

    ActorNode* find(ActorNode* findNode) const;

    void unionSets(ActorNode* node1, ActorNode* node2);
};
#endif