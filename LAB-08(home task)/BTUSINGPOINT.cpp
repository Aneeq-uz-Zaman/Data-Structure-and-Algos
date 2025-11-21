#include <iostream>
#include <math.h>
#include <queue>
#include <utility>
using namespace std;

class DNode
{
public:
    int data;
    DNode *rightchild;
    DNode *leftchild;
    explicit DNode(int v) : data(v), rightchild(nullptr), leftchild(nullptr) {}
};

template <class T>
class Binarytree
{
    DNode *root; // minor fix: root is a pointer to DNode

    DNode *search(DNode *curr, T v)
    {
        if (curr == nullptr)
        {
            return nullptr;
        }
        if (curr->data == v)
        {
            return curr;
        }
        DNode *t = search(curr->leftchild, v);
        if (!t)
        {
            t = search(curr->rightchild, v);
        }
        return t;
    }

    void remove(DNode *curr)
    {
        if (curr == nullptr)
        {
            return;
        }
        remove(curr->leftchild);
        remove(curr->rightchild);
        delete curr;
    }

    void preorder(DNode *curr)
    {
        if (curr == nullptr)
        {
            return;
        }
        cout << curr->data << " ";
        preorder(curr->leftchild);
        preorder(curr->rightchild);
    }

    void postorder(DNode *curr)
    {
        if (curr == nullptr)
        {
            return;
        }
        postorder(curr->leftchild);
        postorder(curr->rightchild);
        cout << curr->data << " ";
    }

    void inorder(DNode *curr)
    {
        if (curr == nullptr)
        {
            return;
        }
        inorder(curr->leftchild);
        cout << curr->data << " ";
        inorder(curr->rightchild);
    }

    // ---------- LeetCode-style helpers (private) ----------
    int maxDepthRec(DNode *curr)
    {
        if (!curr) return 0;
        int L = maxDepthRec(curr->leftchild);
        int R = maxDepthRec(curr->rightchild);
        return 1 + (L > R ? L : R);
    }

    DNode* invertTreeRec(DNode *curr)
    {
        if (!curr) return nullptr;
        DNode *L = invertTreeRec(curr->leftchild);
        DNode *R = invertTreeRec(curr->rightchild);
        curr->leftchild = R;
        curr->rightchild = L;
        return curr;
    }

    bool hasPathSumRec(DNode *curr, int target)
    {
        if (!curr) return false;
        int remain = target - curr->data;
        if (!curr->leftchild && !curr->rightchild) // leaf
            return remain == 0;
        return hasPathSumRec(curr->leftchild, remain) || hasPathSumRec(curr->rightchild, remain);
    }

    int sumOfLeftLeavesRec(DNode *curr, bool isLeft)
    {
        if (!curr) return 0;
        if (!curr->leftchild && !curr->rightchild) // leaf
            return isLeft ? curr->data : 0;
        return sumOfLeftLeavesRec(curr->leftchild, true) + sumOfLeftLeavesRec(curr->rightchild, false);
    }

   
    pair<int,int> diameterRec(DNode *curr)
    {
        if (!curr) return {0, 0};
        auto L = diameterRec(curr->leftchild);
        auto R = diameterRec(curr->rightchild);
        int height = 1 + (L.first > R.first ? L.first : R.first);
        int through = L.first + R.first;  
        int best = max(through, max(L.second, R.second));
        return {height, best};
    }

public:
    Binarytree() : root(nullptr) {} // minor safety init

    void setroot(T v)
    {
       
        if (root) { remove(root); }
        root = new DNode((int)v);
    }

    void setleftchild(T p, T v)
    {
        DNode *n = search(root, p);
        if (!n) return;              
        if (n->leftchild == nullptr)
        {
            n->leftchild = new DNode((int)v);
        }
    }

    void setrightchild(T p, T v)
    {
        DNode *n = search(root, p);
        if (!n) return;              
        if (n->rightchild == nullptr)
        {
            n->rightchild = new DNode((int)v);
        }
    }

    void remove(T value)
    {
        DNode *target = search(root, value);
        if (!target)
        {
            cout << "Node with value " << value << " not found.\n";
            return;
        }
        // Note: This deletes the subtree but does not detach it from the parent.
        // Kept as-is per your original logic.
        remove(target);
        cout << "Subtree rooted at " << value << " deleted.\n";
    }

    void Preorder()
    {
        preorder(root);
    }

    void Postorder()
    {
        postorder(root);
    }

    void Inorder()
    {
        inorder(root);
    }

    void levelorder()
    {
        if (!root) return;
        queue<DNode*> Q;                
        Q.push(root);
        while (!Q.empty())               
        {
            DNode *curr = Q.front();    
            Q.pop();
            cout << curr->data << " ";
            if (curr->leftchild)
                Q.push(curr->leftchild);
            if (curr->rightchild)
                Q.push(curr->rightchild);
        }
    }

    
    int maxDepth()
    {
        return maxDepthRec(root);
    }

    void invertTree()
    {
        root = invertTreeRec(root);
    }

    bool hasPathSum(int targetSum)
    {
        return hasPathSumRec(root, targetSum);
    }

    int sumOfLeftLeaves()
    {
        return sumOfLeftLeavesRec(root, false);
    }

    
    int diameterOfBinaryTreeNodes()
    {
        return diameterRec(root).second + 1; 
    }

    void clear()
    {
        remove(root);
        root = nullptr;
    }
};


int main()
{
    Binarytree<int> bt;

    // Build a simple tree
    bt.setroot(10);
    bt.setleftchild(10, 5);
    bt.setrightchild(10, 15);
    bt.setleftchild(5, 3);
    bt.setrightchild(5, 7);
    bt.setleftchild(15, 12);
    bt.setrightchild(15, 18);

    cout << "Preorder:   ";
    bt.Preorder();
    cout << "\nInorder:    ";
    bt.Inorder();
    cout << "\nPostorder:  ";
    bt.Postorder();
    cout << "\nLevelorder: ";
    bt.levelorder();

    
    return 0;
}
