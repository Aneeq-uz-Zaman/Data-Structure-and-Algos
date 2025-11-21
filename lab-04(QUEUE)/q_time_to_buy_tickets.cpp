#include <iostream>
#include "queue.h"
using namespace std;

// LeetCode 2073: Time Needed to Buy Tickets
int timeToBuyTickets_fixed(int tickets[], int n, int k) {
    CircularQueue<int> q(n + 5);
    CircularQueue<int> idx(n + 5);

    for (int i = 0; i < n; i++) {
        q.enqueue(tickets[i]);
        idx.enqueue(i);
    }

    int time = 0;
    while (!q.isEmpty()) {
        int t = q.dequeue();
        int i = idx.dequeue();
        if (t > 0) {
            t--; time++;
            if (i == k && t == 0) return time;
            q.enqueue(t);
            idx.enqueue(i);
        }
    }
    return time;
}

int main() {
    int tickets[] = {2, 3, 2};
    int n = 3, k = 2;
    cout << timeToBuyTickets_fixed(tickets, n, k) << endl; // Expected 6
    return 0;
}