#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Node
{
    int rollNo;
    string name;
    double cgpa;
    StudentNode *left;
    StudentNode *right;
};
template <class T>
class BST
{
private:
    Node<T> *root;

    // ----------- Height Utilities -----------
    int getHeight(Node<T> *node)
    {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(Node<T> *node)
    {
        return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node<T> *node)
    {
        if (node)
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x; // new root
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y; // new root
    }

    Node<T> *insertHelper(Node<T> *node, T key)
    {
        if (node == nullptr)
            return new Node<T>(key);

        if (key < node->data)
            node->left = insertHelper(node->left, key);
        else
            node->right = insertHelper(node->right, key);

        updateHeight(node);

        int balance = getBalance(node);

        // LL case
        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        // RR case
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        // LR case
        if (balance > 1 && key > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL case
        if (balance < -1 && key < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ----------- Min/Max -----------
    Node<T> *findMin(Node<T> *node)
    {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    Node<T> *findMax(Node<T> *node)
    {
        while (node && node->right != nullptr)
            node = node->right;
        return node;
    }

    // ----------- Delete with balancing -----------
    Node<T> *deleteNode(Node<T> *node, T key)
    {
        if (!node)
            return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);
        else if (key > node->data)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left || !node->right)
            {
                Node<T> *temp = node->left ? node->left : node->right;

                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (!node)
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // ----------- Traversals -----------
    void inOrderHelper(Node<T> *root)
    {
        if (root)
        {
            inOrderHelper(root->left);
            cout << root->data << " ";
            inOrderHelper(root->right);
        }
    }

    void preOrderHelper(Node<T> *root)
    {
        if (root)
        {
            cout << root->data << " ";
            preOrderHelper(root->left);
            preOrderHelper(root->right);
        }
    }

    void postOrderHelper(Node<T> *root)
    {
        if (root)
        {
            postOrderHelper(root->left);
            postOrderHelper(root->right);
            cout << root->data << " ";
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(T key)
    {
        root = insertHelper(root, key);
    }

    void deleteMethod(T key)
    {
        root = deleteNode(root, key);
    }

    bool search(T key)
    {
        Node<T> *cur = root;
        while (cur)
        {
            if (cur->data == key)
                return true;
            cur = (key < cur->data) ? cur->left : cur->right;
        }
        return false;
    }

    T getMin() { return findMin(root)->data; }
    T getMax() { return findMax(root)->data; }

    void inOrder()
    {
        inOrderHelper(root);
        cout << endl;
    }
    void preOrder()
    {
        preOrderHelper(root);
        cout << endl;
    }
    void postOrder()
    {
        postOrderHelper(root);
        cout << endl;
    }
};

int main()
{
    BST<int> obj;
    obj.insert(5);
    obj.insert(3);
    obj.insert(7);
    obj.insert(2);
    obj.insert(4);
    obj.insert(6);
    obj.insert(8);

    obj.inOrder();
    obj.preOrder();
    obj.postOrder();

    cout << "Min: " << obj.getMin() << endl;
    cout << "Max: " << obj.getMax() << endl;

    obj.deleteMethod(2);
    obj.inOrder();
}