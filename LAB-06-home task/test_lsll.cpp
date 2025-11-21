#include <iostream>
#include "lsll.h"
using namespace std;

int main() {
    cout << "=== TEST 1: Insertion Functions ===\n";
    LSLL<int> list;

    list.insertAtHead(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertBefore(10, 5);
    list.insertAfter(20, 25);

    cout << "List after insertions: ";
    list.display();        // Expected: 5 10 20 25 30

    cout << "\n=== TEST 2: Deletion Functions ===\n";
    list.remove(25);
    list.removeAtHead();
    list.removeAtTail();
    list.insertAtTail(40);
    list.insertAtTail(50);
    list.insertAtTail(60);
    cout << "List after deletions: ";
    list.display();        // Expected: 10 20 40 50 60

    list.removeBefore(40);
    cout << "After removeBefore(40): ";
    list.display();        // Expected: 10 40 50 60

    list.removeAfter(40);
    cout << "After removeAfter(40): ";
    list.display();        // Expected: 10 40 60

    cout << "\n=== TEST 3: Search, Update, Count ===\n";
    cout << "Search(40): " << (list.search(40) ? "Found" : "Not Found") << endl;
    list.update(40, 99);
    cout << "After update(40->99): ";
    list.display();        // Expected: 10 99 60
    cout << "Total Nodes: " << list.countNodes() << endl;  // Expected: 3

    cout << "\n=== TEST 4: Reverse & Reverse Display ===\n";
    list.reverseList();
    cout << "Reversed List: ";
    list.display();        // Expected: 60 99 10
    cout << "Reverse Display (without reversing): ";
    list.reverse_display(); // Expected: 10 99 60

    cout << "\n=== TEST 5: Middle Node ===\n";
    Node<int>* mid = list.getMiddleNode();
    if (mid) cout << "Middle node: " << mid->info << endl;  // Expected: 99

    cout << "\n=== TEST 6: Palindrome Check ===\n";
    LSLL<int> pal;
    pal.insertAtTail(1);
    pal.insertAtTail(2);
    pal.insertAtTail(3);
    pal.insertAtTail(2);
    pal.insertAtTail(1);
    pal.display();   // 1 2 3 2 1
    cout << "Is Palindrome? " << (pal.isPalindrome() ? "YES" : "NO") << endl; // YES

    cout << "\n=== TEST 7: Remove Duplicates (Sorted) ===\n";
    LSLL<int> sortedDup;
    sortedDup.insertAtTail(1);
    sortedDup.insertAtTail(1);
    sortedDup.insertAtTail(2);
    sortedDup.insertAtTail(2);
    sortedDup.insertAtTail(3);
    sortedDup.display();   // 1 1 2 2 3
    sortedDup.removeDuplicatesSorted();
    cout << "After removeDuplicatesSorted: ";
    sortedDup.display();   // 1 2 3

    cout << "\n=== TEST 8: Remove Duplicates (Unsorted) ===\n";
    LSLL<int> unsortedDup;
    unsortedDup.insertAtTail(5);
    unsortedDup.insertAtTail(1);
    unsortedDup.insertAtTail(3);
    unsortedDup.insertAtTail(5);
    unsortedDup.insertAtTail(1);
    unsortedDup.insertAtTail(2);
    unsortedDup.display();   // 5 1 3 5 1 2
    unsortedDup.removeDuplicatesUnsorted();
    cout << "After removeDuplicatesUnsorted: ";
    unsortedDup.display();   // 5 1 3 2

    cout << "\n=== TEST 9: Merge Two Sorted Lists ===\n";
    LSLL<int> A, B;
    A.insertAtTail(1);
    A.insertAtTail(3);
    A.insertAtTail(5);

    B.insertAtTail(2);
    B.insertAtTail(4);
    B.insertAtTail(6);

    cout << "List A: ";
    A.display();
    cout << "List B: ";
    B.display();

    LSLL<int> C = LSLL<int>::mergeSortedLists(A, B);
    cout << "Merged List (A+B): ";
    C.display();   // 1 2 3 4 5 6

    cout << "\n=== ALL TESTS COMPLETED SUCCESSFULLY ===\n";
    return 0;
}
