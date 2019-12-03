#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "Movie.hpp"
using namespace std;
class ActorEdge {
  public:
    string star1;
    string star2;
    string actor;
    vector<Movie*> movies;
    Movie* newestMovie;
    int weight;
    explicit ActorEdge(string input_actor) : actor(input_actor) {
        newestMovie = nullptr;
        movies = vector<Movie*>();
    }
    Movie* getNewestMovie() {
        if (newestMovie != nullptr) {
            return newestMovie;
        }
        int index = 0;
        for (int i = 1; i < movies.size(); i++) {
            if (movies[i]->year > movies[index]->year) {
                index = i;
            }
        }
        newestMovie = movies[index];
        return newestMovie;
    }

    struct CompareWeight {
        bool operator()(const ActorEdge* edge1, const ActorEdge* edge2) {
            if (edge1->weight == edge2->weight) {
                return edge1->actor < edge2->actor;
            } else {
                return edge1->weight < edge2->weight;
            }
        }
    };
};
#endif