#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "ActorNode.hpp"
#include "Movie.hpp"
using namespace std;
class ActorEdge {
  public:
    ActorNode* start;
    ActorNode* end;
    Movie* bothMovie;
    int weight;
    ActorEdge() {
        start = nullptr;
        end = nullptr;
        bothMovie = nullptr;
        weight = 0;
    }
};
#endif