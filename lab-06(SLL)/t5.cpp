#include <iostream>
#include "lsll.h"
using namespace std;
int main() {
    LSLL<int> list1;
    LSLL<int> list2;
    LSLL<int> list3;

    list1.insertAtHead(10);
    list1.insertAtHead(20); 
    list1.insertAtHead(30);
    list1.insertAtHead(40);
    list1.insertAtHead(10);
    list1.insertAtHead(20);
    list1.insertAtHead(70);
    list1.insertAtHead(80);
    list1.display();
    // cout<<endl;
    // list2.display();

    list1.removeDuplicates();
    list1.display();


 
    return 0;
}
