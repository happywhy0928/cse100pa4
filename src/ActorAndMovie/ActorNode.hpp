/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the implementation  and header file for ActorNode
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <climits>
#include <cmath>
#include <set>
#include <string>
#include <vector>
#include "ActorEdge.hpp"
#include "Movie.hpp"
using namespace std;

/**
 * a class, instances of which are nodes in the graph
 */
class ActorNode {
  public:
    string ActorName;          // node name: actor name
    vector<ActorEdge*> edges;  // relationship sets
    bool done;                 // later used for search
    ActorNode* prev;           // prev edge connect
    int distance;              // later used for search path
    string prevMovie;
    ActorNode* parent;  // later used for disjoint sets

    /**
     * Constructor for ActorNode
     * Para: actorName: the name of the actor
     *
     */
    ActorNode(string actorName) : ActorName(actorName) {
        done = false;
        prev = nullptr;
        edges = vector<ActorEdge*>();
    }

    /**
     * to reset the distance, prev and done for further use
     */
    void clean() {
        prev = nullptr;
        distance = -1;
        done = false;
    }
};
#endif