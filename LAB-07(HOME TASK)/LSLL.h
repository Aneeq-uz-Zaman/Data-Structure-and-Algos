#ifndef LSLL_H
#define LSLL_H

#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T info;
    Node<T>* next;
    Node() : info(), next(nullptr) {}
    Node(T val) : info(val), next(nullptr) {}
};

template <class T>
class LSLL {
private:
    Node<T>* head;

public:
    LSLL() : head(nullptr) {}

    // ===========================
    // Insertion Functions
    // ===========================
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void insertBefore(T key, T val) {
        if (!head) return;
        if (head->info == key) {
            insertAtHead(val);
            return;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr && curr->info != key) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            Node<T>* newNode = new Node<T>(val);
            prev->next = newNode;
            newNode->next = curr;
        }
    }

    void insertAfter(T key, T val) {
        Node<T>* curr = head;
        while (curr && curr->info != key) curr = curr->next;
        if (curr) {
            Node<T>* newNode = new Node<T>(val);
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }

    // ===========================
    // Deletion Functions
    // ===========================
    void removeAtHead() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    void removeAtTail() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr->next) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nullptr;
        delete curr;
    }

    void remove(T val) {
        if (!head) return;
        if (head->info == val) {
            removeAtHead();
            return;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr && curr->info != val) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            prev->next = curr->next;
            delete curr;
        }
    }

    void removeBefore(T val) {
        if (!head || head->info == val) return;
        Node<T>* prevPrev = nullptr;
        Node<T>* prev = head;
        Node<T>* curr = head->next;
        while (curr && curr->info != val) {
            prevPrev = prev;
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            if (!prevPrev) {
                removeAtHead();
            } else {
                prevPrev->next = curr;
                delete prev;
            }
        }
    }

    void removeAfter(T val) {
        Node<T>* curr = head;
        while (curr && curr->info != val) curr = curr->next;
        if (curr && curr->next) {
            Node<T>* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
    }

    // ===========================
    // Utility Functions
    // ===========================
    int search(T key) {
        Node<T>* curr = head;
        while (curr) {
            if (curr->info == key) return 1;
            curr = curr->next;
        }
        return 0;
    }

    void update(T key, T val) {
        Node<T>* curr = head;
        while (curr) {
            if (curr->info == key) {
                curr->info = val;
                return;
            }
            curr = curr->next;
        }
    }

    int countNodes() {
        int count = 0;
        Node<T>* curr = head;
        while (curr) {
            count++;
            curr = curr->next;
        }
        return count;
    }

    void display() {
        Node<T>* curr = head;
        while (curr) {
            cout << curr->info << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void reverse_display() {
        reverse_display_helper(head);
        cout << endl;
    }

    void reverse_display_helper(Node<T>* curr) {
        if (!curr) return;
        reverse_display_helper(curr->next);
        cout << curr->info << " ";
    }

    // ===========================
    // Reverse Entire List
    // ===========================
    void reverseList() {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    // ===========================
    // Find Middle Node
    // ===========================
    Node<T>* getMiddleNode() {
        if (!head) return nullptr;
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // ===========================
    // Reverse from given node (helper)
    // ===========================
    Node<T>* reverseFrom(Node<T>* start) {
        Node<T>* prev = nullptr;
        Node<T>* curr = start;
        Node<T>* next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    // ===========================
    // Palindrome Check
    // ===========================
    bool isPalindrome() {
        if (!head || !head->next) return true;

        Node<T>* mid = getMiddleNode();
        Node<T>* secondHalf = reverseFrom(mid->next);

        Node<T>* firstHalf = head;
        Node<T>* tempSecond = secondHalf;
        bool palindrome = true;

        while (tempSecond) {
            if (firstHalf->info != tempSecond->info) {
                palindrome = false;
                break;
            }
            firstHalf = firstHalf->next;
            tempSecond = tempSecond->next;
        }

        mid->next = reverseFrom(secondHalf); // restore
        return palindrome;
    }

    // ===========================
    // Remove Duplicates (Sorted)
    // ===========================
    void removeDuplicatesSorted() {
        if (!head) return;
        Node<T>* curr = head;
        while (curr && curr->next) {
            if (curr->info == curr->next->info) {
                Node<T>* temp = curr->next;
                curr->next = temp->next;
                delete temp;
            } else {
                curr = curr->next;
            }
        }
    }

    // ===========================
    // Remove Duplicates (Unsorted)
    // ===========================
    void removeDuplicatesUnsorted() {
        if (!head) return;
        Node<T>* curr = head;
        while (curr) {
            Node<T>* runner = curr;
            while (runner->next) {
                if (runner->next->info == curr->info) {
                    Node<T>* temp = runner->next;
                    runner->next = temp->next;
                    delete temp;
                } else {
                    runner = runner->next;
                }
            }
            curr = curr->next;
        }
    }

    // ===========================
    // Merge Two Sorted Lists (Static)
    // ===========================
    static LSLL<T> mergeSortedLists(LSLL<T>& l1, LSLL<T>& l2) {
        LSLL<T> result;
        Node<T>* dummy = new Node<T>();
        Node<T>* tail = dummy;

        Node<T>* p1 = l1.head;
        Node<T>* p2 = l2.head;

        while (p1 && p2) {
            if (p1->info <= p2->info) {
                tail->next = new Node<T>(p1->info);
                p1 = p1->next;
            } else {
                tail->next = new Node<T>(p2->info);
                p2 = p2->next;
            }
            tail = tail->next;
        }

        while (p1) {
            tail->next = new Node<T>(p1->info);
            tail = tail->next;
            p1 = p1->next;
        }

        while (p2) {
            tail->next = new Node<T>(p2->info);
            tail = tail->next;
            p2 = p2->next;
        }

        result.head = dummy->next;
        delete dummy;
        return result;
    }

    // ===========================
    // Destructor
    // ===========================
    ~LSLL() {
        while (head) removeAtHead();
    }
};

#endif
