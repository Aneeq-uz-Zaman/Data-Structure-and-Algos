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
public:
    Node<T>* head;


    LSLL() : head(nullptr) {}

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


    void removeAtHead() {
        if (!head) 
            return;
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
    bool removeKthNode(int k,int& value)
    {
        if (k <= 0 || !head)
            return false;
        if (k == 1)
        {
            Node<T>* temp = head;
            value=head->next->info;
            head = nullptr;
            delete temp;
            return true;
        }
        Node<T> *temp = head->next;
        Node<T> *prev = head;
        int count = 2;
        while (temp)
        {
            if(k==count)
            {
                value=prev->next->info;
                prev=temp->next;
                delete temp;
                return true;
            }
            temp = temp->next;
            prev=prev->next;
            count++;
        }
        return false;

    }
    void combine (LSLL& list1, LSLL& list2)
    {
        if (!list1.head) {
            head = list2.head;
            return;
        }
        Node<T>* temp = list1.head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = list2.head;
        head = list1.head;
        list1.head = nullptr;
        list2.head = nullptr;
        
        
    }
    
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
    
    void shufflemerge (LSLL& list1, LSLL& list2)
    {
        Node<T> *temp1 = list1.head;
        Node<T> *temp2 = list2.head;
        Node<T> *temp3 = head;
        if(!(temp1))
        {
            head=list2.head;
            list2.head=nullptr;
            return;
        }
        if(!(temp2))
        {
            head=list1.head;
            list1.head=nullptr;
            return;
        }
        int i=2;
        while(temp1!=nullptr || temp2!=nullptr)
        {
            if(i%2==0)
            {
                temp3->next=temp1->next;
                temp1=temp1->next;
                i++;
                
            }
            if(i%2!=0)
            {
                temp3->next=temp2->next;
                temp2=temp2->next;
                i++;  
            }
        }
        head = list1.head;
        list1.head = nullptr;
        list2.head = nullptr;

    }
    void removeDuplicates() 
    {
        Node<T>* curr = head;
        while (curr) {
            Node<T>* x = curr;
            while (x->next) {
                if (x->next->info == curr->info) {
                    Node<T>* temp = x->next;
                    x->next = x->next->next;
                    delete temp;
                } else {
                    x = x->next;
                }
            }
            curr = curr->next;
        }   

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
};
#endif
