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
    // Insertion functions
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
        while (temp->next)
            temp = temp->next;
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
    // Deletion functions
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
    // Utility functions
    int search(T key) {
        Node<T>* curr = head;
        int pos = 0;
        while (curr) {
            if (curr->info == key) return 1;
            curr = curr->next;
            pos++;
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
    }
    void reverse_display_helper(Node<T>* curr) {
        if (!curr) return;
        reverse_display_helper(curr->next);
        cout << curr->info << " ";
    }
    ~LSLL() {
        while (head) removeAtHead();
    }
};

int main() {
    LSLL<int> list;
    // Sample testing (You can add more)
    list.insertAtHead(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAfter(20, 25);
    list.insertBefore(10, 5);
    list.reverse_display();
    list.remove(25);
    list.removeAtHead();
    list.removeAtTail();
    cout << "\nAfter deletions: ";
    list.display();
    list.update(20, 99);
    cout << "\nAfter update: ";
    list.display();
    if (list.search(99))
        cout << "\nElement 99 found!";
    else
        cout << "\nElement 99 not found!";
    cout << "\nTotal Nodes: " << list.countNodes();
    return 0;
}
