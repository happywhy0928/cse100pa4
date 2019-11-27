/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <queue>
#include <unordered_map>;
#include "ActorEdge.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"
// Maybe include some data structures here

using namespace std;
class CompareDit {
  public:
    bool operator()(pair<int, ActorNode*> pair1,
                    pair<int, ActorNode*> pair2) const {
        return pair1.first > pair2.first;
    }
};
class CompareRelationship {
  public:
    bool operator()(pair<int, ActorNode*> pair1,
                    pair<int, ActorNode*> pair2) const {
        if (pair1.first != pair2.first) {
            return pair1.first < pair2.first;
        } else {
            return pair1.second->ActorName > pair2.second->ActorName;
        }
    }
};
/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // Maybe add class data structure(s) here
    /*   unordered_map<string, ActorNode*> ActorList;
       unordered_map<string, ActorEdge*> edges;
       unordered_map<string, Movie*> movieList; */
    // vector<ActorEdge*> edges;

  public:
    /**
     * Constuctor of the Actor graph
     */
    unordered_map<string, ActorNode*> ActorList;
    unordered_map<string, ActorEdge*> edges;
    unordered_map<string, Movie*> movieList;
    ActorGraph(void);
    ~ActorGraph();

    // Maybe add some more methods here

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
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
    void BFSForSearch(string root);
    void findPath(string start, string end, bool weighted, ofstream& outFile);
    void writeTheResultPath(ActorNode* actor, ofstream& outFile);
    void buildingGraph();
    void buildingEdges(string name, Movie* movie, bool edge);
    string returnSize();
    vector<vector<ActorNode*>> predictForExist(vector<ActorNode*> actors);
    vector<vector<ActorNode*>> predictForNew(vector<ActorNode*> actors);
    vector<ActorNode*> helperForPredictExist(ActorNode* actor);
    vector<ActorNode*> helperForPredictNew(ActorNode* actor);
};

#endif  // ACTORGRAPH_HPP
