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
        int countNumOfEdges(vector<vector<int>> gr) ;

    public:
    
        Graph() {
            this->isDirected=false;
            bool isWeighed =false;
            this->numOfEdges=0;
            this->numOfVertices=0;
          
        }

        void loadGraph(vector<vector<int>> gr);
        void printGraph() const;

        // inline methods
        bool getIsDirected() const
        { 
            return this->isDirected;
        }
        bool getIsWeighed() const
        { 
            return this->isWeighed;
        }
        int getNumOfVertices() const
        { 
            return this->numOfVertices;
        }
        int getNumOfEdges() const
        {
            return this->numOfEdges;
        }
        vector<vector<int>> getGraph() const
        { 
            return this->graph;
        }
       

        // operator methods
        // The computing comperators

        // The + operator
        Graph operator + (const Graph g1) const;
        Graph& operator += (Graph g1);
        Graph& operator + ();


        // The - operator
        
        Graph operator - (const Graph g1)const ;
        Graph& operator -= (Graph g1);
        Graph& operator - ();

        // The * operator
        Graph operator * (const Graph g1)const;
        Graph&  operator *= (const int num);

        // The division operator
        Graph&  operator /= (int num);

        // The equality operators
        void operator = ( Graph g1);
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