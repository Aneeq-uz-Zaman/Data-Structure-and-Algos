#include "binarytree.h"
using namespace std;

int main() {
    NodeBinaryTree<int> tree;
    


    tree.setRoot(10);
    Node<int>* root = tree.root;
    Node<int>* left = tree.setLeftChild(root, 20);
    Node<int>* right = tree.setRightChild(root, 30);
    tree.setLeftChild(left, 40);
    tree.setRightChild(left, 50);
    tree.setLeftChild(right, 60);
    tree.setRightChild(right, 70);
    

    cout << "All Orders:\n";
    tree.printAllOrders();
    NodeBinaryTree<int> tree2=tree.getMirrorImage(); 
    cout << "All Orders:\n";
    tree2.printAllOrders();

    cout << "\nSearching 50: ";
    cout << (tree.SEARCH(50) ? "Found" : "Not Found") << endl;
    cout<<tree.height()<<endl;
    cout<<tree.findNodeSiblings(50);
    tree.displayDescendents(20);
    tree.parenthesize();


    cout << "\nRemoving 20..." << endl;
    tree.REMOVE(20);
    tree.printAllOrders();
    return 0;
}
