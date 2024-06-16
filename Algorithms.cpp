// Id-9115
// Email address- orgoren3146@gmail.com

#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#define INFINITE 99999

using namespace std;
using namespace ariel;

// Dfs algorithm for traversing the graph starting from vertex v
void Algorithms::DFS(size_t v, const vector<vector<int>> &graph, vector<bool> &visited)
{
    // Mark the current vertex as visited
    visited[v] = true;

    // Traverse all adjacent vertices of v
    for (size_t u = 0; u < graph.size(); ++u)
    {
        // If u is adjacent to v and not visited yet, recursively call DFS for vertex u
        if (graph[v][u] && !visited[u])
        {
            DFS(u, graph, visited);
        }
    }
}

/**
 * Split the is connected check:
 * If the graph is directed, we will use the Bfs algorithm
 * If the graph is undirected, we will use the Dfs algorithm
 */
bool Algorithms::isConnected(const Graph &gr)
{

    bool ans;
    if (gr.getIsDirected())
    {
        return isConnectedDirected(gr);
    }

    return isConnectedUndirected(gr);
}

// Checking if a directed graph is connected by using dfs algorithm
bool Algorithms::isConnectedDirected(const Graph &gr)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();

    // Making dfs for each vertex
    for (size_t i = 0; i < numOfVertices; ++i)
    {
        vector<bool> visited(numOfVertices, false);
        DFS(i, graph, visited);

        // Check if all vertices are visited, if not, graph is not connecte
        for (bool vVisited : visited)
        {
            if (!vVisited)
            {
                return false;
            }
        }
    }

    return true;
}

/*
Bfs algorithm for checking if an undirected graph is connected.
The output is a bool array that indicates which vertex we checked.
If one of the cells in the array is false, the graph is not connected.
 */
bool Algorithms::isConnectedUndirected(const Graph &gr)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();
    // Initialize boolean array to check if there is a path between the 0 vertex to each one of the other vretices
    vector<bool> visited(numOfVertices, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty())
    {
        /*Each iteration we are checking for  a different vertex if his neighbors already visited,
          if they didn't, setting isPath[neighbor] to true
        */
        size_t vertex = (size_t)q.front();
        q.pop();

        for (size_t i = 0; i < numOfVertices; i++)
        {
            // Insert all the neighbors that has an edge with the vertex to the queue
            if (graph[vertex][i] && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    /*Checking if all the vertices visited.
     If one of the vertices hasn't visited, the graph is not connected.
     */
    for (size_t i = 0; i < numOfVertices; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }

    return true;
}

/**
 * Split the shortest path check:
 * If the graph is weighed we will use the Bellman Ford algorithm
 * If the graph is Unweighed we will use bfs algorithm.
 */
string Algorithms::shortestPath(const Graph &gr, size_t start, size_t end)
{
    string s;
    if (gr.getIsWeighed())
    {
        return shortestPathWeighed(gr, start, end);
    }

    return shortestPathUnweighed(gr, start, end);
}

// Bellman-Ford algorithm for finding the shortest path in a weighted graph
string Algorithms::shortestPathWeighed(const Graph &gr, size_t start, size_t end)
{

    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();
    vector<int> distance(numOfVertices, INFINITE);
    vector<size_t> parent(numOfVertices, (size_t)-1);
    // Setting the distance to the start vertex as 0
    distance[start] = 0;

    // Making relax (numOfVertices - 1) times
    for (size_t i = 0; i < numOfVertices - 1; i++)
    {
        for (size_t u = 0; u < numOfVertices; u++)
        {
            for (size_t v = 0; v < numOfVertices; v++)
            {
                // If there is an edge from u to v and the distance to u is not INFINITE
                // and the distance through u to v is less than the current distance to v
                if (graph[u][v] && distance[u] != INFINITE && distance[u] + graph[u][v] < distance[v])
                {
                    // Update the distance to v
                    distance[v] = distance[u] + graph[u][v];
                    // Set u as the parent of v
                    parent[v] = u;
                }
            }
        }
    }

    // Build the path string
    string path = "Shortest path from vertex " + to_string(start) + " to vertex " + to_string(end) + ": ";
    size_t currentVertex = end;
    stack<size_t> sPath;

    // Trace the path from end to start using the parent vector
    while (currentVertex != -1)
    {
        sPath.push(currentVertex);
        currentVertex = parent[currentVertex];
    }

    while (!sPath.empty())
    {
        path = path + to_string(sPath.top());
        sPath.pop();
        if (!sPath.empty())
        {
            path = path + "->";
        }
    }

    // If the distance to the end vertex is still INFINITE, return -1 (no path exists)
    if (distance[end] == INFINITE)
    {
        return "-1";
    }

    return path;
}

// Bfs algorithm for finding the shortest path in unweighed graph
string Algorithms::shortestPathUnweighed(const Graph &gr, size_t start, size_t end)
{
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)graph.size();
    vector<size_t> distance(numOfVertices, (size_t)-1);
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

    // Build the path string
    string path = "Shortest path from vertex " + to_string(start) + " to vertex " + to_string(end) + ": ";
    size_t currentVertex = end;
    stack<size_t> sPath;

    // Trace the path from end to start using the parent vector
    while (currentVertex != -1)
    {
        sPath.push(currentVertex);
        currentVertex = parent[currentVertex];
    }

    while (!sPath.empty())
    {
        path = path + to_string(sPath.top());
        sPath.pop();
        if (!sPath.empty())
        {
            path = path + "->";
        }
    }

    return path;
}

// DFS algorithm for checking if the graph contains a cycle
bool Algorithms::checkIsContainsCycle(size_t v, vector<bool> &visited, vector<size_t> &parent, stack<int> &cycle, vector<vector<int>> &graph)
{
    visited[v] = true;

    // Iterate through all the adjacent vertices
    for (size_t u = 0; u < graph[v].size(); ++u)
    {
        if (graph[v][u])
        {
            // If u is not visited, continue DFS
            if (!visited[u])
            {
                parent[u] = v;
                if (checkIsContainsCycle(u, visited, parent, cycle, graph))
                    return true;
            }
            // If u is visited and not the parent of v, a cycle is found
            else if (parent[v] != u || cycle.size() == 0)
            {
                // Push the vertices of the cycle into the stack
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

string Algorithms::isContainsCycle(const Graph &gr)
{
    // Get the graph and number of vertices
    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();

    // Initialize visited and parent vectors
    vector<bool> visited(numOfVertices, false);
    vector<size_t> parent(numOfVertices, (size_t)-1);
    stack<int> cycle;
    string cycleprint = "The cycle is: ";

    // Check each vertex for a cycle
    for (size_t v = 0; v < numOfVertices; ++v)
    {
        // If the vertex is not visited, call DFS to check for a cycle
        if (!visited[v] && checkIsContainsCycle(v, visited, parent, cycle, graph))
        {
            // Construct the cycle path string
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
    return "0"; // No cycle found
}

/* Bfs algorithm to find if the graph is bipartite
   It checks for each vertex if his adjacent vertex has the opposite color as him,
   if it does, the graph is bipartite
*/
string Algorithms::isBipartite(const Graph &gr)
{

    vector<vector<int>> graph = gr.getGraph();
    size_t numOfVertices = (size_t)gr.getNumOfVertices();

    // Initialize the color vector with -1 (unvisited)
    vector<int> color(numOfVertices, -1);

    // Start with the first vertex, color it with color 0
    color[0] = 0;

    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        size_t u = (size_t)q.front();
        q.pop();

        // Check all adjacent vertices
        for (size_t v = 0; v < numOfVertices; ++v)
        {
            // If there is an edge and v is not colored
            if (graph[u][v] && color[v] == -1)
            {
                // Color v with the opposite color of u
                color[v] = 1 - color[u];
                q.push(v);
            }
            // If there is an edge and v has the same color as u, the graph is not bipartite. return "0"
            else if (graph[u][v] && color[v] == color[u])
            {
                return "0"; 
            }
        }
    }

    // If the graph is bipartite, create the partition sets
    string partition = "The graph is bipartite:";
    string setA = "{ ";
    string setB = "{ ";

    // Add vertices to the respective sets based on their colors
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
   Doing relax n times to all the edges, if at the n'th time the distance
   for one of the edges changed, there is a negative cycle in the graph.
*/
string Algorithms::negativeCycle(const Graph& gr)
    {
        if( !gr.getIsWeighed()){
            return "Graph doesn't contains negative weight cycle"; 
        }
        vector<vector<int>> graph = gr.getGraph();
        size_t numOfVertices = (size_t)gr.getNumOfVertices();
        vector<int> distance(numOfVertices, INFINITE);
        vector<int> parent(numOfVertices, -1);
        distance[0] = 0;

        // Relax edges n - 1 times
        for (size_t i = 0; i < numOfVertices - 1; i++)
        {
            for (size_t u = 0; u < numOfVertices; u++)
            {
                for (size_t v = 0; v < numOfVertices; v++)
                {
                    // If there is an edge from u to v, and the distance to u is not infinite,
                    // and the path through u to v is shorter than the current distance to v
                    if (graph[u][v] != 0 && distance[u] != INFINITE && distance[u] + graph[u][v] < distance[v])
                    {
                        // Update the distance to v
                        distance[v] = distance[u] + graph[u][v];
                         // Update the parent of v
                        parent[v] = u;
                    }
                }
            }
        }

        // Making relax one more time, if the distance to one of the edges changed, the graph is not bipartite
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
