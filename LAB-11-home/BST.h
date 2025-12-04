#ifndef BST_H
#define BST_H

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
class BST
{
public:
    Node<T> *root;

    BST() : root(nullptr) {}
    ~BST() { clear(); }

    // ---------- Copy constructor ----------
    BST(const BST<T> &other) : root(nullptr)
    {
        root = copyHelper(other.root);
    }

    BST<T> &operator=(const BST<T> &other)
    {
        if (this == &other)
            return *this;
        clear();
        root = copyHelper(other.root);
        return *this;
    }

    // ---------- Insert ----------
    void insert(const T &value)
    {
        root = insertHelper(root, value);
    }

    // ---------- Search ----------
    Node<T> *search(const T &value) const
    {
        return searchHelper(root, value);
    }

    // ---------- Remove ----------
    void remove(const T &value)
    {
        root = removeHelper(root, value);
    }

    // ---------- Rotations ----------
    Node<T> *rotateLeft(Node<T> *node)
    {
        if (!node || !node->right)
            return node;
        Node<T> *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    Node<T> *rotateRight(Node<T> *node)
    {
        if (!node || !node->left)
            return node;               // cannot rotate
        Node<T> *newRoot = node->left; // left child becomes new root
        node->left = newRoot->right;   // move newRoot's right subtree as node's left
        newRoot->right = node;         // old node becomes right child of newRoot
        return newRoot;                // return new root of this subtree
    }

    // ---------- Mirror ----------
    BST<T> getMirrorImage() const
    {
        BST<T> temp;
        temp.root = mirrorClone(root);
        return temp;
    }

    // ---------- Parenthesized view ----------
    void parenthesize() const
    {
        parenthesizeHelper(root);
        cout << endl;
    }

    // ---------- Traversals ----------
    vector<T> preorder() const
    {
        vector<T> out;
        preorderHelper(root, out);
        return out;
    }
    vector<T> inorder() const
    {
        vector<T> out;
        inorderHelper(root, out);
        return out;
    }
    vector<T> postorder() const
    {
        vector<T> out;
        postorderHelper(root, out);
        return out;
    }
    vector<T> levelorder() const
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

    void printAllOrders() const
    {
        print(preorder(), "Preorder");
        print(inorder(), "Inorder");
        print(postorder(), "Postorder");
        print(levelorder(), "Levelorder");
    }

    // ---------- Height, Size, Leaves ----------
    int height() const { return heightHelper(root); }
    int size() const { return countNodes(root); }
    int countLeaves() const { return countLeavesHelper(root); }
    int countNonLeaves() const { return size() - countLeaves(); }

    // ---------- Find parent ----------
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

    // ---------- Find sibling ----------
    T findNodeSiblings(const T &value) const
    {
        Node<T> *parent = findParent(value);
        if (!parent)
            return T();
        if (parent->left && parent->left->data == value)
            return parent->right ? parent->right->data : T();
        if (parent->right && parent->right->data == value)
            return parent->left ? parent->left->data : T();
        return T();
    }

    // ---------- Descendents ----------
    void displayDescendents(const T &value) const
    {
        Node<T> *target = search(value);
        if (!target)
        {
            cout << "Node not found\n";
            return;
        }
        queue<Node<T> *> q;
        cout << "\nDescendents: ";
        q.push(target);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            q.pop();
            if (curr->data != value)
                cout << curr->data << " ";
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        cout << endl;
    }

    // ---------- Path to node ----------
    vector<T> pathToNode(const T &value) const
    {
        vector<T> path;
        pathToNodeHelper(root, value, path);
        return path;
    }

    // ---------- Clear ----------
    void clear()
    {
        clearHelper(root);
        root = nullptr;
    }

private:
    Node<T> *insertHelper(Node<T> *node, const T &value)
    {
        if (!node)
            return new Node<T>(value);
        if (value < node->data)
            node->left = insertHelper(node->left, value);
        else if (value > node->data)
            node->right = insertHelper(node->right, value);
        else
            throw runtime_error("Duplicate value not allowed in BST");
        return node;
    }

    Node<T> *searchHelper(Node<T> *node, const T &value) const
    {
        if (!node || node->data == value)
            return node;
        if (value < node->data)
            return searchHelper(node->left, value);
        else
            return searchHelper(node->right, value);
    }

    Node<T> *removeHelper(Node<T> *node, const T &value)
    {
        if (!node)
            return nullptr;
        if (value < node->data)
            node->left = removeHelper(node->left, value);
        else if (value > node->data)
            node->right = removeHelper(node->right, value);
        else
        {
            // node to delete found
            if (!node->left)
            {
                Node<T> *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node<T> *temp = node->left;
                delete node;
                return temp;
            }
            Node<T> *temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeHelper(node->right, temp->data);
        }
        return node;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    Node<T> *mirrorClone(Node<T> *node) const
    {
        if (!node)
            return nullptr;
        Node<T> *newNode = new Node<T>(node->data);
        newNode->left = mirrorClone(node->right);
        newNode->right = mirrorClone(node->left);
        return newNode;
    }

    Node<T> *copyHelper(Node<T> *node) const
    {
        if (!node)
            return nullptr;
        Node<T> *newNode = new Node<T>(node->data);
        newNode->left = copyHelper(node->left);
        newNode->right = copyHelper(node->right);
        return newNode;
    }

    void preorderHelper(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        out.push_back(node->data);
        preorderHelper(node->left, out);
        preorderHelper(node->right, out);
    }

    void inorderHelper(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        inorderHelper(node->left, out);
        out.push_back(node->data);
        inorderHelper(node->right, out);
    }

    void postorderHelper(Node<T> *node, vector<T> &out) const
    {
        if (!node)
            return;
        postorderHelper(node->left, out);
        postorderHelper(node->right, out);
        out.push_back(node->data);
    }

    void clearHelper(Node<T> *node)
    {
        if (!node)
            return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
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

    void parenthesizeHelper(Node<T> *node) const
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

    void print(const vector<T> &v, const string &label) const
    {
        cout << label << ": ";
        for (auto x : v)
            cout << x << " ";
        cout << endl;
    }

    bool pathToNodeHelper(Node<T> *node, const T &val, vector<T> &path) const
    {
        if (!node)
            return false;
        path.push_back(node->data);
        if (node->data == val)
            return true;
        if (pathToNodeHelper(node->left, val, path) || pathToNodeHelper(node->right, val, path))
            return true;
        path.pop_back();
        return false;
    }
};

#endif
