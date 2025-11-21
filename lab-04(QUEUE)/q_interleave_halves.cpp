#include <iostream>
#include "queue.h"
using namespace std;

// Interleave the first half and second half of the queue
// Example: [1 2 3 4 5 6] -> [1 4 2 5 3 6]
void interleave(CircularQueue<int>& q) {
    int n = q.size();
    if (n <= 1) return;

    int half = n / 2;
    CircularQueue<int> firstHalf(n);

    // Move first half into auxiliary queue
    for (int i = 0; i < half; i++) firstHalf.enqueue(q.dequeue());

    // Interleave by alternately enqueuing from firstHalf and the remaining in q
    for (int i = 0; i < half; i++) {
        q.enqueue(firstHalf.dequeue());
        q.enqueue(q.dequeue());
    }

    // If odd size, one element remains at front, rotate to end
    if (n % 2 == 1) q.enqueue(q.dequeue());
}

int main() {
    CircularQueue<int> q(20);
    for (int i = 1; i <= 6; i++) q.enqueue(i);

    cout << "Original: "; q.display();
    interleave(q);
    cout << "Interleaved: "; q.display();
    return 0;
}