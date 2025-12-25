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
    void rotateLeftCount(int count)
    {
        Node *grandParent = nullptr;
        Node *parent = root;

        for (int i = 0; i < count; i++)
        {
            if (!parent || !parent->right)
                break;

            Node *child = parent->right;

            parent->right = child->left;
            child->left = parent;

            if (!grandParent)
                root = child;
            else
                grandParent->right = child;

            grandParent = child;
            parent = child->left;
        }
    }
    Node *leftRotation(Node *temp)
    {
        Node *temp_right = temp->right;
        temp->right = temp_right->left;
        temp_right->left = temp;
        temp = temp_right;
        return temp;
    }
    Node *rightRotation(Node *temp)
    {
        Node *temp_left = temp->left;
        temp->left = temp_left->right;
        temp_left->right = temp;
        temp = temp_left;
        return temp;
    }
   
public:
    BST() { root = nullptr; }
    ~BST() { destroy(root); }

    void insert(int val)
    {
        root = insertHelper(root, val);
    }

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
    void convertToBackbone()
    {
        Node *temp = root;

        while (temp != nullptr)
        {

            if (temp->left != nullptr)
            {
                Node *child = rightRotation(temp->left);
                temp = child;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    void createPerfectBST()
    {
        convertToBackbone();

        int n = countNodes(root);
        int m = pow(2, log2(n + 1)) - 1;

        rotateLeftCount(n - m);

        while (m > 1)
        {
            m /= 2;
            rotateLeftCount(m);
        }
    }
};
int main()
{
    BST bst;
    bst.insert(1);
    bst.insert(5);
    bst.insert(10);
    bst.insert(20);
    bst.insert(25);
    bst.insert(30);
    bst.insert(35);
    bst.insert(40);
    bst.insert(45);

    cout << "Original BST  Height: " << bst.getHeight()-1 << endl;

    cout << "\nOriginal BST (Inorder): ";
    bst.display_in_order();
    cout << "\nOriginal BST Pre-order: ";
    bst.display_pre_order();

    cout << "\nOriginal BST Post-order: ";
    bst.display_post_order();

    bst.createPerfectBST();

    cout << "\nHeight After DSW: " << bst.getHeight()-2 << endl;

    cout << "\nBalanced BST using DSW (Inorder): ";
    bst.display_in_order();

    cout << "\nBalanced BST using (DSWPre-order:) ";
    bst.display_pre_order();

    cout << "\nBalanced BST using DSW (Post-order:) ";
    bst.display_post_order();

    return 0;
}