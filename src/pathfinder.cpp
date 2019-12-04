/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: this file finds the shortest path
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
//main function to find the shortest path 
int main(int argc, char** argv) {
    ActorGraph graph;
    bool weighted;
    //weighted or unweighted
    if (*(argv[2]) == 'w') {
        weighted = true;
    }

    else {
        weighted = false;
    }
    //build the graph
    graph.loadFromFile(argv[1], weighted);
    graph.buildingGraph();
bool header = false;
    ofstream outFile;
    outFile.open(argv[4]);
    ifstream infile(argv[3]);
    
    while (infile) {
        string temp;

        if (!getline(infile, temp)) {
            break;
        }
        //write the header
        if (!header) {
            header = true;
            outFile << "(actor)--[movie#@year]-->(actor)--..." << endl;
            continue;
        }
        vector<string> memory;
        istringstream iss(temp);

        while (iss) {
            string next;
            if (!getline(iss, next, '\t')) {
                break;
            }
            memory.push_back(next);
        }
        if (memory.size() != 2) {
            continue;
        }
        //write path
        graph.findPath(memory[0], memory[1], weighted, outFile);
        outFile << endl;

    }
    return 0;
}
