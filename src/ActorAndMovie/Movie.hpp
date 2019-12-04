/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: the implementation  and header file for Movie
 */
#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>

using namespace std;
/**
 * a class, instances of which are movies exist in edges in the graph
 */
class Movie {
  public:
    string MovieName;       // movie name + year in format
    int year;               // movie date
    vector<string> actors;  // actor work in this movie
    int weight;             // weight for specific movie

    /**
     * Constructor for Movie
     * Para: movieName: movie name + year
     *       date: movie date
     * also set the weight according to the date for this movie
     */
    Movie(string movieName, int date) : MovieName(movieName), year(date) {
        weight = 1 + 2019 - date;
    }
};
#endif