#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// DFS utility to detect cycle
bool dfsCycleUtil(vector<vector<int>> &adj, int u, vector<bool> &visited, vector<bool> &recStack)
{
    visited[u] = true;
    recStack[u] = true;

    for (int v : adj[u])
    {
        if (!visited[v] && dfsCycleUtil(adj, v, visited, recStack))
            return true;
        else if (recStack[v])
            return true;
    }

    recStack[u] = false;
    return false;
}

// DFS-based cycle detection
bool hasCycleDFS(int V, vector<vector<int>> &adj)
{
    vector<bool> visited(V, false), recStack(V, false);

    for (int i = 0; i < V; ++i)
    {
        if (!visited[i] && dfsCycleUtil(adj, i, visited, recStack))
            return true;
    }

    return false;
}

// Kahn's Algorithm (BFS) for cycle detection
bool hasCycleKahn(int V, vector<vector<int>> &adj)
{
    vector<int> inDegree(V, 0);

    for (int u = 0; u < V; ++u)
        for (int v : adj[u])
            inDegree[v]++;

    queue<int> q;
    for (int i = 0; i < V; ++i)
        if (inDegree[i] == 0)
            q.push(i);

    int count = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        count++;

        for (int v : adj[u])
        {
            if (--inDegree[v] == 0)
                q.push(v);
        }
    }

    return count != V;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);
    cout << "Enter each edge (from to):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        cout << "Edge " << (i + 1) << " - from: ";
        cin >> u;
        cout << "Edge " << (i + 1) << " - to: ";
        cin >> v;

        if (u >= 0 && u < V && v >= 0 && v < V)
            adj[u].push_back(v);
        else
        {
            cout << "Invalid edge (" << u << " -> " << v << "). Please re-enter.\n";
            --i; // repeat this edge
        }
    }

    cout << "\nDFS-based Cycle Detection: ";
    cout << (hasCycleDFS(V, adj) ? "Cycle detected" : "No cycle") << endl;

    cout << "Kahn’s Algorithm (BFS-based) Cycle Detection: ";
    cout << (hasCycleKahn(V, adj) ? "Cycle detected" : "No cycle") << endl;

    return 0;
}
