//Id-9115
//Email address- orgoren3146@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>

using namespace std;
using namespace ariel;
using namespace doctest;


TEST_CASE("Testing == operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph1);
    CHECK((g1==g2)==true);

SUBCASE("Testing != operator"){
    ariel::Graph g3;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}};
    g3.loadGraph(graph);
    CHECK((g1!=g3)==true);
    }
}


TEST_CASE("Addition test")
{
    Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    CHECK((g3 == g4) == true);
    CHECK_FALSE((g3 == g1) == true);



    SUBCASE("Test addition with +=")
    {
        g2 += g1;
        CHECK_FALSE((g2 != g4) == true);
        CHECK((g2 != g3) == false);
    }

    SUBCASE("Test unary +")
    {
        ariel::Graph g5 = +g1;
        CHECK((g5 == g1) == true);
    }

    SUBCASE("Test algorithms")
    {
        CHECK(g3.getIsDirected() == false);
        CHECK(ariel::Algorithms::isConnected(g3) == true);
        CHECK(ariel::Algorithms::shortestPath(g3, 1, 2) == "Shortest path from vertex 1 to vertex 2: 1->2");
        CHECK(ariel::Algorithms::isContainsCycle(g3) == "The cycle is: 0->1->0");
         CHECK(ariel::Algorithms::isBipartite(g3) == "0");
        
    }
}


TEST_CASE("Subtraction test")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
 
    g1.loadGraph(graph);
 
    ariel::Graph g2;
 
    vector<vector<int>> weightedGraph = {
        {0, 2, 0, 0},
        {1, 0, 4, 7},
        {0, 1, 0, 0},
        {0, 2, 6, 0}};
 
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;

    vector<vector<int>> expectedGraph = {
        {0, -1,  0,  1},
        {0,  0, -3, -7},
        {0,  0,  0,  0},
        {0, -1, -6,  0}};
    
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);
    CHECK((g3 == g4) == true);
    CHECK_FALSE((g1!=g2)==false);

    SUBCASE("Test subtraction with -= operator")
    {
        g1 -= g2;
        CHECK((g1 == g4) == true);
        CHECK((g1 != g3) == false);
    }

    SUBCASE("Test unary -")
    {
        g1 -= g2;
        ariel::Graph g5 = -g1;
        g4 = -g4;
        
        CHECK((g5 == g4) == true);

        g5 = -g5;

        CHECK_FALSE((g5 == g1) == true);
    }

    
}

TEST_CASE("multiplication test")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {2, 0, 0}};
    ariel::Graph g5;
    g5.loadGraph(expectedGraph);
    CHECK((g4 == g5) == true);

    SUBCASE("Test multiplication by operator *=")
    {
        g2 *= 4;
        vector<vector<int>> expectedGraph = {
            {0, 8, 4},
            {8, 0, 8},
            {4, 8, 0}};
        ariel::Graph g6;
        g6.loadGraph(expectedGraph);
        CHECK((g2 == g6) == true);

    }

    SUBCASE("Test a big weighted graphs multiplication")
    {
        ariel::Graph g7;
        vector<vector<int>> weightedGraph2 = {
            {0, 1, 1, -1, 1,3},
            {1, 0, -7, 1, 4,5},
            {-25, 1, 0, 2,1,6},
            {1, 0, 1, 0, 1, 2},
            {4, 1, -1, 3, 0, 4},
            {7, 0, 2, 1, 0, 0}};
        g7.loadGraph(weightedGraph2);

        vector<vector<int>> weightedGraph3 = {
            {0, -1, 3, 2, 0,3},
            {1, 0, -2, 6, 8,-5},
            {-9, 7, 0, 6,-1,0},
            {30, 1, 0, 0, 1, 2},
            {-4, 8, 0, 3, 0, 4},
            {17, 0, -2, 11, 0, 0}};
        ariel::Graph g8;
        g8.loadGraph(weightedGraph3);
        ariel::Graph g9 = g7 * g8;
        vector<vector<int>> expectedGraph2 = {
            {0, 14, -8, 48, 6,-3},
            {162, 0, -7, 27, 8,21},
            {159, 35, 0, 25,10,-72},
            {21, 14, -1, 0, -1, 7},
            {168, -8, 2, 52, 0, 13},
            {12, 8, 21, 26, -1, 0}};
        ariel::Graph g10;
        g10.loadGraph(expectedGraph2);
        CHECK_FALSE((g9 == g10) == false);
    }
}


TEST_CASE("Test errors in computing operators")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g2.loadGraph(graph1);

    //check if there is exception while trying to make addition of two graphs with different dimensions
    CHECK_THROWS(g1 + g2);
    CHECK_THROWS(g1 += g2);


SUBCASE("TEST subtraction of two graphs with different dimensions")
    {
        ariel::Graph g3;
        vector<vector<int>> graph2 = {
            {0, 1},
            {1, 0}};

    CHECK_THROWS(g1 - g3);
    CHECK_THROWS(g1 -= g3);

    }
SUBCASE("TEST multiplication of two graphs with different dimensions")
    {
        ariel::Graph g4;
        vector<vector<int>> graph3 = {
            {0, 1},
            {1, 0}};
    CHECK_THROWS(g1 * g4);

    }
}


TEST_CASE("Testing comparison operators")
{

    // Test operator > by containing
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph1);
    
    //g2 contained in g1
    CHECK((g1>g2)==true);
    CHECK((g2<g1)==true);
    
SUBCASE("Test operator > by number of edges"){
    
    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 2},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph2);
    ariel::Graph g4;
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph3);

    // None of the graphs contains the other and g3 have more edges than g4
    CHECK((g3>g4)==true);
    CHECK((g4<g3)==true);
}

SUBCASE("Test operator > by number of vetices"){
    
    ariel::Graph g5;
    vector<vector<int>> graph4 = {
        {0, 1, 0,0,0},
        {1, 0, 0,0,0},
        {0, 0, 0,0,0},
        {0, 0, 0,0,0},
        {0, 0, 0,0,0}};
    g5.loadGraph(graph4);
    ariel::Graph g6;
    vector<vector<int>> graph5 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g6.loadGraph(graph5);

    // None of the graphs contains the other, they have equal number of edges and g5 have more vertices than g6
    CHECK((g5>g6)==true);
    CHECK((g5<g6)==false);
    }

SUBCASE("Test operator >= operator"){

   ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0,0,0},
        {1, 0, 0,0,0},
        {0, 0, 0,0,0},
        {0, 0, 0,0,0},
        {0, 0, 0,0,0}};
    g1.loadGraph(graph1);
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(graph2);
    ariel::Graph g3= +g2;
    CHECK((g1>=g2)==true);
    CHECK((g2>=g3)==true);
    
    //Test <= operator
    CHECK((g2<=g1)==true);
    CHECK((g3<=g2)==true);
    }
}

TEST_CASE("Testing increment and decrement operators"){

//Test ++x and --x operators
 ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3=++g1; 
    CHECK((g3==g2)==true);
    g3=g2--;
    CHECK((g3!=g2)==true);

SUBCASE("Test x++ and x-- operators"){
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    
    ariel::Graph g3=g1++;
    CHECK((g2==g1)==true);
    --g1;
    CHECK((g3==g1)==true);
}

}

