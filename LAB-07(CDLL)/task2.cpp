#include <iostream>
#include "CDLL.H"

using namespace std;

int main() {

    CDLL<int> l;
    CDLL<int> l1;
    CDLL<int> l2;
    l.insertAtHead(20);
    l.insertAtHead(10);
    l.insertAtTail(30);
    l.insertAtTail(40);
    l.display();
    l.splitList(l1,l2);
    


    l1.display();
    l2.display();

    





    return 0;
}
