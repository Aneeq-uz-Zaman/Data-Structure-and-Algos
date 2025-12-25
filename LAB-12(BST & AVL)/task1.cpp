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
};

int main()
{

    BST bst1;
    vector<int> in1 = {1, 2, 3, 4, 5, 6};
    vector<int> pre1 = {3, 1, 2, 5, 4, 6};

    bst1.construct_from_traversals(in1, pre1);

    cout << "Inorder: ";
    bst1.display_in_order();
    cout << "Postorder: ";
    bst1.display_post_order();

    BST bst2;
    vector<int> in2 = {5, 10, 15, 25, 27, 30, 35, 40, 45, 50, 52, 55, 60, 65, 70, 75, 80, 85, 90, 100};
    vector<int> pre2 = {50, 25, 10, 5, 15, 40, 30, 27, 35, 45, 75, 60, 55, 52, 65, 70, 90, 80, 85, 100};

    bst2.construct_from_traversals(in2, pre2);

    cout << "\nIn-order traversal (Example 2): ";
    bst2.display_in_order();

    cout << "Post-order traversal (Example 2): ";
    bst2.display_post_order();
    return 0;
}