#ifndef ARRAY_BINARY_TREE_PROBLEMS_H
#define ARRAY_BINARY_TREE_PROBLEMS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
class ArrayBinaryTree {
private:
    vector<T> tree;
    int capacity;
    int lastIndex;

    void inorderHelper(int idx, vector<T>& out) const {
        if (idx > lastIndex) return;
        inorderHelper(2 * idx, out);
        out.push_back(tree[idx]);
        inorderHelper(2 * idx + 1, out);
    }

    void preorderHelper(int idx, vector<T>& out) const {
        if (idx > lastIndex) return;
        out.push_back(tree[idx]);
        preorderHelper(2 * idx, out);
        preorderHelper(2 * idx + 1, out);
    }

    void postorderHelper(int idx, vector<T>& out) const {
        if (idx > lastIndex) return;
        postorderHelper(2 * idx, out);
        postorderHelper(2 * idx + 1, out);
        out.push_back(tree[idx]);
    }

    void mirrorHelper(int idx) {
        if (idx > lastIndex) return;
        int left = 2 * idx, right = 2 * idx + 1;
        if (left <= lastIndex && right <= lastIndex)
            swap(tree[left], tree[right]);
        mirrorHelper(left);
        mirrorHelper(right);
    }

public:
    ArrayBinaryTree(int size = 100) {
        capacity = size;
        tree.resize(capacity + 1);
        lastIndex = 0;
    }

    void insert(const T& value) {
        if (lastIndex >= capacity) return;
        lastIndex++;
        tree[lastIndex] = value;
    }

    void buildTree(const vector<T>& values) {
        lastIndex = min((int)values.size(), capacity);
        for (int i = 1; i <= lastIndex; i++)
            tree[i] = values[i - 1];
    }

    T getParent(int i) const {
        if (i <= 1 || i > lastIndex)
            throw out_of_range("No parent");
        return tree[i / 2];
    }

    T getLeftChild(int i) const {
        int left = 2 * i;
        if (left > lastIndex)
            throw out_of_range("No left child");
        return tree[left];
    }

    T getRightChild(int i) const {
        int right = 2 * i + 1;
        if (right > lastIndex)
            throw out_of_range("No right child");
        return tree[right];
    }

    vector<T> inorder() const {
        vector<T> out;
        inorderHelper(1, out);
        return out;
    }

    vector<T> preorder() const {
        vector<T> out;
        preorderHelper(1, out);
        return out;
    }

    vector<T> postorder() const {
        vector<T> out;
        postorderHelper(1, out);
        return out;
    }

    vector<T> levelOrder() const {
        vector<T> out;
        for (int i = 1; i <= lastIndex; i++)
            out.push_back(tree[i]);
        return out;
    }

    int findDepth(int i) const {
        if (i < 1 || i > lastIndex) throw out_of_range("Invalid index");
        return (int)floor(log2(i));
    }

    int findHeight() const {
        if (lastIndex == 0) return 0;
        return (int)floor(log2(lastIndex));
    }

    bool isComplete() const {
        for (int i = 1; i <= lastIndex; i++)
            if (tree[i] == T()) return false;
        return true;
    }

    int countLeaves() const {
        int count = 0;
        for (int i = 1; i <= lastIndex; i++) {
            int left = 2 * i, right = 2 * i + 1;
            if (left > lastIndex && right > lastIndex)
                count++;
        }
        return count;
    }

    int countNonLeaves() const {
        return lastIndex - countLeaves();
    }

    void mirror() {
        mirrorHelper(1);
    }

    vector<T> pathToNode(int i) const {
        vector<T> path;
        while (i >= 1 && i <= lastIndex) {
            path.push_back(tree[i]);
            if (i == 1) break;
            i /= 2;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void display() const {
        for (int i = 1; i <= lastIndex; i++)
            cout << tree[i] << " ";
        cout << endl;
    }

    int size() const {
        return lastIndex;
    }
};

#endif
