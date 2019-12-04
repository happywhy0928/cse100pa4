/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: this file finds the MST
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorEdge.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "DisjointSets.hpp"
#include "cxxopts.hpp"

using namespace std;
//the main function to find the MST
int main(int argc, char** argv) {
    ActorGraph graph;
    //build the graph
    graph.loadFromFile(argv[1], true);
    graph.buildingGraph();
    ofstream outfile(argv[2]);

    int numActors = graph.ActorList.size();
    outfile << "(actor)<--[movie#@year]-->(actor)" << endl;
    vector<ActorEdge*> edgeList;
    //start to sort all the edge by the weight
    for (auto edge : graph.edges) {
        edgeList.push_back(edge.second);
        edge.second->weight = 1 + 2019 - edge.second->getNewestMovie()->year;
    }
    sort(edgeList.begin(), edgeList.end(), ActorEdge::CompareWeight());
    DisjointSets sets = DisjointSets(&graph);
    int edgesInMST = 0;
    int totalWeights = 0;
    //start to find the MST
    for (ActorEdge* edge : edgeList) {
        ActorNode* temp1 = graph.ActorList.find(edge->star1)->second;
        ActorNode* temp2 = graph.ActorList.find(edge->star2)->second;
        ActorNode* find1 = sets.find(temp1);
        ActorNode* find2 = sets.find(temp2);
        //find the path to write
        if (find1 != find2) {
            sets.unionSets(temp1, temp2);
            outfile << "(" << temp1->ActorName << ")<--["
                    << edge->newestMovie->MovieName << "]-->("
                    << temp2->ActorName << ")" << endl;

            edgesInMST++;
            totalWeights += edge->weight;
        }
        //to avoid the cycle
        if (edgesInMST == numActors - 1) {
            break;
        }
    }
    //format the result
    outfile << "#NODE CONNECTED: " << numActors << endl;
    outfile << "#EDGE CHOSEN: " << edgesInMST << endl;
    outfile << "TOTAL EDGE WEIGHTS: " << totalWeights << endl;

    outfile.close();
    return 0;
}