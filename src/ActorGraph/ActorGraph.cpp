/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorEdge.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
 * movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;

    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss(s);
        vector<string> record;

        while (ss) {
            string str;

            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        insertToGraph(actor, movie_title, year);

        // TODO: we have an actor/movie relationship, now what?
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
void ActorGraph::insertToGraph(string actor, string movie, int date) {
    string movieName = movie + "#@" + to_string(date);
    if (MovieList.find(movieName) == MovieList.end()) {
        if (ActorList.find(actor) == ActorList.end()) {
            ActorNode* newActor = new ActorNode(actor);
            Movie* newMovie = new Movie(movieName, date);
            (newActor->movie).push_back(newMovie);
            (newMovie->actors).push_back(actor);
            MovieList.insert(pair<string, Movie*>(movieName, newMovie));
            ActorList.insert(pair<string, ActorNode*>(actor, newActor));
        } else {
            ActorNode* currActor = ActorList[actor];
            Movie* newMovie = new Movie(movieName, date);
            (currActor->movie).push_back(newMovie);
            (newMovie->actors).push_back(actor);
            MovieList.insert(pair<string, Movie*>(movieName, newMovie));
        }
    } else {
        Movie* currMovie = MovieList[movieName];
        if (ActorList.find(actor) == ActorList.end()) {
            ActorNode* newActor = new ActorNode(actor);
            (newActor->movie).push_back(currMovie);
            (currMovie->actors).push_back(actor);
            ActorList.insert(pair<string, ActorNode*>(actor, newActor));
        } else {
            ActorNode* currActor = ActorList[actor];
            (currActor->movie).push_back(currMovie);
            (currMovie->actors).push_back(actor);
        }
    }
}

ActorGraph::~ActorGraph {}
