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
    list2.insertAtHead(50);
    list2.insertAtHead(60);
    list2.insertAtHead(70);
    list2.insertAtHead(80);
    list1.display();
    cout<<endl;
    list2.display();

    list3.combine(list1,list2);
    list3.display();


 
    return 0;
}
