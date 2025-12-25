#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

class BST
{
private:
    Node *root;

    Node *insertHelper(Node *p, int val)
    {
        if (!p)
            return new Node(val);
        if (val < p->data)
            p->left = insertHelper(p->left, val);
        else
            p->right = insertHelper(p->right, val);
        return p;
    }

    void destroy(Node *p)
    {
        if (!p)
            return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }

    void inOrder(Node *p)
    {
        if (!p)
            return;
        inOrder(p->left);
        cout << p->data << " ";
        inOrder(p->right);
    }

    void preOrder(Node *p)
    {
        if (!p)
            return;
        cout << p->data << " ";
        preOrder(p->left);
        preOrder(p->right);
    }

    void postOrder(Node *p)
    {
        if (!p)
            return;
        postOrder(p->left);
        postOrder(p->right);
        cout << p->data << " ";
    }

    int height(Node *p)
    {
        if (!p)
            return 0;
        return 1 + max(height(p->left), height(p->right));
    }

    Node *buildTree(vector<int> &inorder, vector<int> &preorder, int inStart, int inEnd, int &preIndex)
    {

        if (inStart > inEnd)
            return nullptr;

        int rootVal = preorder[preIndex];
        preIndex++;
        cout << rootVal << endl;
        Node *node = new Node(rootVal);

        int mid = 0;
        for (int i = inStart; i <= inEnd; i++)
            if (inorder[i] == rootVal)
                mid = i;

        node->left = buildTree(inorder, preorder, inStart, mid - 1, preIndex);
        node->right = buildTree(inorder, preorder, mid + 1, inEnd, preIndex);

        return node;
    }

    int countNodes(Node *p)
    {
        if (!p)
            return 0;
        return 1 + countNodes(p->left) + countNodes(p->right);
    }

    void buildBalanced(int *arr, int start, int end)
    {
        if (start > end)
            return;
        int mid = (start + end) / 2;
        insert(arr[mid]);
        buildBalanced(arr, start, mid - 1);
        buildBalanced(arr, mid + 1, end);
    }

public:
    BST() { root = nullptr; }
    ~BST() { destroy(root); }

    void insert(int val) { root = insertHelper(root, val); }

    void display_in_order()
    {
        inOrder(root);
        cout << endl;
    }
    void display_pre_order()
    {
        preOrder(root);
        cout << endl;
    }
    void display_post_order()
    {
        postOrder(root);
        cout << endl;
    }

    int getHeight() { return height(root); }

    void construct_from_traversals(vector<int> in_order, vector<int> pre_order)
    {
        destroy(root);
        root = nullptr;

        int preIndex = 0;
        root = buildTree(in_order, pre_order, 0, in_order.size() - 1, preIndex);
    }
    void createBalancedTree(int *arr, int start, int end)
    {
        destroy(root);
        root = nullptr;
        buildBalanced(arr, start, end);
    }
};
int main()
{
    BST bst;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    bst.createBalancedTree(arr, 0, n - 1);
    cout << "Pre-order: ";
    bst.display_pre_order();
    cout << "In-order: ";
    bst.display_in_order();
    cout << "Post-order: ";
    bst.display_post_order();
    return 0;
}