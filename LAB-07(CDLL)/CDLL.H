#ifndef CDLL_H
#define CDLL_H

#include <iostream>
#include <stdexcept>
using namespace std;

// Circular Doubly Linked List Node
template <class T>
class CDNode {
public:
    T info;
    CDNode<T>* prev;
    CDNode<T>* next;
    CDNode() : info(), prev(nullptr), next(nullptr) {}
    CDNode(T val) : info(val), prev(nullptr), next(nullptr) {}
};

// Circular Doubly Linked List
template <class T>
class CDLL {
private:
    CDNode<T>* head;
    CDNode<T>* tail;

public:
    CDLL() : head(nullptr), tail(nullptr) {}

    // ===========================
    // Insertion Functions
    // ===========================
    void insertAtHead(T val) {
        CDNode<T>* n = new CDNode<T>(val);
        if (!head) {
            head = tail = n;
            n->next = n->prev = n;
            return;
        }
        n->next = head;
        n->prev = tail;
        head->prev = n;
        tail->next = n;
        head = n;
    }

    void insertAtTail(T val) {
        CDNode<T>* n = new CDNode<T>(val);
        if (!head) {
            head = tail = n;
            n->next = n->prev = n;
            return;
        }
        n->prev = tail;
        n->next = head;
        tail->next = n;
        head->prev = n;
        tail = n;
    }

    void insertBefore(T key, T val) {
        if (!head) return;
        if (head->info == key) { insertAtHead(val); return; }
        CDNode<T>* curr = head->next;
        while (curr != head) {
            if (curr->info == key) {
                CDNode<T>* n = new CDNode<T>(val);
                n->prev = curr->prev;
                n->next = curr;
                curr->prev->next = n;
                curr->prev = n;
                return;
            }
            curr = curr->next;
        }
    }

    void insertAfter(T key, T val) {
        if (!head) { insertAtHead(val); return; }
        CDNode<T>* curr = head;
        do {
            if (curr->info == key) {
                if (curr == tail) { insertAtTail(val); }
                else {
                    CDNode<T>* n = new CDNode<T>(val);
                    n->next = curr->next;
                    n->prev = curr;
                    curr->next->prev = n;
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
        if (head == tail) { delete head; head = tail = nullptr; return; }
        CDNode<T>* temp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
    }

    void removeAtTail() {
        if (!head) return;
        if (head == tail) { delete head; head = tail = nullptr; return; }
        CDNode<T>* temp = tail;
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        delete temp;
    }

    void remove(T val) {
        if (!head) return;
        if (head->info == val) { removeAtHead(); return; }
        if (tail->info == val) { removeAtTail(); return; }
        CDNode<T>* curr = head->next;
        while (curr != head) {
            if (curr->info == val) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                delete curr;
                return;
            }
            curr = curr->next;
        }
    }

    void removeBefore(T val) {
        if (!head || head == tail) return;
        if (head->info == val) return; // define 'before head' as no-op
        CDNode<T>* curr = head->next;
        while (curr != head) {
            if (curr->info == val) {
                CDNode<T>* target = curr->prev;
                if (target == head) { removeAtHead(); }
                else if (target == tail) { removeAtTail(); }
                else {
                    target->prev->next = curr;
                    curr->prev = target->prev;
                    delete target;
                }
                return;
            }
            curr = curr->next;
        }
    }

    void removeAfter(T val) {
        if (!head) return;
        CDNode<T>* curr = head;
        do {
            if (curr->info == val) {
                CDNode<T>* target = curr->next;
                if (target == head) { removeAtHead(); }
                else if (target == tail) { removeAtTail(); }
                else {
                    curr->next = target->next;
                    target->next->prev = curr;
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
        CDNode<T>* curr = head;
        do { if (curr->info == key) return 1; curr = curr->next; } while (curr != head);
        return 0;
    }

    void update(T key, T val) {
        if (!head) return;
        CDNode<T>* curr = head;
        do { if (curr->info == key) { curr->info = val; return; } curr = curr->next; } while (curr != head);
    }

    int countNodes() {
        if (!head) return 0;
        int cnt = 0;
        CDNode<T>* curr = head;
        do { ++cnt; curr = curr->next; } while (curr != head);
        return cnt;
    }

    void display() {
        if (!head) { cout << endl; return; }
        CDNode<T>* curr = head;
        do { cout << curr->info << " "; curr = curr->next; } while (curr != head);
        cout << endl;
    }

    void reverse_display() {
        if (!head) { cout << endl; return; }
        CDNode<T>* curr = tail;
        do { cout << curr->info << " "; curr = curr->prev; } while (curr != tail);
        cout << endl;
    }


    void reverseList() {
        if (!head || head == tail) return;
        CDNode<T>* curr = head;
        do {
            CDNode<T>* tmp = curr->next;
            curr->next = curr->prev;
            curr->prev = tmp;
            curr = tmp;
        } while (curr != head);
        CDNode<T>* tmp = head; head = tail; tail = tmp;
    }
    void swapNodes(T v1, T v2) {
        if (v1 == v2 || !head) return;
        CDNode<T>* n1 = nullptr; CDNode<T>* n2 = nullptr;
        CDNode<T>* curr = head;
        do { 
            if (curr->info == v1) 
                n1 = curr; 
            if (curr->info == v2) 
                n2 = curr;
            curr = curr->next;
         } while (curr != head && (!n1 || !n2));
        if (!n1 || !n2) return;
        T t = n1->info; 
        n1->info = n2->info; 
        n2->info = t;
    }

    void sort() {
        if (!head || head == tail) return;
        bool swapped;
        do {
            swapped = false;
            CDNode<T>* curr = head;
            do {
                CDNode<T>* nxt = curr->next;
                if (curr != nxt && curr->info > nxt->info) { T t = curr->info; curr->info = nxt->info; nxt->info = t; swapped = true; }
                curr = curr->next;
            } while (curr != head);
        } while (swapped);
    }

    T findMiddle() {
        if (!head) throw std::runtime_error("List is empty");
        CDNode<T>* mid = getMiddleNode();
        return mid->info;
    }

    CDNode<T>* getTail() { return tail; }
    ~CDLL() {
        if (!head) return;

        tail->next = nullptr;
        CDNode<T>* curr = head;
        while (curr) {
            CDNode<T>* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = tail = nullptr;
    }


    CDNode<T>* getMiddleNode() {
        if (!head) return nullptr;
        CDNode<T>* slow = head;
        CDNode<T>* fast = head;
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }


    void removeKthNode(int k) {
        if (k <= 0 || !head) return;
        if (k == 1) { removeAtHead(); return; }
        int n = countNodes();
        if (k > n) return;
        CDNode<T>* curr = head;
        for (int i = 1; i < k; ++i) curr = curr->next;
        if (curr == head) { removeAtHead(); return; }
        if (curr == tail) { removeAtTail(); return; }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
    }

    void merge(CDLL<T>& other) {
        if (!other.head) return;
        if (!head) { head = other.head; tail = other.tail; other.head = other.tail = nullptr; return; }

        tail->next = other.head;
        other.head->prev = tail;
        other.tail->next = head;
        head->prev = other.tail;
        tail = other.tail;
        other.head = other.tail = nullptr;
    }
//     This function will merge the nodes of the two sorted circular doubly linked lists with dummy 
// header nodes (list1 and list2) to form one sorted list.   
// For example, if list1 contains {4 7 10 12} and list2 contains {1 3 6 8 9 15} and list3 is empty, 
// then after the function call list3.merge(list1,list2), list3 should contain {1 3 4 6 7 8 9 10 
// 12 15} and list1 and list2 should be empty now. 
    void mergewithsort(CDLL<T>& l1,CDLL<T>& l2)
    {
        

    }
    
    void splitList (CDLL& leftHalf, CDLL& rightHalf)
    {
        CDNode<T>* mid = getMiddleNode();
        if (!mid)
            return;
        CDNode<T>* head2 = mid->next;
        mid->next = head;
        head->prev = mid;
        leftHalf.head = head;
        leftHalf.tail = mid;
        rightHalf.head = head2;
        rightHalf.tail = tail;
        mid->next = head;
        head->prev = mid;
        tail->next = head2;
        head2->prev = tail;
        head=nullptr;
        tail=nullptr;
    }
    void combine (CDLL& list1, CDLL& list2)
    {
        if (list1.head==list1.tail) {
            head = list2.head;
            tail = list2.tail;
            head->prev=tail;
            tail->next=head;
            return;
        }
        if (list2.head==list2.tail) {
            head = list1.head;
            tail = list1.tail;
            head->prev=tail;
            tail->next=head;
            return;
        }
        DNode<T>* temp = list1.head;
        
        list1.tail->next = list2.head;
    
        tail = list2.tail;
        tail->next=head;
        head->prev=tail;
        list1.head = nullptr;
        list2.head = nullptr;
        
        
    }

};

#endif
