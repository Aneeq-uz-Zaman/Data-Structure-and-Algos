#include <iostream>
#include <queue>
using namespace std;

class Graph
{
private:
    int **adjMatrix;
    int maxVertices;
    int n;
    bool *visited;

    void DFS(int v)
    {
        cout << v << " ";
        visited[v] = true;

        for (int i = 1; i <= n; i++)
        {
            if (adjMatrix[v][i] && !visited[i])
                DFS(i);
        }
    }

public:
    Graph(int maxV, int currV)
    {
        maxVertices = maxV;
        n = currV;

        adjMatrix = new int *[maxVertices + 1];
        for (int i = 0; i <= maxVertices; i++)
        {
            adjMatrix[i] = new int[maxVertices + 1];
            for (int j = 0; j <= maxVertices; j++)
                adjMatrix[i][j] = 0;
        }

        visited = new bool[maxVertices + 1];
    }

    Graph(const Graph &g)
    {
        maxVertices = g.maxVertices;
        n = g.n;

        adjMatrix = new int *[maxVertices + 1];
        for (int i = 0; i <= maxVertices; i++)
        {
            adjMatrix[i] = new int[maxVertices + 1];
            for (int j = 0; j <= maxVertices; j++)
                adjMatrix[i][j] = g.adjMatrix[i][j];
        }

        visited = new bool[maxVertices + 1];
    }

    ~Graph()
    {
        for (int i = 0; i <= maxVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
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
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
        return true;
    }

    bool removeEdge(int u, int v)
    {
        if (u < 1 || v < 1 || u > n || v > n)
            return false;
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
        return true;
    }

    bool isEmpty()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (adjMatrix[i][j])
                    return false;
        return true;
    }

    bool isComplete()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (i != j && adjMatrix[i][j] == 0)
                    return false;
        return true;
    }

    void clear()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                adjMatrix[i][j] = 0;
    }

    void display()
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    int Degree(int v)
    {
        if (v < 1 || v > n)
            return -1;
        int d = 0;
        for (int i = 1; i <= n; i++)
            if (adjMatrix[v][i])
                d++;
        return d;
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

            for (int i = 1; i <= n; i++)
            {
                if (adjMatrix[u][i] && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
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

                    for (int j = 1; j <= n; j++)
                    {
                        if (adjMatrix[u][j] && !visited[j])
                        {
                            visited[j] = true;
                            q.push(j);
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
