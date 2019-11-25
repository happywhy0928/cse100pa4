#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP
#include <climits>
#include <cmath>
#include <string>
#include <vector>
#include "Movie.hpp"

using namespace std;

class ActorNode {
  public:
    string ActorName;
    vector<Movie*> movie;
    bool done;
    ActorNode* prev;
    Movie* bothMovie;
    int disToBegin;
    int size;

    ActorNode(string actorName) : ActorName(actorName) {
        done = false;
        prev = nullptr;
        bothMovie = nullptr;
        disToBegin = INT_MAX;
        size = 1;
    }
};
#endif