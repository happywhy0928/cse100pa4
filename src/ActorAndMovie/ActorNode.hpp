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

class ActorNode {
  public:
    string ActorName;
    vector<ActorEdge*> edges;
    bool done;
    ActorNode* prev;
    int distance;
    string prevMovie;

    ActorNode(string actorName) : ActorName(actorName) {
        done = false;
        prev = nullptr;
        distance = INT_MAX;
        edges = vector<ActorEdge*>();
    }
    void clean() {
        prev = nullptr;
        distance = -1;
        done = false;
    }
};
#endif