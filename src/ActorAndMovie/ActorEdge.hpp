#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "Movie.hpp"
using namespace std;
class ActorEdge {
  public:
    string actor;
    vector<Movie*> movies;
    Movie* newestMovie;
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
};
#endif