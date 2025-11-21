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

    cout << "\nSearching 50: ";
    cout << (tree.SEARCH(50) ? "Found" : "Not Found") << endl;

    cout << "\nRemoving 20..." << endl;
    tree.REMOVE(20);
    tree.printAllOrders();

    cout << "\nMin: " << tree.findMin() << endl;
    cout << "Max: " << tree.findMax() << endl;

    cout << "\nPath to 70: ";
    for (auto x : tree.pathToNode(70)) cout << x << " ";
    cout << endl;

    cout << "\nDeleting parent of 70..." << endl;
    tree.deleteParentOf(70);
    tree.printAllOrders();

    return 0;
}
