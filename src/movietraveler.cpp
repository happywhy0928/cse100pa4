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

int main(int argc, char** argv) {
    ActorGraph* graph;
    cout << "wenti99" << endl;
    graph->loadFromFile(argv[1], true);
    cout << "wenti100" << endl;
    graph->buildingGraph();
    cout << "wenti101" << endl;
    ofstream outfile(argv[2]);

    int numActors = graph->ActorList.size();
    outfile << "(actor)<--[movie#@year]-->(actor)" << endl;
    vector<ActorEdge*> edgeList;
    cout << "wenti" << endl;
    for (auto edge : graph->edges) {
        edgeList.push_back(edge.second);
        edge.second->weight = 1 + 2019 - edge.second->getNewestMovie()->year;
    }
    sort(edgeList.begin(), edgeList.end(), ActorEdge::CompareWeight());
    DisjointSets sets = DisjointSets(graph, numActors);
    cout << "wenti1" << endl;
    int edgesChosen = 0;
    int edgeWeights = 0;
    for (ActorEdge* edge : edgeList) {
        ActorNode* temp1 = graph->ActorList.find(edge->star1)->second;
        ActorNode* temp2 = graph->ActorList.find(edge->star2)->second;
        ActorNode* find1 = sets.find(temp1);
        ActorNode* find2 = sets.find(temp2);
        cout << "wenti2" << endl;
        if (find1 != find2) {
            sets.unionSets(temp1, temp2);
            outfile << "(" << temp1->ActorName << ")<--["
                    << edge->newestMovie->MovieName << "#@"
                    << edge->newestMovie->year << "]-->(" << temp2->ActorName
                    << ")" << endl;

            edgesChosen++;
            edgeWeights += edge->weight;
        }
        if (edgesChosen == numActors - 1) {
            break;
        }
    }
}