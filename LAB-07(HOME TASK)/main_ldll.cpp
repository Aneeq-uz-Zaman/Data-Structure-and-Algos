#include <iostream>
#include "LDLL.H"

using namespace std;

template <typename T>
void printWith(const char* label, LDLL<T>& list) {
    cout << label;
    list.display();
}

int main() {
    cout << "--- LDLL<T> basic operations ---\n";
    LDLL<int> l;
    l.insertAtHead(3);
    l.insertAtHead(2);
    l.insertAtHead(1);
    l.insertAtTail(4);
    printWith("Initial: ", l); // 1 2 3 4

    l.insertBefore(3, 99);
    l.insertAfter(3, 100);
    printWith("After insertBefore/After 3: ", l); // 1 2 99 3 100 4

    cout << "search(99): " << l.search(99) << "\n";
    l.update(99, 9);
    printWith("After update 99->9: ", l);
    cout << "countNodes(): " << l.countNodes() << "\n";

    l.removeBefore(3); // remove 9
    l.removeAfter(3);  // remove 100
    l.remove(4);
    printWith("After removals: ", l); // 1 2 3

    l.reverseList();
    printWith("After reverseList: ", l); // 3 2 1
    cout << "Middle value: " << l.findMiddle() << "\n";

    // Palindrome test
    LDLL<int> pal;
    pal.insertAtTail(1); pal.insertAtTail(2); pal.insertAtTail(3); pal.insertAtTail(2); pal.insertAtTail(1);
    printWith("Palindrome list: ", pal);
    cout << "isPalindrome(): " << (pal.isPalindrome() ? "true" : "false") << "\n";

    // Duplicates removal (unsorted)
    LDLL<int> dup;
    dup.insertAtTail(5); dup.insertAtTail(1); dup.insertAtTail(5); dup.insertAtTail(2); dup.insertAtTail(1);
    printWith("Before removeDuplicatesUnsorted: ", dup);
    dup.removeDuplicatesUnsorted();
    printWith("After removeDuplicatesUnsorted: ", dup);

    // Merge two sorted lists
    LDLL<int> a; a.insertAtTail(1); a.insertAtTail(3); a.insertAtTail(5);
    LDLL<int> b; b.insertAtTail(2); b.insertAtTail(4); b.insertAtTail(6);
    auto merged = LDLL<int>::mergeSortedLists(a, b);
    printWith("Merged sorted: ", merged);

    // New reversed list (copy)
    LDLL<int>* rl = merged.reverselist();
    printWith("reverselist(copy): ", *rl);
    delete rl;

    // Kth removal + swap + sort
    merged.removeKthNode(2); // remove '2'
    printWith("After removeKthNode(2): ", merged);
    merged.swapNodes(1, 5);
    printWith("After swapNodes(1,5): ", merged);
    merged.sort();
    printWith("After sort(): ", merged);

    cout << "All LDLL tests finished.\n";
    return 0;
}
