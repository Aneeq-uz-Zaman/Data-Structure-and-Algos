#include <iostream>
#include "queue.h"
#include "Stack.h"
using namespace std;

// Reverse first k elements of a queue using auxiliary stack
void reverseFirstK(CircularQueue<int>& q, int k) {
    if (k <= 0 || q.isEmpty()) return;
    if (k > q.size()) k = q.size();

    Stack<int> st(k);
    int n = q.size();

    // Dequeue first k elements into stack
    for (int i = 0; i < k; i++) st.push(q.dequeue());

    // Enqueue back from stack (reversed order)
    while (!st.empty()) q.enqueue(st.pop());

    // Move the remaining n-k items to back to preserve order
    for (int i = 0; i < n - k; i++) q.enqueue(q.dequeue());
}

int main() {
    CircularQueue<int> q(20);
    for (int i = 1; i <= 8; i++) q.enqueue(i);
    cout << "Original: "; q.display();

    int k = 5;
    reverseFirstK(q, k);

    cout << "After reversing first " << k << ": "; q.display();
    return 0;
}