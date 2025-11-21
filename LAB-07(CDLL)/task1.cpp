#include <iostream>
#include "CDLL.H"

using namespace std;

int main() {

    CDLL<int> l;
    CDLL<int> l1;
    l.insertAtHead(20);
    l.insertAtHead(10);
    l.insertAtTail(30);
    l.insertAtTail(40);
    CDLL<int> l2;
    l2.insertAtHead(60);
    l2.insertAtHead(50);
    l2.insertAtTail(70);
    l2.insertAtTail(80);
    l.display();
    l2.display();
    l.mergewithsort(l,l2);
    l1.display();

    





    return 0;
}
