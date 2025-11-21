#include "binaryarray.h"
using namespace std;

int main() {
    ArrayBinaryTree<int> tree(15);
    tree.buildTree({1, 2, 3, 4, 5, 6, 7, 8});

    cout << "Tree elements (level order): ";
    tree.display();

    auto inorder = tree.inorder();
    cout << "Inorder: ";
    for (int x : inorder) cout << x << " ";
    cout << endl;

    cout << "Depth of index 7: " << tree.findDepth(7) << endl;
    cout << "Height of tree: " << tree.findHeight() << endl;
    cout << "Parent of index 4: " << tree.getParent(4) << endl;
    cout << "Left child of index 2: " << tree.getLeftChild(2) << endl;
    cout << "Right child of index 2: " << tree.getRightChild(2) << endl;

    cout << "Leaf nodes: " << tree.countLeaves() << endl;
    cout << "Non-leaf nodes: " << tree.countNonLeaves() << endl;

    cout << "Path to index 7: ";
    for (int x : tree.pathToNode(7)) cout << x << " ";
    cout << endl;

    cout << "Mirroring tree...\n";
    tree.mirror();
    tree.display();
}
