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

int main(int argc, char* argv[]) {
    ActorGraph graph;
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
        // cout << "123" << endl;
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
    // cout << "456" << endl;
    vector<ActorNode*> actors;
    for (string i : names) {
        actors.push_back(graph.ActorList[i]);
    }

    vector<vector<ActorNode*>> result1 = graph.predictForExist(actors);
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

        //      while (count < 4) {
        //        outFile1 << "";
        ///      count++;
        //     if (count < 4) {
        //         outFile1 << "\t";
        //     }
        //}

        outFile1 << endl;
    }
    outFile1.close();

    vector<vector<ActorNode*>> result2 = graph.predictForNew(actors);
    for (int i = 0; i < result2.size(); i++) {
        int count = 0;
        for (int k = 0; k < result2[i].size(); k++) {
            outFile2 << result2[i][k]->ActorName;
            count++;

            if (count < 4) {
                outFile2 << "\t";
            }
        }
        /*
        while (count < 4) {
            outFile2 << "NULL";
            count++;
            if (count < 4) {
                outFile2 << "\t";
            }
        } */
        outFile2 << endl;
    }
    outFile2.close();
    /*for(int i = 0; i< actors.size(); i++){
        delete actors[i];
    }*/
    return 0;
}