/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: this file finds the linkpredict for exist edges and non-existed
 * edges
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorEdge.hpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "cxxopts.hpp"

using namespace std;
// main function to linkpredict
int main(int argc, char* argv[]) {
    ActorGraph graph;

    // build the graph
    graph.loadFromFile(argv[1], false);
    graph.buildingGraph();
    ifstream inFile(argv[2]);
    ofstream outFile1(argv[3]);
    ofstream outFile2(argv[4]);

    bool header = false;

    vector<string> names;
    while (inFile) {
        string temp;

        if (!getline(inFile, temp)) {
            break;
        }
        if (!header) {
            // cout << "aaa" << endl;
            header = true;
            outFile1 << "Actor1,Actor2,Actor3,Actor4" << endl;
            outFile2 << "Actor1,Actor2,Actor3,Actor4" << endl;
            continue;
        }
        // get all the names to search
        istringstream iss(temp);
        while (iss) {
            string next;
            if (!getline(iss, next)) {
                break;
            }
            names.push_back(next);
        }
    }
    inFile.close();
    vector<ActorNode*> actors;
    for (string i : names) {
        actors.push_back(graph.ActorList[i]);
    }
    vector<vector<ActorNode*>> result1(actors.size());
    vector<vector<ActorNode*>> result2(actors.size());
    for (int i = 0; i < actors.size(); i++) {
        for (auto x : graph.ActorList) {
            x.second->clean();
        }
        vector<ActorNode*> temp1 = graph.helperForPredictExist(actors[i]);
        for (int j = 0; j < temp1.size(); j++) {
            result1[i].push_back(temp1[j]);
        }
        vector<ActorNode*> temp2 = graph.helperForPredictNew(actors[i]);
        for (int j = 0; j < temp2.size(); j++) {
            result2[i].push_back(temp2[j]);
        }
    }
    // start to predict for existed edges
    // vector<vector<ActorNode*>> result1 = graph.predictForExist(actors);
    for (int i = 0; i < result1.size(); i++) {
        int count = 0;
        for (int k = 0; k < result1[i].size(); k++) {
            outFile1 << result1[i][k]->ActorName;
            count++;
            // cout << result1[i][k]->ActorName << endl;
            if (count < 4) {
                outFile1 << "\t";
            }
        }

        outFile1 << endl;
    }
    outFile1.close();
    // start to predict for non-existed edges
    // vector<vector<ActorNode*>> result2 = graph.predictForNew(actors);
    for (int i = 0; i < result2.size(); i++) {
        int count = 0;
        for (int k = 0; k < result2[i].size(); k++) {
            outFile2 << result2[i][k]->ActorName;
            count++;

            if (count < 4) {
                outFile2 << "\t";
            }
        }
        outFile2 << endl;
    }
    outFile2.close();
    return 0;
}