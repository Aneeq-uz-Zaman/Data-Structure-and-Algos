#ifndef CSLL_H
#define CSLL_H

#include <iostream>
#include <stdexcept>
using namespace std;

// Circular Singly Linked List Node
template <class T>
class CSNode {
public:
    T info;
    CSNode<T>* next;
    CSNode() : info(), next(nullptr) {}
    CSNode(T val) : info(val), next(nullptr) {}
};

// Circular Singly Linked List
template <class T>
class CSLL {
private:
    CSNode<T>* head;
    CSNode<T>* tail;

    void reverse_display_from(CSNode<T>* curr, CSNode<T>* stop) {
        if (!curr || !stop) return;
        if (curr->next != stop)
            reverse_display_from(curr->next, stop);
        cout << curr->info << " ";
    }

public:
    CSLL() : head(nullptr), tail(nullptr) {}

    // ===========================
    // Insertion Functions
    // ===========================
    void insertAtHead(T val) {
        CSNode<T>* n = new CSNode<T>(val);
        if (!head) {
            head = tail = n;
            n->next = n;
            return;
        }
        n->next = head;
        tail->next = n;
        head = n;
    }

    void insertAtTail(T val) {
        CSNode<T>* n = new CSNode<T>(val);
        if (!head) {
            head = tail = n;
            n->next = n;
            return;
        }
        n->next = head;
        tail->next = n;
        tail = n;
    }

    void insertBefore(T key, T val) {
        if (!head) return;
        if (head->info == key) { insertAtHead(val); return; }
        CSNode<T>* prev = head;
        CSNode<T>* curr = head->next;
        while (curr != head) {
            if (curr->info == key) {
                CSNode<T>* n = new CSNode<T>(val);
                prev->next = n;
                n->next = curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void insertAfter(T key, T val) {
        if (!head) { insertAtHead(val); return; }
        CSNode<T>* curr = head;
        do {
            if (curr->info == key) {
                if (curr == tail) { insertAtTail(val); }
                else {
                    CSNode<T>* n = new CSNode<T>(val);
                    n->next = curr->next;
                    curr->next = n;
                }
                return;
            }
            curr = curr->next;
        } while (curr != head);
    }

    // ===========================
    // Deletion Functions
    // ===========================
    void removeAtHead() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        CSNode<T>* temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
    }

    void removeAtTail() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; return; }
        CSNode<T>* prev = head;
        while (prev->next != tail) prev = prev->next;
        prev->next = head;
        delete tail;
        tail = prev;
    }

    void remove(T val) {
        if (!head) return;
        if (head->info == val) { removeAtHead(); return; }
        CSNode<T>* prev = head;
        CSNode<T>* curr = head->next;
        while (curr != head) {
            if (curr->info == val) {
                if (curr == tail) tail = prev;
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void removeBefore(T val) {
        if (!head || head->info == val) return; // for circular, define 'before head' as no-op
        if (head == tail) return;
        CSNode<T>* prevPrev = head;
        CSNode<T>* prev = head->next;
        CSNode<T>* curr = prev->next;
        // Handle case when second node has val -> remove head
        if (head->next && head->next->info == val) { removeAtHead(); return; }
        while (curr != head) {
            if (curr->info == val) {
                prevPrev->next = curr;
                if (prev == tail) tail = prevPrev;
                delete prev;
                return;
            }
            prevPrev = prev;
            prev = curr;
            curr = curr->next;
        }
    }

    void removeAfter(T val) {
        if (!head) return;
        CSNode<T>* curr = head;
        do {
            if (curr->info == val) {
                CSNode<T>* target = curr->next;
                if (target == head) { // removing head
                    removeAtHead();
                } else if (target == tail) {
                    removeAtTail();
                } else {
                    curr->next = target->next;
                    delete target;
                }
                return;
            }
            curr = curr->next;
        } while (curr != head);
    }

    // ===========================
    // Utility Functions
    // ===========================
    int search(T key) {
        if (!head) return 0;
        CSNode<T>* curr = head;
        do {
            if (curr->info == key) return 1;
            curr = curr->next;
        } while (curr != head);
        return 0;
    }

    void update(T key, T val) {
        if (!head) return;
        CSNode<T>* curr = head;
        do {
            if (curr->info == key) { curr->info = val; return; }
            curr = curr->next;
        } while (curr != head);
    }

    int countNodes() {
        if (!head) return 0;
        int cnt = 0;
        CSNode<T>* curr = head;
        do { ++cnt; curr = curr->next; } while (curr != head);
        return cnt;
    }

    void display() {
        if (!head) { cout << endl; return; }
        CSNode<T>* curr = head;
        do { cout << curr->info << " "; curr = curr->next; } while (curr != head);
        cout << endl;
    }

    void reverse_display() {
        if (!head) { cout << endl; return; }
        reverse_display_from(head, head);
        cout << endl;
    }

    // ===========================
    // Reverse Entire List
    // ===========================
    void reverseList() {
        if (!head || head == tail) return;
        CSNode<T>* prev = nullptr;
        CSNode<T>* curr = head;
        CSNode<T>* stop = head;
        do {
            CSNode<T>* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        } while (curr != stop);
        // prev is new head; old head becomes tail
        tail = head;
        head = prev;
        tail->next = head;
    }

    // ===========================
    // Find Middle Node
    // ===========================
    CSNode<T>* getMiddleNode() {
        if (!head) return nullptr;
        CSNode<T>* slow = head;
        CSNode<T>* fast = head;
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Palindrome Check (uses extra memory for simplicity)
    bool isPalindrome() {
        if (!head || head == tail) return true;
        int n = countNodes();
        T* arr = new T[n];
        int i = 0;
        CSNode<T>* curr = head;
        do { arr[i++] = curr->info; curr = curr->next; } while (curr != head);
        int l = 0, r = n - 1;
        bool ok = true;
        while (l < r) { if (arr[l++] != arr[r--]) { ok = false; break; } }
        delete[] arr;
        return ok;
    }

    // ===========================
    // Remove Duplicates (Sorted)
    // ===========================
    void removeDuplicatesSorted() {
        if (!head) return;
        CSNode<T>* curr = head;
        do {
            while (curr->next != head && curr->info == curr->next->info) {
                CSNode<T>* dup = curr->next;
                if (dup == tail) tail = curr;
                curr->next = dup->next;
                delete dup;
            }
            curr = curr->next;
        } while (curr != head);
    }

    // ===========================
    // Remove Duplicates (Unsorted)
    // ===========================
    void removeDuplicatesUnsorted() {
        if (!head) return;
        CSNode<T>* curr = head;
        do {
            CSNode<T>* runner = curr;
            while (runner->next != head) {
                if (runner->next->info == curr->info) {
                    CSNode<T>* del = runner->next;
                    if (del == tail) tail = runner;
                    runner->next = del->next;
                    delete del;
                } else {
                    runner = runner->next;
                }
            }
            curr = curr->next;
        } while (curr != head);
    }

    // ===========================
    // Merge Two Sorted Lists (Static)
    // ===========================
    static CSLL<T> mergeSortedLists(CSLL<T>& l1, CSLL<T>& l2) {
        CSLL<T> res;
        CSNode<T>* p1 = l1.head;
        CSNode<T>* p2 = l2.head;
        if (p1) p1 = p1; // no-op to clarify intent
        if (p2) p2 = p2;
        int n1 = l1.countNodes();
        int n2 = l2.countNodes();
        for (int i = 0; i < n1; ++i) { res.insertAtTail(p1->info); p1 = p1->next; }
        // We'll rebuild from scratch with a simple merge using arrays-like iteration
        // A proper two-pointer merge across circles directly is verbose; above approach is O(n) insert order
        // Alternative: true two-pointer
        res = CSLL<T>();
        p1 = l1.head; p2 = l2.head;
        if (!p1 && !p2) return res;
        int i1 = 0, i2 = 0;
        while ((p1 && i1 < n1) || (p2 && i2 < n2)) {
            if (p2 == nullptr || i2 >= n2 || (p1 && i1 < n1 && p1->info <= p2->info)) {
                res.insertAtTail(p1->info);
                p1 = p1->next; ++i1;
            } else {
                res.insertAtTail(p2->info);
                p2 = p2->next; ++i2;
            }
        }
        return res;
    }

    // ===========================
    // Extras (parity with other headers)
    // ===========================
    CSLL<T>* reverselist() {
        CSLL<T>* r = new CSLL<T>();
        if (!head) return r;
        CSNode<T>* curr = head;
        do { r->insertAtHead(curr->info); curr = curr->next; } while (curr != head);
        return r;
    }

    void removeKthNode(int k) {
        if (k <= 0 || !head) return;
        if (k == 1) { removeAtHead(); return; }
        int n = countNodes();
        if (k > n) return;
        CSNode<T>* prev = head;
        for (int i = 1; i < k - 1; ++i) prev = prev->next;
        CSNode<T>* target = prev->next;
        if (target == tail) tail = prev;
        prev->next = target->next;
        delete target;
    }

    void removeDuplicates() { removeDuplicatesUnsorted(); }

    void merge(CSLL<T>& other) {
        if (!other.head) return;
        if (!head) { head = other.head; tail = other.tail; other.head = other.tail = nullptr; return; }
        // connect circles: tail->next to other's head, other's tail->next to head
        tail->next = other.head;
        other.tail->next = head;
        tail = other.tail;
        other.head = other.tail = nullptr;
    }

    void swapNodes(T v1, T v2) {
        if (v1 == v2 || !head) return;
        CSNode<T>* n1 = nullptr; CSNode<T>* n2 = nullptr;
        CSNode<T>* curr = head;
        do {
            if (curr->info == v1) n1 = curr;
            if (curr->info == v2) n2 = curr;
            curr = curr->next;
        } while (curr != head && (!n1 || !n2));
        if (!n1 || !n2) return;
        T tmp = n1->info; n1->info = n2->info; n2->info = tmp;
    }

    void sort() {
        if (!head || head == tail) return;
        bool swapped;
        do {
            swapped = false;
            CSNode<T>* curr = head;
            do {
                CSNode<T>* nxt = curr->next;
                if (curr != nxt && curr->info > nxt->info) {
                    T t = curr->info; curr->info = nxt->info; nxt->info = t; swapped = true;
                }
                curr = curr->next;
            } while (curr != head);
        } while (swapped);
    }

    T findMiddle() {
        if (!head) throw std::runtime_error("List is empty");
        CSNode<T>* mid = getMiddleNode();
        return mid->info;
    }

    CSNode<T>* getTail() { return tail; }

    // ===========================
    // Destructor
    // ===========================
    ~CSLL() {
        if (!head) return;
        // break the circle to simplify deletion
        tail->next = nullptr;
        CSNode<T>* curr = head;
        while (curr) {
            CSNode<T>* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = tail = nullptr;
    }
};

#endif
