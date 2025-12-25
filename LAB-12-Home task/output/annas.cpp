#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) { data = val; left = right = nullptr; }
};

class BST {
private:
    Node* root;

    /*---------------- BASIC HELPERS ----------------*/

    Node* insertHelper(Node* p, int val) {
        if (!p) return new Node(val);
        if (val < p->data) p->left = insertHelper(p->left, val);
        else p->right = insertHelper(p->right, val);
        return p;
    }

    void destroy(Node* p) {
        if (!p) return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }

    void inOrder(Node* p) {
        if (!p) return;
        inOrder(p->left);
        cout << p->data << " ";
        inOrder(p->right);
    }

    void preOrder(Node* p) {
        if (!p) return;
        cout << p->data << " ";
        preOrder(p->left);
        preOrder(p->right);
    }

    void postOrder(Node* p) {
        if (!p) return;
        postOrder(p->left);
        postOrder(p->right);
        cout << p->data << " ";
    }

    int height(Node* p) {
        if (!p) return 0;
        return 1 + max(height(p->left), height(p->right));
    }

    /*---------------- TASK-1: BUILD FROM TRAVERSALS ----------------*/

    Node* buildTree(vector<int>& inorder, vector<int>& preorder,
                    int inStart, int inEnd, int& preIndex) {

        if (inStart > inEnd) return nullptr;

        int rootVal = preorder[preIndex++];
        Node* node = new Node(rootVal);

        int mid = 0;
        for (int i = inStart; i <= inEnd; i++)
            if (inorder[i] == rootVal) mid = i;

        node->left = buildTree(inorder, preorder, inStart, mid - 1, preIndex);
        node->right = buildTree(inorder, preorder, mid + 1, inEnd, preIndex);

        return node;
    }

    /*---------------- TASK-2: BALANCED TREE FROM SORTED ARRAY ----------------*/

    void buildBalanced(int* arr, int start, int end) {
        if (start > end) return;
        int mid = (start + end) / 2;
        insert(arr[mid]);
        buildBalanced(arr, start, mid - 1);
        buildBalanced(arr, mid + 1, end);
    }

    /*---------------- TASK-3: DSW ALGORITHM ----------------*/

    // Convert BST to backbone (vine)
    void convertToBackboneInternal() {
        Node* grandParent = nullptr;
        Node* parent = root;

        while (parent != nullptr) {

            if (parent->left != nullptr) {
                Node* child = parent->left;

                parent->left = child->right;
                child->right = parent;

                if (grandParent == nullptr)
                    root = child;
                else
                    grandParent->right = child;

                parent = child;

            } else {
                grandParent = parent;
                parent = parent->right;
            }
        }
    }

    int countNodes(Node* p) {
        if (!p) return 0;
        return 1 + countNodes(p->left) + countNodes(p->right);
    }

    void rotateLeftCount(int count) {
        Node* grandParent = nullptr;
        Node* parent = root;

        for (int i = 0; i < count; i++) {
            if (!parent || !parent->right) break;

            Node* child = parent->right;

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

public:

    BST() { root = nullptr; }
    ~BST() { destroy(root); }

    void insert(int val) { root = insertHelper(root, val); }

    void display_in_order() { inOrder(root); cout << endl; }
    void display_pre_order() { preOrder(root); cout << endl; }
    void display_post_order() { postOrder(root); cout << endl; }

    int getHeight() { return height(root); }

    /*---------------- TASK-1 PUBLIC ----------------*/

    void construct_from_traversals(vector<int> in_order, vector<int> pre_order) {
        destroy(root);
        root = nullptr;

        int preIndex = 0;
        root = buildTree(in_order, pre_order, 0, in_order.size() - 1, preIndex);
    }

    /*---------------- TASK-2 PUBLIC ----------------*/

    void createBalancedTree(int* arr, int start, int end) {
        destroy(root);
        root = nullptr;
        buildBalanced(arr, start, end);
    }

    /*---------------- TASK-3 PUBLIC ----------------*/

    void convertToBackbone() { convertToBackboneInternal(); }

    void createPerfectBST() {
        convertToBackbone();

        int n = countNodes(root);
        int m = pow(2, floor(log2(n + 1))) - 1;

        rotateLeftCount(n - m);

        while (m > 1) {
            m /= 2;
            rotateLeftCount(m);
        }
    }
};

/*===================================================
                MAIN PROGRAM
===================================================*/

int main() {

    cout << "================= TASK 1 =================\n";

    BST bst1;
    vector<int> in1 = {1,2,3,4,5,6};
    vector<int> pre1 = {3,1,2,5,4,6};

    bst1.construct_from_traversals(in1, pre1);

    cout << "Inorder: "; bst1.display_in_order();
    cout << "Postorder: "; bst1.display_post_order();


    cout << "\n================= TASK 2 =================\n";

    BST bst2;
    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    int n = sizeof(arr)/sizeof(arr[0]);

    bst2.createBalancedTree(arr, 0, n-1);

    cout << "Preorder: "; bst2.display_pre_order();
    cout << "Inorder: "; bst2.display_in_order();
    cout << "Postorder: "; bst2.display_post_order();


    cout << "\n================= TASK 3 (DSW) =================\n";

    BST bst3;
    bst3.insert(1);
    bst3.insert(5);
    bst3.insert(10);
    bst3.insert(20);
    bst3.insert(25);
    bst3.insert(30);
    bst3.insert(35);
    bst3.insert(40);
    bst3.insert(45);

    cout << "Original Height: " << bst3.getHeight() << endl;

    bst3.createPerfectBST();

    cout << "Height After DSW: " << bst3.getHeight() << endl;

    cout << "Inorder: "; bst3.display_in_order();
    cout << "Preorder: "; bst3.display_pre_order();
    cout << "Postorder: "; bst3.display_post_order();

    return 0;
}