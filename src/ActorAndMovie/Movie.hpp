#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <vector>

using namespace std;

class Movie {
  public:
    string MovieName;
    int year;
    vector<string> actors;
    int weight;

    Movie(string movieName, int date) : MovieName(movieName), year(date) {
        weight = 1 + 2019 - date;
    }
};
#endif