#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

template <class T>
class Node
{
public:
    T info;
    Node<T> *next;
    Node()
    {
        info = T(); // safer default for any T
        next = nullptr;
    }
    Node(T val)
    {
        info = val;
        next = nullptr; // <-- missing ';' fixed
    }
};

template <class T>
class LSLL
{
private:
    Node<T> *head;

public:
    LSLL()
    {
        head = nullptr; // <-- was using head before init
    }

    // Insertion functions
    void insertAtHead(T val)
    {
        Node<T> *t = new Node<T>(val);
        t->next = head;
        head = t;
    }

    void insertAtTail(T val)
    {
        Node<T> *t = new Node<T>(val);
        if (head == nullptr)
        { // keep structure; handle empty
            head = t;
            return;
        }
        Node<T> *temp = head;
        while (temp->next != nullptr)
        { // loop condition corrected
            temp = temp->next;
        }
        temp->next = t; // <-- was 'temp->= t;'
    }

    void insertBefore(T key, T val)
    {
        if (head == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }

        // If key is found at the head
        if (head->info == key)
        {
            Node<T> *t = new Node<T>(val);
            t->next = head;
            head = t;
            return;
        }

        Node<T> *temp = head;
        Node<T> *prev = nullptr;

        // check every node (including last)
        while (temp != nullptr)
        { // loop condition corrected
            if (temp->info == key)
            {
                Node<T> *t = new Node<T>(val);
                t->next = temp;
                if (prev)
                    prev->next = t;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        // (silent if not found, matching your structure)
    }

    void insertAfter(T key, T val)
    {
        if (head == nullptr)
        {
            head = new Node<T>(val);
            return;
        }

        Node<T> *temp = head;
        while (temp != nullptr)
        { // loop condition corrected
            if (temp->info == key)
            {
                Node<T> *t = new Node<T>(val);
                t->next = temp->next;
                temp->next = t;
                return;
            }
            temp = temp->next;
        }
        cout << "Key not found.\n";
    }

    // Deletion functions
    void removeAtHead()
    {
        if (head == nullptr)
        {
            return;
        }
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    void removeAtTail()
    {
        if (head == nullptr)
        {
            std::cout << "List is empty.\n";
            return;
        }

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        while (temp->next != nullptr)
        { // loop condition corrected
            prev = temp;
            temp = temp->next;
        }
        prev->next = nullptr;
        delete temp;
    }

    void remove(T val)
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->info == val)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        while (temp != nullptr)
        { // loop condition corrected
            if (temp->info == val)
            {
                if (prev)
                    prev->next = temp->next;
                delete temp;
                return;
            }
            prev = temp; // prev must advance
            temp = temp->next;
        }
    }

    void removeBefore(T val)
    {
        if (head == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }
        if (head->info == val)
        {
            cout << "ONLY ONE NODE IN LINK/n";
            return;
        }
        if (head->next && head->next->info == val)
        {
            Node<T> *doomed = head;
            head = head->next;
            delete doomed;
            return;
        }
        if (!head->next)
        { // safety
            cout << "List too short.\n";
            return;
        }

        Node<T> *prev = head;       // node before 'curr'
        Node<T> *curr = head->next; // candidate to remove
        Node<T> *next = curr->next;

        while (next != nullptr)
        { // loop condition corrected
            if (next->info == val)
            {
                prev->next = curr->next;
                delete curr;
                return;
            }
            prev = curr;
            curr = next;
            next = next->next;
        }
        // silent if not found
    }

    void removeAfter(T val)
    {
        if (head == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }

        Node<T> *temp = head;

        while (temp != nullptr)
        { // loop condition ok
            if (temp->info == val)
            {
                if (temp->next == nullptr)
                {
                    cout << "No node exists after the given value.\n";
                    return;
                }
                Node<T> *t = temp->next;
                temp->next = t->next;
                delete t;
                return;
            }
            temp = temp->next;
        }

        cout << "Value not found.\n";
    }

    // Utility functions
    int search(T key)
    {
        Node<T> *temp = head;
        int pos = 1;

        while (temp != nullptr)
        { // loop condition ok
            if (temp->info == key)
            {
                return pos; // found at position 'pos'
            }
            temp = temp->next;
            pos++;
        }
        return -1; // not found
    }

    void update(T key, T val)
    {
        Node<T> *temp = head;

        while (temp != nullptr)
        { // loop condition ok
            if (temp->info == key)
            {
                temp->info = val;
                cout << "Value updated.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Key not found.\n";
    }

    int countNodes()
    {
        Node<T> *temp = head;
        int count = 0;

        while (temp != nullptr)
        { // loop condition ok
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display()
    {
        Node<T> *temp = head;

        if (temp == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }

        while (temp != nullptr)
        { // loop condition ok
            cout << temp->info << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    ~LSLL()
    {
        Node<T> *temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    LSLL<T> *reverselist()
    {
        LSLL<T> *res = new LSLL<T>();
        if (head == nullptr)
        {
            return res;
        }
        Node<T> *temp = head;
        res->insertAtHead(temp->info);
        if (temp->next == nullptr)
        {
            return res;
        }
        Node<T> *prev = head;
        temp = temp->next;
        T v;
        while (temp != nullptr)
        {
            v = prev->info;
            res->insertBefore(v, temp->info);
            prev = temp;
            temp = temp->next;
        }
        return res;
    }
    void removeKthNode(int k)
    {
        if (k <= 0 || !head)
            return;
        if (k == 1)
        {
            removeAtHead();
            return;
        }
        Node<T> *temp = head;
        Node<T> *prev = nullptr;
        int count = 1;
        while (temp && count < k)
        {
            prev = temp;
            temp = temp->next;
            count++;
        }
        if (!temp)
            return;
        prev->next = temp->next;
        delete temp;
    }
    void removeDuplicates()
    {
        Node<T> *temp = head;
        while (temp)
        {
            Node<T> *runner = temp;
            while (runner->next)
            {
                if (runner->next->data == temp->data)
                {
                    Node<T> *del = runner->next;
                    runner->next = del->next;
                    delete del;
                }
                else
                {
                    runner = runner->next;
                }
            }
            temp = temp->next;
        }
    }   
        void merge(LSLL<T> & other)
        {
            if (!head)
            {
                head = other.head;
                other.head = nullptr;
                return;
            }
            Node<T> *tail = getTail();
            tail->next = other.head;
            other.head = nullptr;
        }
    

    void swapNodes(T val1, T val2)
    {
        if (val1 == val2)
            return;

        Node<T> *prev1 = nullptr, *prev2 = nullptr;
        Node<T> *node1 = head, *node2 = head;

        while (node1 && node1->data != val1)
        {
            prev1 = node1;
            node1 = node1->next;
        }
        while (node2 && node2->data != val2)
        {
            prev2 = node2;
            node2 = node2->next;
        }

        if (!node1 || !node2)
            return;

        if (prev1)
            prev1->next = node2;
        else
            head = node2;

        if (prev2)
            prev2->next = node1;
        else
            head = node1;

        swap(node1->next, node2->next);
    }
    void sort() {
        if (!head || !head->next) return;
        for (Node<T>* i = head; i->next; i = i->next) {
            for (Node<T>* j = i->next; j; j = j->next) {
                if (i->data > j->data)
                    swap(i->data, j->data);
            }
        }
    }
    T findMiddle() {
        if (!head) throw runtime_error("List is empty");
        Node<T>* slow = head;
        Node<T>* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->data;
    }
};

int main()
{
    LSLL<int> list; // Create a linked list of integers

    cout << "--- INSERT OPERATIONS ---\n";
    list.insertAtHead(30);
    list.insertAtHead(20);
    list.insertAtHead(10);
    list.display(); // 10 -> 20 -> 30 -> NULL

    cout << "\nInsert After 20:\n";
    list.insertAfter(20, 25);
    list.display(); // 10 -> 20 -> 25 -> 30 -> NULL
    LSLL<int> *reverse = list.reverselist();
    reverse->display();

    return 0;
}
