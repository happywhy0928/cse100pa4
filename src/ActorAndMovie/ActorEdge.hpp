#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include "Movie.hpp"
using namespace std;
class ActorEdge {
  public:
    string actor;
    vector<Movie*> movies;
    Movie* mostRecentMovie;
    explicit ActorEdge(string input_actor) : actor(input_actor) {
        mostRecentMovie = nullptr;
        movies = vector<Movie*>();
    }
    Movie* getMostRecentMovie() {
        if (mostRecentMovie != nullptr) {
            return mostRecentMovie;
        }
        int index = 0;
        for (int i = 1; i < movies.size(); i++) {
            if (movies[i]->year > movies[index]->year) {
                index = i;
            }
        }
        mostRecentMovie = movies[index];
        return mostRecentMovie;
    }
};
#endif