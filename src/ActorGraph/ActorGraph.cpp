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
        // cout << "999" << endl;
        string actor(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship, now what?
        if (ActorList.find(actor) == ActorList.end()) {
            ActorNode* newActor = new ActorNode(actor);
            ActorList[actor] = newActor;
        }
        string movie = movie_title + "#@" + to_string(year);
        if (movieList.find(movie) == movieList.end()) {
            Movie* newMovie = new Movie(movie, year);
            movieList[movie] = newMovie;
            newMovie->actors.push_back(actor);
        } else {
            auto curMovie = movieList.find(movie);
            curMovie->second->actors.push_back(actor);
        }
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
}
void ActorGraph::findPath(string start, string end, bool weighted,
                          ofstream& outFile) {
    for (auto start = ActorList.begin(); start != ActorList.end(); start++) {
        start->second->clean();
    }
    priority_queue<pair<int, ActorNode*>, vector<pair<int, ActorNode*>>,
                   CompareDit>
        checklist;
    auto startActor = ActorList.find(start);
    startActor->second->distance = 0;
    checklist.push(pair<int, ActorNode*>(0, startActor->second));
    while (checklist.size() > 0) {
        auto curr = checklist.top();
        checklist.pop();
        if (curr.second->done == false) {
            curr.second->done = true;
            if (curr.second->ActorName == end) {
                break;
            }

            for (auto edge : curr.second->edges) {
                auto checkActor = ActorList[edge->actor];
                if (checkActor->done == true) {
                    continue;
                }
                int weight = 1;
                if (checkActor->distance == -1) {
                    checkActor->distance = curr.second->distance + weight;
                    //  checkActor->prevMovie = edge->movies[0]->MovieName;

                    checkActor->prevMovie = edge->getNewestMovie()->MovieName;
                    checkActor->prev = curr.second;
                    checklist.push(pair<int, ActorNode*>(checkActor->distance,
                                                         checkActor));
                } else if (checkActor->distance >
                           curr.second->distance + weight) {
                    checkActor->distance = curr.second->distance + weight;
                    //   checkActor->prevMovie = edge->movies[0]->MovieName;

                    checkActor->prevMovie = edge->getNewestMovie()->MovieName;
                    checkActor->prev = curr.second;
                    checklist.push(pair<int, ActorNode*>(checkActor->distance,
                                                         checkActor));
                }
            }
        }
    }
    auto endActor = ActorList[end];
    writeTheResultPath(endActor, outFile);
}
void ActorGraph::writeTheResultPath(ActorNode* actor, ofstream& outFile) {
    if (actor->prev == nullptr) {
        outFile << "(" << actor->ActorName << ")";
    } else {
        writeTheResultPath(actor->prev, outFile);
        outFile << "--[" << actor->prevMovie << "]-->(" << actor->ActorName
                << ")";
    }
}
void ActorGraph::buildingGraph() {
    for (unordered_map<string, Movie*>::iterator x = movieList.begin();
         x != movieList.end(); x++) {
        buildingEdges(x->first, x->second, true);
    }
}
void ActorGraph::buildingEdges(string name, Movie* movie, bool edge) {
    vector<string> actorSets = movie->actors;
    for (int i = 0; i < actorSets.size(); i++) {
        auto currActor = this->ActorList.find(actorSets[i]);
        for (int k = 0; k < actorSets.size(); k++) {
            if (i == k) {
                continue;
            }
            string currEdge = currActor->first + actorSets[k];
            if (this->edges.find(currEdge) == this->edges.end()) {
                this->edges[currEdge] = new ActorEdge(actorSets[k]);
                currActor->second->edges.push_back(this->edges[currEdge]);
                if (edge) {
                    auto temp = this->edges.find(currEdge);
                    temp->second->movies.push_back(movie);
                }
            } else {
                if (edge) {
                    auto temp = this->edges.find(currEdge);
                    temp->second->movies.push_back(movie);
                } else {
                    continue;
                }
            }
        }
    }
}
ActorGraph::~ActorGraph() {
    for (auto i : ActorList) {
        delete i.second;
    }
    for (auto i : movieList) {
        delete i.second;
    }
    for (auto i : edges) {
        delete i.second;
    }
}
string ActorGraph::returnSize() {
    string result1 = to_string(ActorList.size());
    string result2 = to_string(movieList.size());
    string result3 = to_string(edges.size());
    return result1 + 'a' + result2 + 'b' + result3;
}
vector<vector<ActorNode*>> ActorGraph::predictForExist(
    vector<ActorNode*> actors) {
    // auto pq = priority_queue <
    vector<vector<ActorNode*>> pq;
    for (int i = 0; i < actors.size(); i++) {
        pq[i] = helperForPredictExist(actors[i]);
    }
    return pq;
}
vector<ActorNode*> ActorGraph::helperForPredictExist(ActorNode* actor) {
    for (auto start = ActorList.begin(); start != ActorList.end(); start++) {
        start->second->clean();
    }
    priority_queue<pair<int, ActorNode*>, vector<pair<int, ActorNode*>>,
                   CompareRelationship>
        pq;
    ActorNode* start = actor;
    start->distance = 0;
    pq.push(pair<int, ActorNode*>(0, start));
    // while (pq.size() > 0) {
    auto curr = pq.top();
    pq.pop();
    if (!curr.second->done) {
        curr.second->done = true;

        for (auto edge : curr.second->edges) {
            auto currActor1 = ActorList[edge->actor];
            if (currActor1->done == true) {
                continue;
            }
            for (auto edge1 : curr.second->edges) {
                auto currActor2 = ActorList[edge1->actor];
                if (currActor2 == currActor1) {
                    continue;
                }
                for (auto edge2 : currActor1->edges) {
                    auto checkFor2 = ActorList[edge2->actor];
                    if (checkFor2 == currActor2) {
                        currActor1->done = true;
                        pq.push(pair<int, ActorNode*>(
                            edge1->movies.size() * edge2->movies.size(),
                            currActor1));
                    }
                }
            }
        }
        //  }
    }
    cout << pq.size() << endl;
    vector<ActorNode*> result;
    if (pq.empty() == false) {
        for (int i = 0; i < 4; i++) {
            result[i] = pq.top().second;
            pq.pop();
            if (pq.empty() == true) {
                break;
            }
        }
    }
}
vector<vector<ActorNode*>> ActorGraph::predictForNew(
    vector<ActorNode*> actors) {
    // auto pq = priority_queue <
    vector<vector<ActorNode*>> pq;
    return pq;
}