#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

// Generate binary numbers from 1 to n using a queue
void generateBinary(int n) {
    CircularQueue<string> q(2 * n + 5);
    q.enqueue("1");

    for (int i = 1; i <= n; i++) {
        string s = q.dequeue();
        cout << s << (i == n ? "\n" : " ");
        q.enqueue(s + "0");
        q.enqueue(s + "1");
    }
}

int main() {
    int n = 10;
    cout << "Binary numbers 1.." << n << ": ";
    generateBinary(n);
    return 0;
}