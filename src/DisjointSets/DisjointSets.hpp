/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the header file  for DisjointSets
 */
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
/**
 * a class, instances of which are disjointSet for MST use.
 */
class DisjointSets {
  public:
    ActorGraph* graph;          //current graph 
/**
 * constructor of disjointset which set the pointer to the graph
 * and initialize the parent for the further use
 * Para: inputgraph: the graph to take disjointset
 */
    DisjointSets(ActorGraph* inputGraph);
/**
 * find the root of current node
 * para: findNode: the node to find the root
 * Return: return the root 
 */
    ActorNode* find(ActorNode* findNode) const;
/**
 * union two node merge their root
 * para: node1 node2 two node two union the set
 */
    void unionSets(ActorNode* node1, ActorNode* node2);
};
#endif