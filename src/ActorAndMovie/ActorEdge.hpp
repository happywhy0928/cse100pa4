/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the implementation  and header file for ActorEdge
 */

#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP
#include <string>
#include <vector>
#include "Movie.hpp"
using namespace std;
/**
 * a class, instances of which are edges in the graph
 */
class ActorEdge {
  public:
    string star1;           // left side of edge
                            //  string star2;           // right side of edge
    string actor;           // name of the actor on the other side
    vector<Movie*> movies;  // movie list these two actor work
    Movie* newestMovie;     // most recent movie to determine the weight
    int weight;             // edge weight

    /**
     * Constructor
     * Para: input_actor: the name of the actor on the other sider
     */
    explicit ActorEdge(string input_actor) : actor(input_actor) {
        newestMovie = nullptr;
        movies = vector<Movie*>();
    }

    /**
     * return the most recent movie in the edge
     */
    Movie* getNewestMovie() {
        // if already set
        if (newestMovie != nullptr) {
            return newestMovie;
        }
        int index = 0;
        // start to search and compare
        for (int i = 1; i < movies.size(); i++) {
            if (movies[i]->year > movies[index]->year) {
                index = i;
            }
        }
        newestMovie = movies[index];
        return newestMovie;
    }

    /**
     * a comparator later used in priority queue for edge sets
     */
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