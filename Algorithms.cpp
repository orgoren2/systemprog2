//Id-9115
//Email address- orgoren3146@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#define INFINITE 99999

using namespace std;
using namespace ariel;

/*
Bfs algorithm for checking if the graph is connected.
The output of it is a bool array that indicates which vertex we checked.
If one of the cells in the array is false, the graph is not connected.
 */
bool Algorithms::isConnected(Graph gr)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();
    vector<bool> isPath(numOfVertices, false);
    queue<int> q;
    q.push(0);
    isPath[0] = true;

    while (!q.empty())
    {
        size_t vertex = (size_t)q.front();
        q.pop();

        for (size_t i = 0; i < numOfVertices; i++)
        {
            if (graph[vertex][i] && !isPath[i])
            {
                q.push(i);
                isPath[i] = true;
            }
        }
    }

    for (size_t i = 0; i < numOfVertices; i++)
    {
        if (!isPath[i])
        {
            return false;
        }
    }

    return true;
}

/**
 * Split the shortest path check to 2 functions:
 * If the graph is weighed use the Bellman Ford algorithm
 * If the graph is Unweighed
 */
string Algorithms::shortestPath(Graph gr, size_t start, size_t end)
{
    string s;
    if (gr.getIsWeighed())
    {
        s=shortestPathWeighed(gr, start, end);
        
    }
    else
    {
        s=shortestPathUnweighed(gr, start, end);
    
    }
    return s;
}

// Bellman ford algorithm for finding the shortest path in weighed graph
string Algorithms::shortestPathWeighed(Graph gr, size_t start, size_t end)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();
    vector<int> distance(numOfVertices, INFINITE);
    vector<size_t> parent(numOfVertices, (size_t)-1); 
    distance[start] = 0;

    for (size_t i = 0; i < numOfVertices - 1; i++)
    {
        for (size_t u = 0; u < numOfVertices; u++)
        {
            for (size_t v = 0; v < numOfVertices; v++)
            {
                if (graph[u][v] && distance[u] != INFINITE && distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u; 
                }
            }
        }
    }

    string path= "Shortest path from vertex "+ to_string(start)+ " to vertex " +to_string(end) +": ";
    size_t currentVertex = end ;
     stack<size_t> sPath;
    while (currentVertex != -1)
    {
        sPath.push(currentVertex);
        currentVertex = parent[currentVertex];
    }
   
    while(!sPath.empty()){
         path = path + to_string(sPath.top() ); 
         sPath.pop();
          if (!sPath.empty())
                    {
                        path = path + "->";
                    }
    }
    if (distance[end] == INFINITE)
    {
        return "-1"; 
    }

    return path;
}

// Bfs algorithm for finding the shortest path in unweighed graph
string Algorithms::shortestPathUnweighed(Graph gr, size_t start, size_t end)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)graph.size();
    vector<size_t> distance(numOfVertices,(size_t) -1); 
    vector<size_t> parent(numOfVertices, (size_t)-1); 

    queue<size_t> q;
    q.push(start);
    distance[start] = 0; 

    while (!q.empty())
    {
        size_t currentVertex = q.front();
        q.pop();

        if (currentVertex == end)
        {
            break;
        }
        
        for (size_t neighborVertex = 0; neighborVertex < numOfVertices; neighborVertex++)
        {
            if (graph[currentVertex][neighborVertex] && distance[neighborVertex] == -1)
            {
                distance[neighborVertex] = distance[currentVertex] + 1; 
                parent[neighborVertex] = currentVertex; 
                q.push(neighborVertex); 
            }
        }
    }

    if (distance[end] == -1)
    {
        return "-1";
    }

    vector<size_t> path;
    for (size_t v = end; v != -1; v = parent[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end()); 


    string s= "Shortest path from vertex " + to_string(start)+ " to vertex "+ to_string(end)+ ": ";
    for (size_t i = 0; i < path.size(); i++)
    {
        s=s+to_string(path[i]);
        if (i != path.size() - 1)
        {
            s=s+"->";
        }
    }
    
    return s;
}

    //Dfs algorithm for checking if the graph contains cycle
    bool Algorithms::checkIsContainsCycle(size_t v, vector<bool> & visited, vector<size_t> & parent, stack<int> & cycle, vector<vector<int>> & graph)
    {
        visited[v] = true;

        for (size_t u = 0; u < graph[v].size(); ++u)
        {

            if (graph[v][u])
            {
                if (!visited[u])
                {
                    parent[u] = v;
                    if (checkIsContainsCycle(u, visited, parent, cycle, graph))
                        return true;
                }
                else if (parent[v] != u || cycle.size() == 0)
                {
                    cycle.push(u);
                    for (size_t p = v; p != u; p = parent[p])
                    {
                        cycle.push(p);
                    }
                    cycle.push(u);
                    return true;
                }
            }
        }
        cout << 0 << endl;
        return false;
    }

    string Algorithms::isContainsCycle(Graph gr)
    {
       
        vector<vector<int>> graph = gr.getGraph();
        size_t numOfVertices = (size_t)gr.getNumOfVertices();

        vector<bool> visited(numOfVertices, false);
        vector<size_t> parent(numOfVertices, (size_t)-1);
        stack<int> cycle;
        string cycleprint = "The cycle is: ";
        for (size_t v = 0; v < numOfVertices; ++v)
        {
            if (!visited[v] && checkIsContainsCycle(v, visited, parent, cycle, graph))
            {
                while (!cycle.empty())
                {
                    cycleprint = cycleprint + to_string(cycle.top());
                    cycle.pop();
                    if (!cycle.empty())
                    {
                        cycleprint = cycleprint + "->";
                    }
                }
                return cycleprint;
            }
        }
        return "0";
    }

    /* Bfs algorithm to find if the graph is bipartite
       It checks for each vertex if his adjacent vertex has the same color as him,
       if it does, the graph is bipartite
    */
    string Algorithms::isBipartite(Graph gr)
    {
        vector<vector<int>> graph = gr.getGraph();
        size_t numOfVertices = (size_t)gr.getNumOfVertices();

        vector<int> color(numOfVertices, -1);

        color[0] = 0;

        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            size_t u = (size_t)q.front();
            q.pop();

            for (size_t v = 0; v < numOfVertices; ++v)
            {
                if (graph[u][v] && color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if (graph[u][v] && color[v] == color[u])
                {
                    return "0";
                }
            }
        }

        string partition = "The graph is bipartite:";
        string setA = "{ ";
        string setB = "{ ";

        for (size_t u = 0; u < numOfVertices; u++)
        {
            if (color[u] == 0)
                setA += to_string(u) + " ";
            else
                setB += to_string(u) + " ";
        }

        setA += "}";
        setB += "}";

        partition = partition + " A=" + setA + ", B=" + setB;

        return partition;
    }

    /* Bellman ford algorithm for checking if the graph has negative cycle.
       Doing relax n times to all the edges, if at the n's time the distance
       for one of the edges changed, there is a negative cycle in the graph.
    */

    string Algorithms::negativeCycle(Graph gr)
    {
        if( !gr.getIsWeighed()){
            return "Graph doesn't contains negative weight cycle"; 
        }
        vector<vector<int>> graph = gr.getGraph();
        size_t numOfVertices = (size_t)gr.getNumOfVertices();
        vector<int> distance(numOfVertices, INFINITE);
        vector<int> parent(numOfVertices, -1);
        distance[0] = 0;


        for (size_t i = 0; i < numOfVertices - 1; i++)
        {
            for (size_t u = 0; u < numOfVertices; u++)
            {
                for (size_t v = 0; v < numOfVertices; v++)
                {
                    if (graph[u][v] != 0 && distance[u] != INFINITE && distance[u] + graph[u][v] < distance[v])
                    {
                        distance[v] = distance[u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        for (size_t u = 0; u < numOfVertices; u++)
        {
            for (size_t v = 0; v < numOfVertices; v++)
            {
                if (graph[u][v] != 0 && distance[u] != INFINITE && distance[u] + graph[u][v] < distance[v])
                {

                    return "Graph contains negative weight cycle";
                }
            }
        }
        return "Graph doesn't contains negative weight cycle";
    }

