/*
 * ActorGraph.hpp
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Date:   12/03/2019
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
// class to help compare the distance
class CompareDit {
  public:
    bool operator()(pair<int, ActorNode*> pair1,
                    pair<int, ActorNode*> pair2) const {
        return pair1.first > pair2.first;
    }
};
// class to help compare the number for linkpredictor
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
 * a class, instances of the graph
 */
class ActorGraph {
  protected:
  public:
    unordered_map<string, ActorNode*> ActorList;  // all the actor
    unordered_map<string, ActorEdge*> edges;      // all the edge
    unordered_map<string, Movie*> movieList;      // all the movie
    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);
    // destructor of graph
    ~ActorGraph();

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
    /**
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
/**
 * write the bfs search for unweight graph and also Dijkstra's algorithm for
 * weighted graph
 * Param: start: the starting node
 *        end:the ending node
 *        weighted: whether the graph is weighted or not
 *        outFile: the output file to write
 */
    void findPath(string start, string end, bool weighted, ofstream& outFile);
/**
 * write the path by the prev
 * Para: acotr: the current actor to write
 *       outFile: the output file to write
 */
    void writeTheResultPath(ActorNode* actor, ofstream& outFile);
/**
 * build the graph with edge
 */
    void buildingGraph();
/**
 * build the edges from the movie
 * Para:
 * name: name of movie
 * movie: pointer to the movie
 */
    void buildingEdges(string name, Movie* movie, bool edge);
/**
 * check method to get the graph each components size
 */
    string returnSize();
/**
 * linkpredictor for already exist edges
 * Para: vector<ActorNode*> actors : actor list to search
 * Return : return the predict result for each actor of already existed edges
 */
    vector<vector<ActorNode*>> predictForExist(vector<ActorNode*> actors);
/**
 * linkpredictor for non-exist edges
 * Para: vector<ActorNode*> actors : actor list to search
 * Return : return the predict result for each actor of non-existed edges
 */
    vector<vector<ActorNode*>> predictForNew(vector<ActorNode*> actors);
/**
 * helper method to predict each actor individually for existed edges case
 * Para: ActorNode* actor: the specific actor node to predict
 * Return: return a vector list for predict result for this actor
 */
    vector<ActorNode*> helperForPredictExist(ActorNode* actor);
/**
 * helper method to predict non exist edges for each actor individually
 * Para: ActorNode* actor: the specific actor node to predict
 * Return: return a vector list for predict result for this actor
 */
    vector<ActorNode*> helperForPredictNew(ActorNode* actor);
};

#endif  // ACTORGRAPH_HPP
