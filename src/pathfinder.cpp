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

int main(int argc, char** argv) {
    ActorGraph graph;
    bool weighted;
    if (*(argv[2]) == 'w') {
        weighted = true;
    }

    else {
        weighted = false;
    }
    graph.loadFromFile(argv[1], weighted);
    graph.buildingGraph();

    ofstream outFile;
    outFile.open(argv[4]);
    bool header = false;
    ifstream infile(argv[3]);

    while (infile) {
        string temp;

        if (!getline(infile, temp)) {
            break;
        }
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
        graph.findPath(memory[0], memory[1], weighted, outFile);
    }
}
