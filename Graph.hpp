//Id-9115
//Email address- orgoren3146@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <vector>
using namespace std;

namespace ariel
{
    class Graph
    {

    private:
        vector<vector<int>> graph;
        bool isDirected;
        bool isWeighed ;
        int numOfVertices;
        int numOfEdges;
        int countNumOfEdges(const vector<vector<int>> &gr);
    
    public:
    
        Graph();
        void loadGraph(const vector<vector<int>> &gr);
        void printGraph() const;
        bool getIsDirected() const;
        bool getIsWeighed() const;
        int getNumOfVertices() const;
        int getNumOfEdges() const;
        vector<vector<int>> getGraph() const;
       

        // operator methods
        // The computing comperators

        // The + operator
        Graph operator + (const Graph g1) ;
        Graph& operator += (const Graph g1);
        Graph& operator + ();


        // The - operator
        
        Graph operator - (const Graph g1) ;
        Graph& operator -= (const Graph g1);
        Graph& operator - ();

        // The * operator
        Graph operator * (const Graph g1);
        Graph&  operator *= (int num);

        // The division operator
        Graph&  operator /= (int num);

        // The equality operators
        void operator = ( const Graph g1);
        bool operator == (const Graph g1)const;
        bool operator != (const Graph g1)const;
        bool operator > (const Graph& g1) const;
        bool operator >= (const Graph& g1) const;
        bool operator <(const Graph& g1) const;
        bool operator <= (const Graph& g1) const;
        
       // The print operator
        friend ostream& operator<<(ostream& os,const Graph &gr) ;
        
        // Increment/ decrement by 1
        Graph& operator++ ();
        Graph operator++ (int num);
        Graph& operator-- ();
        Graph operator-- (int num);
        
        
    };
}

#endif
