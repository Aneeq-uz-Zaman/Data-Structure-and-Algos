#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Graph
{
private:
    vector<int> *adjList;
    int maxVertices;
    int n;
    bool *visited;

    void DFS(int v)
    {
        cout << v << " ";
        visited[v] = true;

        for (int x : adjList[v])
        {
            if (!visited[x])
                DFS(x);
        }
    }

public:
    Graph(int maxV, int currV)
    {
        maxVertices = maxV;
        n = currV;
        adjList = new vector<int>[maxVertices + 1];
        visited = new bool[maxVertices + 1];
    }

    Graph(const Graph &g)
    {
        maxVertices = g.maxVertices;
        n = g.n;
        adjList = new vector<int>[maxVertices + 1];
        for (int i = 1; i <= n; i++)
            adjList[i] = g.adjList[i];
        visited = new bool[maxVertices + 1];
    }

    ~Graph()
    {
        delete[] adjList;
        delete[] visited;
    }

    bool addVertex(int &v)
    {
        if (n >= maxVertices)
            return false;
        n++;
        v = n;
        return true;
    }

    bool addEdge(int u, int v)
    {
        if (u < 1 || v < 1 || u > n || v > n)
            return false;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        return true;
    }

    bool removeEdge(int u, int v)
    {
        if (u < 1 || v < 1 || u > n || v > n)
            return false;

        for (auto it = adjList[u].begin(); it != adjList[u].end(); it++)
        {
            if (*it == v)
            {
                adjList[u].erase(it);
                break;
            }
        }

        for (auto it = adjList[v].begin(); it != adjList[v].end(); it++)
        {
            if (*it == u)
            {
                adjList[v].erase(it);
                break;
            }
        }

        return true;
    }

    bool isEmpty()
    {
        for (int i = 1; i <= n; i++)
            if (!adjList[i].empty())
                return false;
        return true;
    }

    bool isComplete()
    {
        for (int i = 1; i <= n; i++)
            if ((int)adjList[i].size() != n - 1)
                return false;
        return true;
    }

    void clear()
    {
        for (int i = 1; i <= n; i++)
            adjList[i].clear();
    }

    void display()
    {
        for (int i = 1; i <= n; i++)
        {
            cout << i << ": ";
            for (int x : adjList[i])
                cout << x << " ";
            cout << endl;
        }
    }

    int Degree(int v)
    {
        if (v < 1 || v > n)
            return -1;
        return adjList[v].size();
    }

    void DFS()
    {
        for (int i = 1; i <= n; i++)
            visited[i] = false;

        int s;
        cin >> s;

        if (s >= 1 && s <= n)
            DFS(s);

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                DFS(i);

        cout << endl;
    }

    void BFS()
    {
        for (int i = 1; i <= n; i++)
            visited[i] = false;

        int s;
        cin >> s;

        queue<int> q;

        if (s >= 1 && s <= n)
        {
            q.push(s);
            visited[s] = true;
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int x : adjList[u])
            {
                if (!visited[x])
                {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = true;

                while (!q.empty())
                {
                    int u = q.front();
                    q.pop();
                    cout << u << " ";

                    for (int x : adjList[u])
                    {
                        if (!visited[x])
                        {
                            visited[x] = true;
                            q.push(x);
                        }
                    }
                }
            }
        }

        cout << endl;
    }
};
int main()
{
    Graph g(10, 0);

    int v;
    g.addVertex(v);
    g.addVertex(v);
    g.addVertex(v);
    g.addVertex(v);
    g.addVertex(v);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    g.display();

    g.DFS();
    g.BFS();

    return 0;
}
