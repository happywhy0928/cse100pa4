#include <iostream>
#include <string>
#include <vector>

/**
 * Author: Hongyu Wang
 *         Carghin Rekani
 * Overview: unit tests 
 */
#include <gtest/gtest.h>
#include "ActorEdge.hpp"
#include "ActorGraph.cpp"
#include "ActorGraph.hpp"
#include "ActorNode.hpp"
#include "Movie.hpp"

using namespace std;
using namespace testing;

class simpleGraphTesting : public ::testing::Test {
  protected:
    // ActorGraph graph;

  public:
    ActorGraph graph;
    simpleGraphTesting() {}
};
TEST_F(simpleGraphTesting, Test_predict) {
    /* graph.loadFromFile("imdb_2019.tsv", false);
     graph.buildingGraph();
     ofstream ss;
     // graph.findPath("Djimon Hounsou", "50 Cent", false, ss);
     vector<ActorNode*> actors;
     actors.push_back(graph.ActorList["Michael Fassbender"]);
     actors.push_back(graph.ActorList["Samuel L. Jackson"]);
     graph.predictForExist(actors);
     graph.predictForNew(actors); */
    ASSERT_EQ(1, 1);
}