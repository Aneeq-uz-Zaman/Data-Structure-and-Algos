#ifndef NODE_BINARY_TREE_H
#define NODE_BINARY_TREE_H

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;
    Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class NodeBinaryTree {
public:
    Node<T>* root;

    NodeBinaryTree() : root(nullptr) {}
    ~NodeBinaryTree() { clear(); }

    bool isEmpty() const { return root == nullptr; }

    void clear(Node<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void clear() { clear(root); root = nullptr; }

    // ---------------- BASIC STRUCTURE BUILDERS ----------------
    void setRoot(const T& value) {
        clear(root);
        root = new Node<T>(value);
    }

    Node<T>* setLeftChild(Node<T>* parent, const T& value) {
        if (!parent) throw runtime_error("Parent is null");
        if (parent->left) throw runtime_error("Left child already exists");
        parent->left = new Node<T>(value);
        return parent->left;
    }

    Node<T>* setRightChild(Node<T>* parent, const T& value) {
        if (!parent) throw runtime_error("Parent is null");
        if (parent->right) throw runtime_error("Right child already exists");
        parent->right = new Node<T>(value);
        return parent->right;
    }

    void insertLevelOrder(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!root) { root = newNode; return; }
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            if (!curr->left) { curr->left = newNode; return; }
            if (!curr->right) { curr->right = newNode; return; }
            q.push(curr->left);
            q.push(curr->right);
        }
    }

    // ---------------- SEARCH & REMOVE ----------------
    Node<T>* SEARCH(const T& value) const {
        if (!root) return nullptr;
        queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            if (curr->data == value) return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return nullptr;
    }

    bool REMOVE(const T& value) {
        if (!root) return false;
        if (!root->left && !root->right) {
            if (root->data == value) { delete root; root = nullptr; return true; }
            return false;
        }
        queue<Node<T>*> q;
        q.push(root);
        Node<T>* target = nullptr;
        Node<T>* last = nullptr;
        Node<T>* parentOfLast = nullptr;
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            if (curr->data == value) target = curr;
            if (curr->left) { parentOfLast = curr; last = curr->left; q.push(curr->left); }
            if (curr->right) { parentOfLast = curr; last = curr->right; q.push(curr->right); }
        }
        if (!target) return false;
        if (last) {
            target->data = last->data;
            if (parentOfLast->right == last) parentOfLast->right = nullptr;
            else parentOfLast->left = nullptr;
            delete last;
        }
        return true;
    }

    // ---------------- TRAVERSALS ----------------
    vector<T> PREORDER() const { vector<T> out; preorder(root, out); return out; }
    vector<T> INORDER() const { vector<T> out; inorder(root, out); return out; }
    vector<T> POSTORDER() const { vector<T> out; postorder(root, out); return out; }
    vector<T> LEVELORDER() const {
        vector<T> out; if (!root) return out;
        queue<Node<T>*> q; q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            out.push_back(curr->data);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return out;
    }

    // ---------------- INFO FUNCTIONS ----------------
    int height() const { return heightHelper(root); }
    int size() const { return countNodes(root); }
    int countLeaves() const { return countLeavesHelper(root); }
    int countNonLeaves() const { return size() - countLeaves(); }

    T findMin() const {
        if (!root) throw runtime_error("Empty tree");
        T m = root->data;
        queue<Node<T>*> q; q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            m = min(m, curr->data);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return m;
    }

    T findMax() const {
        if (!root) throw runtime_error("Empty tree");
        T M = root->data;
        queue<Node<T>*> q; q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            M = max(M, curr->data);
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return M;
    }

    Node<T>* findParent(const T& value) const {
        if (!root || root->data == value) return nullptr;
        queue<Node<T>*> q; q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            if ((curr->left && curr->left->data == value) ||
                (curr->right && curr->right->data == value))
                return curr;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return nullptr;
    }

    void deleteParentOf(const T& value) {
        if (!root) return;
        if (root->data == value) return;
        queue<Node<T>*> q; q.push(root);
        while (!q.empty()) {
            Node<T>* curr = q.front(); q.pop();
            if ((curr->left && curr->left->data == value) ||
                (curr->right && curr->right->data == value)) {
                REMOVE(curr->data);
                return;
            }
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    vector<T> pathToNode(const T& value) const {
        vector<T> path;
        if (!root) return path;
        bool found = pathToNodeHelper(root, value, path);
        if (!found) path.clear();
        return path;
    }

    // ---------------- DISPLAY HELPERS ----------------
    void print(const vector<T>& v, const string& label) const {
        cout << label << ": ";
        for (auto& x : v) cout << x << " ";
        cout << endl;
    }

    void printAllOrders() const {
        print(PREORDER(), "Preorder");
        print(INORDER(), "Inorder");
        print(POSTORDER(), "Postorder");
        print(LEVELORDER(), "Levelorder");
    }

private:
    // Recursive traversal helpers
    void preorder(Node<T>* node, vector<T>& out) const {
        if (!node) return;
        out.push_back(node->data);
        preorder(node->left, out);
        preorder(node->right, out);
    }

    void inorder(Node<T>* node, vector<T>& out) const {
        if (!node) return;
        inorder(node->left, out);
        out.push_back(node->data);
        inorder(node->right, out);
    }

    void postorder(Node<T>* node, vector<T>& out) const {
        if (!node) return;
        postorder(node->left, out);
        postorder(node->right, out);
        out.push_back(node->data);
    }

    int heightHelper(Node<T>* node) const {
        if (!node) return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    int countNodes(Node<T>* node) const {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeavesHelper(Node<T>* node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }

    bool pathToNodeHelper(Node<T>* node, const T& val, vector<T>& path) const {
        if (!node) return false;
        path.push_back(node->data);
        if (node->data == val) return true;
        if (pathToNodeHelper(node->left, val, path) ||
            pathToNodeHelper(node->right, val, path)) return true;
        path.pop_back();
        return false;
    }
};

#endif
