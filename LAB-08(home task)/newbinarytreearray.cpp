#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
class Binary_Tree_Array
{
protected:
    int height;
    int maxSize;
    T *data;
    bool *exists;

public:

    Binary_Tree_Array(int h = 0)
    {
        height = h;
        maxSize = pow(2, height) - 1;
        data = new T[maxSize];
        exists = new bool[maxSize];

        for (int i = 0; i < maxSize; i++)
            exists[i] = false;
    }

    ~Binary_Tree_Array()
    {
        delete[] data;
        delete[] exists;
    }

    // ----------------------------
    // Basic Info
    // ----------------------------
    int MaxSize() { return maxSize; }
    int Height() { return height; }

    bool IsEmpty() { return !exists[0]; }

    // ----------------------------
    // Root and Child Setters
    // ----------------------------
    void SetRoot(T val)
    {
        data[0] = val;
        exists[0] = true;
    }

    void SetLeftChild(T parent, T val)
    {
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i] && data[i] == parent)
            {
                int left = 2 * i + 1;
                if (left < maxSize)
                {
                    data[left] = val;
                    exists[left] = true;
                }
                return;
            }
        }
    }

    void SetRightChild(T parent, T val)
    {
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i] && data[i] == parent)
            {
                int right = 2 * i + 2;
                if (right < maxSize)
                {
                    data[right] = val;
                    exists[right] = true;
                }
                return;
            }
        }
    }

    // ----------------------------
    // Traversals
    // ----------------------------
    void PreOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        cout << data[i] << " ";
        PreOrder(2 * i + 1);
        PreOrder(2 * i + 2);
    }

    void InOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        InOrder(2 * i + 1);
        cout << data[i] << " ";
        InOrder(2 * i + 2);
    }

    void PostOrder(int i = 0)
    {
        if (i >= maxSize || !exists[i])
            return;
        PostOrder(2 * i + 1);
        PostOrder(2 * i + 2);
        cout << data[i] << " ";
    }

    void LevelOrder()
    {
        if (!exists[0])
            return;

        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int i = q.front();
            q.pop();
            cout << data[i] << " ";

            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < maxSize && exists[left])
                q.push(left);
            if (right < maxSize && exists[right])
                q.push(right);
        }
    }

    // ----------------------------
    // Counting Functions
    // ----------------------------
    int CountNodes()
    {
        int count = 0;
        for (int i = 0; i < maxSize; i++)
            if (exists[i])
                count++;
        return count;
    }

    int CountLeaves()
    {
        int count = 0;
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i])
            {
                int left = 2 * i + 1, right = 2 * i + 2;
                if ((left >= maxSize || !exists[left]) && (right >= maxSize || !exists[right]))
                    count++;
            }
        }
        return count;
    }

    int CountInternalNodes()
    {
        int total = CountNodes();
        return total - CountLeaves();
    }

    // ----------------------------
    // Min / Max (for comparable types)
    // ----------------------------
    T FindMin()
    {
        if (IsEmpty())
            throw runtime_error("Tree is empty!");
        T mn;
        bool first = true;
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i])
            {
                if (first)
                {
                    mn = data[i];
                    first = false;
                }
                else
                    mn = min(mn, data[i]);
            }
        }
        return mn;
    }

    T FindMax()
    {
        if (IsEmpty())
            throw runtime_error("Tree is empty!");
        T mx;
        bool first = true;
        for (int i = 0; i < maxSize; i++)
        {
            if (exists[i])
            {
                if (first)
                {
                    mx = data[i];
                    first = false;
                }
                else
                    mx = max(mx, data[i]);
            }
        }
        return mx;
    }

    // ----------------------------
    // Mirror the Tree
    // ----------------------------
    void Mirror()
    {
        for (int i = 0; i < maxSize; i++)
        {
            if (!exists[i])
                continue;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < maxSize && right < maxSize)
            {
                swap(data[left], data[right]);
                swap(exists[left], exists[right]);
            }
        }
    }

    // ----------------------------
    // Check if Tree is Complete
    // ----------------------------
    bool IsComplete()
    {
        bool foundEmpty = false;
        for (int i = 0; i < maxSize; i++)
        {
            if (!exists[i])
                foundEmpty = true;
            else if (foundEmpty)
                return false; // found a non-null after null
        }
        return true;
    }

    // ----------------------------
    // Check if Tree is Perfect
    // ----------------------------
    bool IsPerfect()
    {
        int expectedNodes = pow(2, height) - 1;
        return CountNodes() == expectedNodes && IsComplete();
    }

    // ----------------------------
    // Print All Root-to-Leaf Paths
    // ----------------------------
    void PrintPathsUtil(int i, vector<T> path)
    {
        if (i >= maxSize || !exists[i])
            return;

        path.push_back(data[i]);

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if ((left >= maxSize || !exists[left]) && (right >= maxSize || !exists[right]))
        {
            for (auto val : path)
                cout << val << " ";
            cout << endl;
        }
        else
        {
            PrintPathsUtil(left, path);
            PrintPathsUtil(right, path);
        }
    }

    void PrintAllPaths()
    {
        vector<T> path;
        PrintPathsUtil(0, path);
    }

    // ----------------------------
    // Display Tree Information
    // ----------------------------
    void DisplayInfo()
    {
        cout << "\nNodes: " << CountNodes();
        cout << "\nLeaves: " << CountLeaves();
        cout << "\nInternal Nodes: " << CountInternalNodes();
        cout << "\nHeight: " << height;
        cout << "\nMin Value: " << FindMin();
        cout << "\nMax Value: " << FindMax();
        cout << "\nIs Complete: " << (IsComplete() ? "Yes" : "No");
        cout << "\nIs Perfect: " << (IsPerfect() ? "Yes" : "No") << endl;
    }
};

// ===========================================
// MAIN FUNCTION — TESTING
// ===========================================
int main()
{
    Binary_Tree_Array<int> tree(3); // height = 3 -> maxSize = 7
    tree.SetRoot(1);
    tree.SetLeftChild(1, 2);
    tree.SetRightChild(1, 3);
    tree.SetLeftChild(2, 4);
    tree.SetRightChild(2, 5);
    tree.SetLeftChild(3, 6);
    tree.SetRightChild(3, 7);

    cout << "PreOrder: ";
    tree.PreOrder();
    cout << "\nInOrder: ";
    tree.InOrder();
    cout << "\nPostOrder: ";
    tree.PostOrder();
    cout << "\nLevelOrder: ";
    tree.LevelOrder();

    tree.DisplayInfo();

    cout << "\nAll Root-to-Leaf Paths:\n";
    tree.PrintAllPaths();

    cout << "\nMirroring tree...\n";
    tree.Mirror();
    cout << "LevelOrder after Mirror: ";
    tree.LevelOrder();
    cout << endl;

    return 0;
}
