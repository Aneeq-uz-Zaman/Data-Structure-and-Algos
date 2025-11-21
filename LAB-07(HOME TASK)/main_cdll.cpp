#include <iostream>
#include "CDLL.H"

using namespace std;

template <typename T>
void printWith(const char* label, CDLL<T>& list) {
    cout << label;
    list.display();
}

int main() {
    cout << "--- CDLL<T> basic operations ---\n";
    CDLL<int> l;
    l.insertAtHead(20);
    l.insertAtHead(10);
    l.insertAtTail(30);
    l.insertAtTail(40);
    printWith("Initial: ", l); // 10 20 30 40

    l.insertBefore(30, 25);
    l.insertAfter(30, 35);
    printWith("After insertBefore/After 30: ", l); // 10 20 25 30 35 40

    cout << "search(25): " << l.search(25) << "\n";
    l.update(25, 26);
    printWith("After update 25->26: ", l);
    cout << "countNodes(): " << l.countNodes() << "\n";

    l.removeBefore(30); // remove 26
    l.removeAfter(30);  // remove 35
    l.removeAtHead();   // remove 10
    l.removeAtTail();   // remove 40
    printWith("After removals: ", l); // 20 30

    l.reverseList();
    printWith("After reverseList: ", l); // 30 20
    cout << "Middle value: " << l.findMiddle() << "\n";

    // Palindrome test
    CDLL<int> pal;
    pal.insertAtTail(1); pal.insertAtTail(2); pal.insertAtTail(3); pal.insertAtTail(2); pal.insertAtTail(1);
    printWith("Palindrome list: ", pal);
    cout << "isPalindrome(): " << (pal.isPalindrome() ? "true" : "false") << "\n";

    // Duplicates removal (unsorted)
    CDLL<int> dup;
    dup.insertAtTail(5); dup.insertAtTail(1); dup.insertAtTail(5); dup.insertAtTail(2); dup.insertAtTail(1);
    printWith("Before removeDuplicatesUnsorted: ", dup);
    dup.removeDuplicatesUnsorted();
    printWith("After removeDuplicatesUnsorted: ", dup);

    // Merge two sorted circles
    CDLL<int> a; a.insertAtTail(1); a.insertAtTail(3); a.insertAtTail(5);
    CDLL<int> b; b.insertAtTail(2); b.insertAtTail(4); b.insertAtTail(6);
    auto merged = CDLL<int>::mergeSortedLists(a, b);
    printWith("Merged sorted: ", merged);

    // New reversed list (copy)
    CDLL<int>* rl = merged.reverselist();
    printWith("reverselist(copy): ", *rl);
    delete rl;

    // Kth removal + swap + sort
    merged.removeKthNode(2); // remove second
    printWith("After removeKthNode(2): ", merged);
    merged.swapNodes(1, 5);
    printWith("After swapNodes(1,5): ", merged);
    merged.sort();
    printWith("After sort(): ", merged);

    cout << "All CDLL tests finished.\n";
    return 0;
}
