#include <fstream>
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
    graph.buildGraph();
}
