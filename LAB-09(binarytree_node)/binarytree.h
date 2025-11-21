#ifndef NODE_BINARY_TREE_H
#define NODE_BINARY_TREE_H

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *left;
    Node<T> *right;
    Node(const T &val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class NodeBinaryTree
{
public:
    Node<T> *root;

    NodeBinaryTree() : root(nullptr) {}
    ~NodeBinaryTree() { clear(); }
    NodeBinaryTree<T> &operator=(const NodeBinaryTree<T> &other)
    {
        if (&other == this)
            return *this;
        clear();
        if (!other.root)
            return *this;

        root = new Node<T>(other.root->data);
        queue<Node<T> *> qOld, qNew;
        qOld.push(other.root);
        qNew.push(root);

        while (!qOld.empty())
        {
            Node<T> *oldN = qOld.front();
            qOld.pop();
            Node<T> *newN = qNew.front();
            qNew.pop();

            if (oldN->left)
            {
                newN->left = new Node<T>(oldN->left->data);
                qOld.push(oldN->left);
                qNew.push(newN->left);
            }
            if (oldN->right)
            {
                newN->right = new Node<T>(oldN->right->data);
                qOld.push(oldN->right);
                qNew.push(newN->right);
            }
        }
        return *this;
    }
    //     D:\C++\DSA\LAB-09(binarytree_node)>g++ test-node.cpp
    // test-node.cpp: In function 'int main()':
    // test-node.cpp:21:50: error: invalid initialization of non-const reference of type 'NodeBinaryTree<int>&' from an rvalue of type 'NodeBinaryTree<int>'
    //      NodeBinaryTree<int> tree2=tree.getMirrorImage();
    //                                ~~~~~~~~~~~~~~~~~~~^~
    // In file included from test-node.cpp:1:0:
    // binarytree.h:64:5: note:   initializing argument 1 of 'NodeBinaryTree<T>::NodeBinaryTree(NodeBinaryTree<T>&) [with T = int]'
    //      NodeBinaryTree(NodeBinaryTree<T> &other)


    NodeBinaryTree(const NodeBinaryTree<T> &other)
    {
        root = nullptr;
        if (&other == this)
            return;
        if (!other.root)
            return;

        root = new Node<T>(other.root->data);
        queue<Node<T> *> qOld, qNew;
        qOld.push(other.root);
        qNew.push(root);

        while (!qOld.empty())
        {
            Node<T> *oldN = qOld.front();
            qOld.pop();
            Node<T> *newN = qNew.front();
            qNew.pop();

            if (oldN->left)
            {
                newN->left = new Node<T>(oldN->left->data);
                qOld.push(oldN->left);
                qNew.push(newN->left);
            }
            if (oldN->right)
            {
                newN->right = new Node<T>(oldN->right->data);
                qOld.push(oldN->right);
                qNew.push(newN->right);
            }
        }
    }
    int isInternalNode(T node) // Internal Node is one which has degree greater than zero
    {
        Node<T> *target = SEARCH(node);
        if (!target)
            throw runtime_error("Node not found");
        if (target->left || target->right)
            return 1;
        else
            return 0;
    }
    int isExternalNode(T node) // External Node is one which has degree equal to zero
    {
        Node<T> *target = SEARCH(node);
        if (!target)
            throw runtime_error("Node not found");
        if (!(target->left) && !(target->right))
            return 1;
        else
            return 0;
    }

    bool isEmpty() const { return root == nullptr; }

    void clear(Node<T> *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    void setRoot(const T &value)
    {
        clear(root);
        root = new Node<T>(value);
    }

    Node<T> *setLeftChild(Node<T> *parent, const T &value)
    {
        if (!parent)
            throw runtime_error("Parent is null");
        if (parent->left)
            throw runtime_error("Left child already exists");
        parent->left = new Node<T>(value);
        return parent->left;
    }

    Node<T> *setRightChild(Node<T> *parent, const T &value)
    {
        if (!parent)
            throw runtime_error("Parent is null");
        if (parent->right)
            throw runtime_error("Right child already exists");
        parent->right = new Node<T>(value);
        return parent->right;
    }
    Node<T> *findParent(const T &value)
    {
        if (!root || root->data == value)
            return nullptr;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if ((curr->left && curr->left->data == value) ||
                (curr->right && curr->right->data == value))
                return curr;
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        return nullptr;
    }

    void insertLevelOrder(const T &value)
    {
        Node<T> *newNode = new Node<T>(value);
        if (!root)
        {
            root = newNode;
            return;
        }
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if (!curr->left)
            {
                curr->left = newNode;
                return;
            }
            if (!curr->right)
            {
                curr->right = newNode;
                return;
            }
            q.push(curr->left);
            q.push(curr->right);
        }
    }

    Node<T> *SEARCH(const T &value) const
    {
        if (!root)
            return nullptr;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if (curr->data == value)
                return curr;
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        return nullptr;
    }

    bool REMOVE(const T &value)
    {
        if (!root)
            return false;
        Node<T> *target = SEARCH(value);
        if (!target)
            return false;
        Node<T> *parent = findParent(value);

        // if target is root, delete entire tree
        if (!parent)
        {
            clear(root);
            root = nullptr;
            return true;
        }

        // delete subtree and unlink from parent
        if (parent->left && parent->left->data == value)
        {
            clear(parent->left);
            parent->left = nullptr;
            return true;
        }
        if (parent->right && parent->right->data == value)
        {
            clear(parent->right);
            parent->right = nullptr;
            return true;
        }

        return false;
    }
    T findNodeSiblings(T node)
    {
        Node<T> *parent = findParent(node);
        if (!parent)
            return T();
        if (parent->left && parent->left->data == node)
        {

            if (parent->right)
                return parent->right->data;
            else
                return T();
        }
        if (parent->right && parent->right->data == node)
        {
            if (parent->left)
                return parent->left->data;
            else
                return T();
        }
        return T();
    }
    void displayDescendents(T node)
    {
        Node<T> *target = SEARCH(node);
        queue<Node<T> *> q;
        cout << endl
             << "Descendents:";
        q.push(target);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if (!(curr->data == node))
                cout << curr->data << " ";
            if (curr->left)
            {
                q.push(curr->left);
            }
            if (curr->right)
            {
                q.push(curr->right);
            }
        }
    }

    vector<T> PREORDER() const
    {
        vector<T> out;
        preorder(root, out);
        return out;
    }

    vector<T> INORDER() const
    {
        vector<T> out;
        inorder(root, out);
        return out;
    }

    vector<T> POSTORDER() const
    {
        vector<T> out;
        postorder(root, out);
        return out;
    }

    vector<T> LEVELORDER() const
    {
        vector<T> out;
        if (!root)
            return out;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            out.push_back(curr->data);
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        return out;
    }

    int height() const { return heightHelper(root); }
    int size() const { return countNodes(root); }
    int countLeaves() const { return countLeavesHelper(root); }
    int countNonLeaves() const { return size() - countLeaves(); }

    Node<T> *findParent(const T &value) const
    {
        if (!root || root->data == value)
            return nullptr;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if ((curr->left && curr->left->data == value) ||
                (curr->right && curr->right->data == value))
                return curr;
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        return nullptr;
    }

    void deleteParentOf(const T &value)
    {
        if (!root)
            return;
        if (root->data == value)
            return;
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if ((curr->left && curr->left->data == value) ||
                (curr->right && curr->right->data == value))
            {
                REMOVE(curr->data);
                return;
            }
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }

    vector<T> pathToNode(const T &value) const
    {
        vector<T> path;
        if (!root)
            return path;
        bool found = pathToNodeHelper(root, value, path);
        if (!found)
            path.clear();
        return path;
    }

    void print(const vector<T> &v, const string &label) const
    {
        cout << label << ": ";
        for (auto &x : v)
            cout << x << " ";
        cout << endl;
    }

    void printAllOrders() const
    {
        print(PREORDER(), "Preorder");
        print(INORDER(), "Inorder");
        print(POSTORDER(), "Postorder");
        print(LEVELORDER(), "Levelorder");
    }
    
    Node<T> *mirrorClone(Node<T> *curr) const
    {
        if (!curr)
            return nullptr;
        Node<T> *node = new Node<T>(curr->data);
        // swap left/right while cloning to create mirror
        node->left = mirrorClone(curr->right);
        node->right = mirrorClone(curr->left);
        return node;
    }
    NodeBinaryTree<T> getMirrorImage() const
    {
        NodeBinaryTree<T> temp;
        temp.root = mirrorClone(root);
        return temp;
    }
    void parenthesize()
    {
        cout<<endl;
        parenthesizeHelper(root);
        cout << endl;
    }
private:
    void preorder(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        out.push_back(node->data);
        preorder(node->left, out);
        preorder(node->right, out);
    }

    void inorder(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        inorder(node->left, out);
        out.push_back(node->data);
        inorder(node->right, out);
    }

    void postorder(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        postorder(node->left, out);
        postorder(node->right, out);
        out.push_back(node->data);
    }

    int heightHelper(Node<T> *node) const
    {
        if (!node)
            return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    int countNodes(Node<T> *node) const
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeavesHelper(Node<T> *node) const
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return 1;
        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }
    // paratenhize view of whole tree 
    void parenthesizeHelper(Node<T> *node)
    {
        if (!node)
            return;
        cout << node->data;
        if (node->left || node->right)
        {
            cout << "(";
            if (node->left)
                parenthesizeHelper(node->left);
            else
                cout << "null";
            cout << ",";
            if (node->right)
                parenthesizeHelper(node->right);
            else
                cout << "null";
            cout << ")";
        }
    }
    
    bool pathToNodeHelper(Node<T> *node, const T &val, vector<T> &path) const
    
    {
        if (!node)
            return false;
        path.push_back(node->data);
        if (node->data == val)
            return true;
        if (pathToNodeHelper(node->left, val, path) ||
            pathToNodeHelper(node->right, val, path))
            return true;
        path.pop_back();
        return false;
    }
};

#endif
