#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v); // Directed edge from u to v
    }

    // DFS-based cycle detection helper
    bool dfsCycleUtil(int node, vector<bool> &visited, vector<bool> &recStack)
    {
        visited[node] = true;
        recStack[node] = true;

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor] && dfsCycleUtil(neighbor, visited, recStack))
                return true;
            else if (recStack[neighbor])
                return true;
        }

        recStack[node] = false;
        return false;
    }

    // DFS-based cycle detection (main function)
    bool hasCycleDFS()
    {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; ++i)
        {
            if (!visited[i] && dfsCycleUtil(i, visited, recStack))
                return true;
        }
        return false;
    }

    // Kahn's Algorithm (BFS-based cycle detection)
    bool hasCycleKahn()
    {
        vector<int> inDegree(V, 0);
        for (int i = 0; i < V; ++i)
        {
            for (int neighbor : adj[i])
            {
                inDegree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; ++i)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }

        int count = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            count++;

            for (int neighbor : adj[u])
            {
                if (--inDegree[neighbor] == 0)
                    q.push(neighbor);
            }
        }

        return (count != V); // If count != V, there's a cycle
    }

    // Utility function to display the adjacency list (for debug)
    void printGraph()
    {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < V; ++i)
        {
            cout << i << ": ";
            for (int v : adj[i])
                cout << v << " ";
            cout << endl;
        }
    }
};

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    Graph g(V);
    cout << "Enter " << E << " directed edges (from to):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < V && v >= 0 && v < V)
        {
            g.addEdge(u, v);
        }
        else
        {
            cout << "❌ Invalid edge: " << u << " -> " << v
                 << " (vertex out of range 0 to " << (V - 1) << "). Please re-enter this edge.\n";
            --i; // Decrement i to repeat this iteration
        }
    }

    g.printGraph();

    cout << "\nCycle Detection using DFS: ";
    if (g.hasCycleDFS())
        cout << "Cycle detected." << endl;
    else
        cout << "No cycle detected." << endl;

    cout << "Cycle Detection using Kahn's Algorithm (BFS): ";
    if (g.hasCycleKahn())
        cout << "Cycle detected." << endl;
    else
        cout << "No cycle detected." << endl;

    return 0;
}
