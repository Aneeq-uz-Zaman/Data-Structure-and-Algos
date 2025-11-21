#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// ==============================================
// Node Class Template
// ==============================================
template <typename T>
class Node
{
public:
    T info;
    Node<T> *left;
    Node<T> *right;

    Node(T val = 0)
    {
        info = val;
        left = nullptr;
        right = nullptr;
    }
};

// ==============================================
// Binary Tree Template Class
// ==============================================
template <typename T>
class Binary_Tree
{
private:
    Node<T> *root;

    // --------------------------
    // Helper: Search recursively
    // --------------------------
    Node<T> *Search(Node<T> *curr, T val)
    {
        if (curr == nullptr)
            return nullptr;
        if (curr->info == val)
            return curr;

        Node<T> *found = Search(curr->left, val);
        if (found)
            return found;
        return Search(curr->right, val);
    }

    // --------------------------
    // Helper: Remove all nodes
    // --------------------------
    void RemoveSubtree(Node<T> *curr)
    {
        if (!curr)
            return;
        RemoveSubtree(curr->left);
        RemoveSubtree(curr->right);
        delete curr;
    }

    // --------------------------
    // Traversal Helpers
    // --------------------------
    void PreOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        cout << curr->info << " ";
        PreOrder(curr->left);
        PreOrder(curr->right);
    }

    void InOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        InOrder(curr->left);
        cout << curr->info << " ";
        InOrder(curr->right);
    }

    void PostOrder(Node<T> *curr)
    {
        if (!curr)
            return;
        PostOrder(curr->left);
        PostOrder(curr->right);
        cout << curr->info << " ";
    }

    // --------------------------
    // Count Functions
    // --------------------------
    int CountNodes(Node<T> *curr)
    {
        if (!curr)
            return 0;
        return 1 + CountNodes(curr->left) + CountNodes(curr->right);
    }

    int CountLeaves(Node<T> *curr)
    {
        if (!curr)
            return 0;
        if (!curr->left && !curr->right)
            return 1;
        return CountLeaves(curr->left) + CountLeaves(curr->right);
    }

    int CountInternalNodes(Node<T> *curr)
    {
        if (!curr || (!curr->left && !curr->right))
            return 0;
        return 1 + CountInternalNodes(curr->left) + CountInternalNodes(curr->right);
    }

    int Height(Node<T> *curr)
    {
        if (!curr)
            return 0;
        return 1 + max(Height(curr->left), Height(curr->right));
    }

    // --------------------------
    // Find Min / Max (for comparable T)
    // --------------------------
    T FindMin(Node<T> *curr)
    {
        if (!curr)
            throw runtime_error("Empty tree");
        T mn = curr->info;
        if (curr->left)
            mn = min(mn, FindMin(curr->left));
        if (curr->right)
            mn = min(mn, FindMin(curr->right));
        return mn;
    }

    T FindMax(Node<T> *curr)
    {
        if (!curr)
            throw runtime_error("Empty tree");
        T mx = curr->info;
        if (curr->left)
            mx = max(mx, FindMax(curr->left));
        if (curr->right)
            mx = max(mx, FindMax(curr->right));
        return mx;
    }

    // --------------------------
    // Equality Check
    // --------------------------
    bool IsEqual(Node<T> *a, Node<T> *b)
    {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr || b == nullptr)
            return false;
        return (a->info == b->info) &&
               IsEqual(a->left, b->left) &&
               IsEqual(a->right, b->right);
    }

    // --------------------------
    // Mirror Helper
    // --------------------------
    void Mirror(Node<T> *curr)
    {
        if (!curr)
            return;
        swap(curr->left, curr->right);
        Mirror(curr->left);
        Mirror(curr->right);
    }

    // --------------------------
    // Path Printing
    // --------------------------
    void PrintAllPaths(Node<T> *curr, vector<T> &path)
    {
        if (!curr)
            return;
        path.push_back(curr->info);
        if (!curr->left && !curr->right)
        {
            for (T val : path)
                cout << val << " ";
            cout << endl;
        }
        else
        {
            PrintAllPaths(curr->left, path);
            PrintAllPaths(curr->right, path);
        }
        path.pop_back();
    }

    // --------------------------
    // Complete Binary Tree check
    // --------------------------
    bool IsComplete(Node<T> *root)
    {
        if (!root)
            return true;
        queue<Node<T> *> q;
        q.push(root);
        bool nullSeen = false;

        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();

            if (curr == nullptr)
                nullSeen = true;
            else
            {
                if (nullSeen)
                    return false; // Found non-null after a null
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return true;
    }

public:
    // --------------------------
    // Constructor / Destructor
    // --------------------------
    Binary_Tree(T val = 0)
    {
        root = new Node<T>(val);
    }

    ~Binary_Tree()
    {
        RemoveSubtree(root);
    }

    // --------------------------
    // Setters
    // --------------------------
    void SetRoot(T v)
    {
        if (!root)
            root = new Node<T>(v);
        else
            root->info = v;
    }

    void SetLeftChild(T parentVal, T childVal)
    {
        Node<T> *parent = Search(root, parentVal);
        if (!parent)
            return;
        if (!parent->left)
            parent->left = new Node<T>(childVal);
        else
            parent->left->info = childVal;
    }

    void SetRightChild(T parentVal, T childVal)
    {
        Node<T> *parent = Search(root, parentVal);
        if (!parent)
            return;
        if (!parent->right)
            parent->right = new Node<T>(childVal);
        else
            parent->right->info = childVal;
    }

    // --------------------------
    // Traversals
    // --------------------------
    void PreOrder() { PreOrder(root); cout << endl; }
    void InOrder() { InOrder(root); cout << endl; }
    void PostOrder() { PostOrder(root); cout << endl; }

    void LevelOrder()
    {
        if (!root)
            return;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            cout << curr->info << " ";
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        cout << endl;
    }

    // --------------------------
    // Public Utilities
    // --------------------------
    bool IsEmpty() { return root == nullptr; }

    int GetHeight() { return Height(root); }

    int GetNodeCount() { return CountNodes(root); }

    int GetLeafCount() { return CountLeaves(root); }

    int GetInternalCount() { return CountInternalNodes(root); }

    T GetMin() { return FindMin(root); }

    T GetMax() { return FindMax(root); }

    void MakeMirror() { Mirror(root); }

    bool IsComplete() { return IsComplete(root); }

    bool IsEqual(Binary_Tree<T> &other) { return IsEqual(root, other.root); }

    void PrintAllPaths()
    {
        vector<T> path;
        PrintAllPaths(root, path);
    }
};

// ==============================================
// MAIN FUNCTION - TESTING
// ==============================================
int main()
{
    Binary_Tree<int> tree(1);

    tree.SetLeftChild(1, 2);
    tree.SetRightChild(1, 3);
    tree.SetLeftChild(2, 4);
    tree.SetRightChild(2, 5);
    tree.SetLeftChild(3, 6);
    tree.SetRightChild(3, 7);

    cout << "PreOrder: ";
    tree.PreOrder();

    cout << "InOrder: ";
    tree.InOrder();

    cout << "PostOrder: ";
    tree.PostOrder();

    cout << "LevelOrder: ";
    tree.LevelOrder();

    cout << "\nNode Count: " << tree.GetNodeCount();
    cout << "\nLeaf Count: " << tree.GetLeafCount();
    cout << "\nInternal Count: " << tree.GetInternalCount();
    cout << "\nHeight: " << tree.GetHeight();
    cout << "\nMin Value: " << tree.GetMin();
    cout << "\nMax Value: " << tree.GetMax();
    return 0;
}