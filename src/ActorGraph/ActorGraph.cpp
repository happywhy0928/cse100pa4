/*
 * ActorGraph.cpp
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Date:   12/03/2019
 *
 * This file is meant to exist as a container for starter code that you can use
 * to read the input file format defined in imdb_2019.tsv. Feel free to modify
 * any/all aspects as you wish.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <queue>
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

/**
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

        // search if the actor as node has been created or not
        if (ActorList.find(actor) == ActorList.end()) {
            ActorNode* newActor = new ActorNode(actor);
            ActorList[actor] = newActor;
        }

        // set the movie name in the format
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
/**
 * write the bfs search for unweight graph and also Dijkstra's algorithm for
 * weighted graph
 * Param: start: the starting node
 *        end:the ending node
 *        weighted: whether the graph is weighted or not
 *        outFile: the output file to write
 * Citation: get the idea from the discussion
 */
void ActorGraph::findPath(string start, string end, bool weighted,
                          ofstream& outFile) {
    for (auto start = ActorList.begin(); start != ActorList.end(); start++) {
        start->second->clean();
    }
    // create the priority queue
    priority_queue<pair<int, ActorNode*>, vector<pair<int, ActorNode*>>,
                   CompareDit>
        checklist;
    // find the start node
    auto startActor = ActorList.find(start);
    startActor->second->distance = 0;
    checklist.push(pair<int, ActorNode*>(0, startActor->second));
    // start to search
    while (checklist.size() > 0) {
        auto curr = checklist.top();
        checklist.pop();
        // if node is not done
        if (curr.second->done == false) {
            curr.second->done = true;
            if (curr.second->ActorName == end) {
                break;
            }
            // get the next actor in the edge sets
            for (auto edge : curr.second->edges) {
                auto checkActor = ActorList[edge->actor];
                if (checkActor->done == true) {
                    continue;
                }
                // calculate weight
                int weight;
                if (weighted == false) {
                    weight = 1;
                } else {
                    weight = 1 + 2019 - edge->getNewestMovie()->year;
                }
                // set the distance and prev
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
    // start to write the path
    writeTheResultPath(endActor, outFile);
}
/**
 * write the path by the prev
 * Para: acotr: the current actor to write
 *       outFile: the output file to write
 */
void ActorGraph::writeTheResultPath(ActorNode* actor, ofstream& outFile) {
    if (actor->prev == nullptr) {
        outFile << "(" << actor->ActorName << ")";
    } else {
        // recursively call the method
        writeTheResultPath(actor->prev, outFile);
        outFile << "--[" << actor->prevMovie << "]-->(" << actor->ActorName
                << ")";
    }
}
/**
 * build the graph with edge
 * Citation: get the idea from the discussion
 */
void ActorGraph::buildingGraph() {
    for (unordered_map<string, Movie*>::iterator x = movieList.begin();
         x != movieList.end(); x++) {
        buildingEdges(x->first, x->second, true);
    }
}
/**
 * build the edges from the movie
 * Para:
 * name: name of movie
 * movie: pointer to the movie
 * Citation: get the idea from the discussion
 */
void ActorGraph::buildingEdges(string name, Movie* movie, bool edge) {
    vector<string> actorSets = movie->actors;
    for (int i = 0; i < actorSets.size(); i++) {
        auto currActor = this->ActorList.find(actorSets[i]);
        for (int k = 0; k < actorSets.size(); k++) {
            if (i == k) {
                continue;
            }
            string currEdge = currActor->first + actorSets[k];
            // check if this edge for this movie added or not
            if (this->edges.find(currEdge) == this->edges.end()) {
                this->edges[currEdge] = new ActorEdge(actorSets[k]);
                this->edges[currEdge]->star1 = currActor->first;
                //   this->edges[currEdge]->star2 =
                //     this->ActorList.find(actorSets[k])->first;

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
/**
 * check method to get the graph each components size
 */
string ActorGraph::returnSize() {
    string result1 = to_string(ActorList.size());
    string result2 = to_string(movieList.size());
    string result3 = to_string(edges.size());
    return result1 + 'a' + result2 + 'b' + result3;
}
/**
 * linkpredictor for already exist edges
 * Para: vector<ActorNode*> actors : actor list to search
 * Return : return the predict result for each actor of already existed edges
 */
vector<vector<ActorNode*>> ActorGraph::predictForExist(
    vector<ActorNode*> actors) {
    // auto pq = priority_queue <
    // cout << actors.size() << endl;
    for (auto x : ActorList) {
        x.second->clean();
    }
    vector<vector<ActorNode*>> result(actors.size());
    // start to seach for each actor specific
    for (int i = 0; i < actors.size(); i++) {
        vector<ActorNode*> temp1 = helperForPredictExist(actors[i]);
        for (int j = 0; j < temp1.size(); j++) {
            //  cout << temp1[j]->ActorName << endl;
            result[i].push_back(temp1[j]);
            //  cout << temp1[j]->ActorName << endl;
        }
    }
    //  cout << "correct" << endl;
    return result;
}
/**
 * helper method to predict each actor individually
 * Para: ActorNode* actor: the specific actor node to predict
 * Return: return a vector list for predict result for this actor
 */
vector<ActorNode*> ActorGraph::helperForPredictExist(ActorNode* actor) {
    for (auto start = ActorList.begin(); start != ActorList.end(); start++) {
        start->second->clean1();
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
        //   cout << start->ActorName << endl;
        //   cout << start->edges.size() << endl;

        // first search each edge for this actor
        for (auto edge : start->edges) {
            auto currActor1 = ActorList[edge->actor];
            // cout << currActor1->ActorName << endl;
            // cout << "list1" << endl;
            currActor1->alcheck = true;
            if (currActor1->done == true) {
                continue;
            }
            int relation = 0;
            // search the next neighbor which have common neighbor with first
            for (auto edge1 : start->edges) {
                auto currActor2 = ActorList[edge1->actor];
                //  cout << currActor2->ActorName << endl;
                // cout << "list2" << endl;
                if (currActor2 == currActor1) {
                    continue;
                }
                for (auto edge2 : currActor1->edges) {
                    auto checkFor2 = ActorList[edge2->actor];
                    // cout << checkFor2->ActorName << endl;
                    // cout << "list3" << endl;
                    if (checkFor2 == currActor2) {
                        currActor1->done = true;
                        relation += edge1->movies.size() * edge2->movies.size();
                        //  cout << currActor1->ActorName << endl;
                        // cout << "input" << endl;
                    }
                }
            }
            currActor1->done = true;
            pq.push(pair<int, ActorNode*>(relation, currActor1));
        }
    }
    // get the result of predict start to get the top 4
    vector<ActorNode*> result;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        //  cout << count << endl;
        if (pq.empty() == true) {
            break;
        }
        if (count == 4) {
            break;
        }
        result.push_back(pq.top().second);
        pq.pop();
        count++;
        //  cout << count << endl;
    }
    // cout << result.size() << endl;
    return result;
}
/**
 * linkpredictor for non-exist edges
 * Para: vector<ActorNode*> actors : actor list to search
 * Return : return the predict result for each actor of non-existed edges
 */
vector<vector<ActorNode*>> ActorGraph::predictForNew(
    vector<ActorNode*> actors) {
    for (auto x : ActorList) {
        x.second->clean1();
    }
    vector<vector<ActorNode*>> result(actors.size());
    // using helper method to search for each actor specific
    for (int i = 0; i < actors.size(); i++) {
        vector<ActorNode*> temp1 = helperForPredictNew(actors[i]);
        for (int j = 0; j < temp1.size(); j++) {
            result[i].push_back(temp1[j]);
        }
    }
    return result;
}
/**
 * helper method to predict non exist edges for each actor individually
 * Para: ActorNode* actor: the specific actor node to predict
 * Return: return a vector list for predict result for this actor
 */
vector<ActorNode*> ActorGraph::helperForPredictNew(ActorNode* actor) {
    for (auto start = ActorList.begin(); start != ActorList.end(); start++) {
        start->second->clean1();
    }
    priority_queue<pair<int, ActorNode*>, vector<pair<int, ActorNode*>>,
                   CompareRelationship>
        pq;
    vector<ActorNode*> NodeList;
    ActorNode* start = actor;
    start->distance = 0;
    pq.push(pair<int, ActorNode*>(0, start));
    // while (pq.size() > 0) {
    auto curr = pq.top();
    pq.pop();
    // first get all the possible choice which do not have edge with actor of
    // parameter
    if (!curr.second->done) {
        curr.second->done = true;
        // all the neighbor of actor
        for (auto edge : start->edges) {
            auto temp = ActorList[edge->actor];
            // all the neighbor of neighbor and add to check if is not neightbor
            // of actor

            for (auto edge1 : temp->edges) {
                auto currActor1 = ActorList[edge1->actor];
                if (currActor1->done == true) {
                    continue;
                }
                currActor1->done = true;

                bool neighbor = false;
                /*
                for (auto edge2 : currActor1->edges) {
                    auto check = ActorList[edge2->actor];
                    if (check == start) {
                        neighbor = true;
                        break;
                    }
                }*/
                // cout << "123456" << endl;
                if (currActor1->alcheck == true) {
                    neighbor = true;
                    continue;
                }
                if (neighbor == false) {
                    NodeList.push_back(currActor1);
                }

                // int relation  = 0;
            }
        }
    }
    // start to calculate for each possible
    for (int i = 0; i < NodeList.size(); i++) {
        auto check1 = NodeList[i];
        int relation = 0;
        for (auto edge : check1->edges) {
            auto check2 = ActorList[edge->actor];
            for (auto edge1 : check2->edges) {
                auto check3 = ActorList[edge1->actor];
                if (check3 == start) {
                    relation += edge->movies.size() * edge1->movies.size();
                }
            }
        }
        pq.push(pair<int, ActorNode*>(relation, check1));
    }
    vector<ActorNode*> result;
    int count = 0;
    // start to get the top four
    for (int i = 0; i < 4; i++) {
        //  cout << count << endl;
        if (pq.empty() == true) {
            break;
        }
        if (count == 4) {
            break;
        }
        result.push_back(pq.top().second);
        pq.pop();
        count++;
        //  cout << count << endl;
    }
    // cout << result.size() << endl;
    return result;
}