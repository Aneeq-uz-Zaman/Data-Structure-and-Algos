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
    int data;     
    string name;    
       

    double cgpa;
    Node<T> *left;
    Node<T> *right;
    Node(const int &val,const double &val1,const string &val2) : data(val),cgpa(val1),name(val2), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST
{
public:

    Node<T> *root;

 
    bool insert(const int &val,const double &val1,const string &val2)
    {
        insertHelper(root, val ,val1,val2);
        return true;
        
    }


    Node<T> *search(const int &val,const double &val1,const string &val2) const
    {
        return insertHelper(root, val ,val1,val2);
    }


    void remove(const T &value)
    {
        root = removeHelper(root, value);
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

   

private:
    Node<T> *insertHelper(Node<T> *node, const int &val,const double &val1,const string &val2)
    {
        if (!node)
            return new Node<T>(val,val1,val2);
        if (val < node->data)
            node->left = insertHelper(node->left, val ,val1,val2);
        else if (val > node->data)
            node->right = insertHelper(node->right, val ,val1,val2);
        else
            throw runtime_error("Duplicate value not allowed in BST");
        return node;
    }

    Node<T> *searchHelper(Node<T> *node,const int &val,const double &val1,const string &val2) const
    {
        if (!node || node->data == val )
            return node;
        if (val < node->data)
            return searchHelper(node->left, val ,val1,val2);
        else
            return searchHelper(node->right, val ,val1,val2);
    }

    // Node<T> *removeHelper(Node<T> *node, const int &val,const double &val1,const string &val2)
    // {
    //     if (!node)
    //         return nullptr;
    //     if (value < node->data)
    //         node->left = removeHelper(node->left, val ,val1,val2);
    //     else if (value > node->data)
    //         node->right = removeHelper(node->right, val ,val1,val2);
    //     else
    //     {
    //         // node to delete found
    //         if (!node->left)
    //         {
    //             Node<T> *temp = node->right;
    //             delete node;
    //             return temp;
    //         }
    //         else if (!node->right)
    //         {
    //             Node<T> *temp = node->left;
    //             delete node;
    //             return temp;
    //         }
    //         Node<T> *temp = minValueNode(node->right);
    //         node->data = temp->data;
    //         node->right = removeHelper(node->right, temp->data);
    //     }
    //     return node;
    // }

    
};

#endif
