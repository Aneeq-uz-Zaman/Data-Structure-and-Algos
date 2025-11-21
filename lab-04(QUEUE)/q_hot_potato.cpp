#include <iostream>
#include "queue.h"
using namespace std;

// Hot Potato / Josephus-like problem with step m
int hotPotato(int n, int m) {
    CircularQueue<int> q(n + 5);
    for (int i = 1; i <= n; i++) q.enqueue(i);

    while (q.size() > 1) {
        // Pass the potato m-1 times
        for (int i = 1; i < m; i++) q.enqueue(q.dequeue());
        // Eliminate m-th person
        q.dequeue();
    }
    return q.dequeue();
}

int main() {
    int n = 7, m = 3;
    cout << "Winner: " << hotPotato(n, m) << endl;
    return 0;
}