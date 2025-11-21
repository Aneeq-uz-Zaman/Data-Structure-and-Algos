#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ✅ Insert at Head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // ✅ Insert at Tail
    void insertAtTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!tail) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // ✅ Delete from Head
    void deleteAtHead() {
        if (!head) return;
        Node<T>* temp = head;
        if (head == tail) head = tail = nullptr;
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    // ✅ Delete from Tail
    void deleteAtTail() {
        if (!tail) return;
        Node<T>* temp = tail;
        if (head == tail) head = tail = nullptr;
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    // ✅ Delete by Value
    void deleteValue(T val) {
        if (!head) return;
        Node<T>* temp = head;

        while (temp && temp->data != val)
            temp = temp->next;

        if (!temp) return; // not found

        if (temp == head) deleteAtHead();
        else if (temp == tail) deleteAtTail();
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
    }

    // ✅ Search value
    bool search(T val) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == val)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // ✅ Count nodes
    int countNodes() {
        int count = 0;
        Node<T>* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // ✅ Get Kth Node (1-based)
    Node<T>* getKthNode(int k) {
        if (k <= 0) return nullptr;
        Node<T>* temp = head;
        int count = 1;
        while (temp && count < k) {
            temp = temp->next;
            count++;
        }
        return temp;
    }

    // ✅ Get Middle Node
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

    // ✅ Swap Two Nodes (by their values)
    void swapNodes(T val1, T val2) {
        if (val1 == val2) return;

        Node<T>* node1 = head;
        Node<T>* node2 = head;

        while (node1 && node1->data != val1) node1 = node1->next;
        while (node2 && node2->data != val2) node2 = node2->next;

        if (!node1 || !node2) return; // one not found

        T temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    // ✅ Display Forward
    void displayForward() {
        Node<T>* temp = head;
        cout << "NULL <-> ";
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // ✅ Display Backward
    void displayBackward() {
        Node<T>* temp = tail;
        cout << "NULL <-> ";
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    // ✅ Destructor (Free memory)
    ~DoublyLinkedList() {
        Node<T>* temp = head;
        while (temp) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = nullptr;
    }
};

#endif
