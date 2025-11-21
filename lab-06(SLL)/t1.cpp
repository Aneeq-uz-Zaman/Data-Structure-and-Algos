#include <iostream>
#include "lsll.h"
using namespace std;
int main() {
    LSLL<int> list;

    list.insertAtHead(10);
    list.insertAtHead(20); 
    list.insertAtHead(30);
    list.insertAtHead(40);
    list.insertAtHead(50);
    list.insertAtHead(60);
    list.insertAtHead(70);
    list.insertAtHead(80);
    int value;
    list.display();

    cout<<list.removeKthNode(4,value)<<endl;
    cout<<value;


 
    return 0;
}
