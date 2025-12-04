#include "BST.h"
#include <iostream>
int main()
{
    BST<int> tree;

    // ---------- Insert nodes ----------
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    cout << "Original BST (parenthesized view): ";
    tree.parenthesize();

    // ---------- Traversals ----------
    cout << "\nAll Traversals:" << endl;
    tree.printAllOrders();

    // ---------- Mirror Image ----------
    BST<int> mirrorTree = tree.getMirrorImage();
    cout << "\nMirror BST (parenthesized view): ";
    mirrorTree.parenthesize();

    // ---------- Search ----------
    int searchVal = 40;
    Node<int> *found = tree.search(searchVal);
    if (found)
        cout << "\nNode " << searchVal << " found in BST." << endl;
    else
        cout << "\nNode " << searchVal << " NOT found in BST." << endl;

    // ---------- Find Parent ----------
    Node<int> *parent = tree.findParent(40);
    if (parent)
        cout << "Parent of 40: " << parent->data << endl;

    // ---------- Find Sibling ----------
    int sibling = tree.findNodeSiblings(40);
    cout << "Sibling of 40: " << (sibling ? sibling : -1) << endl;

    // ---------- Path to Node ----------
    vector<int> path = tree.pathToNode(60);
    cout << "Path to 60: ";
    for (int val : path)
        cout << val << " ";
    cout << endl;

    // ---------- Descendents ----------
    tree.displayDescendents(30);

    

    // ---------- Remove ----------
    // cout << "\nRemoving 20..." << endl;
    // tree.remove(20);
    // tree.parenthesize();

    // ---------- Rotations ----------
    cout << "\nRotating right at root..." << endl;
    tree.root = tree.rotateRight(tree.root);
    tree.parenthesize();

    cout << "\nRotating left at root..." << endl;
    tree.root = tree.rotateLeft(tree.root);
    tree.parenthesize();

    // ---------- Tree info ----------
    cout << "\nHeight: " << tree.height() << endl;
    cout << "Size: " << tree.size() << endl;
    cout << "Leaves: " << tree.countLeaves() << endl;
    cout << "Non-leaves: " << tree.countNonLeaves() << endl;

    return 0;
}
