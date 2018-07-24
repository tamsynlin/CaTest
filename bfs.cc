// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices 
// reachable from s.
// g++ bfs.cc -std=c++11 -o bfs
#include<iostream>
#include <list>
 
using namespace std;
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
private:
    int V;    // No. of vertices
    int Loop;
 
    // Pointer to an array containing adjacency lists
    list<int> *adj;   

    // A recursive function used by DFS
    void DFSUtil(int v, bool visited[]);

public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w); 
 
    // prints BFS traversal from a given source s
    void BFS(int s);

    // DFS traversal of the vertices reachable from v
    void DFS(int v);

    bool isCyclic()
    {
    	return this->Loop > 0 ? true:false;
    };
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    Loop = 0;
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];

    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited, 
        // then mark it visited and enqueue it
        for (auto i: adj[s])
        {
            if (!visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent to this vertex
    for (auto i: adj[v])
    {
        if (!visited[i])
        {
            DFSUtil(i, visited);
        }
        else
        {
        	Loop++;
        }
    }
}
 
// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
    {
    	visited[i] = false;
    }
 
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(v, visited);
}
 
// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2);
    cout << "\n";

    cout << "Following is Depth First Traversal"
        " (starting from vertex 2) \n";
    g.DFS(2);
    g.isCyclic()? cout << "Has loop?" <<  "Yes\n": cout << "Has loop?" << "No\n";
 
    return 0;
}
