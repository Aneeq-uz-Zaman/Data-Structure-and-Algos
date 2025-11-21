#include <iostream>
#include "queue.h"
using namespace std;
int timeToBuyTickets(int tickets[], int n, int k) {
    CircularQueue<int> q(n);
    for (int i = 0; i < n; i++) {
        q.enqueue(tickets[i]);
    }

    int time = 0;
    while (true) {
        int current_tickets = q.dequeue();
        if (current_tickets > 0) {
            current_tickets--;
            time++;
            if (k == 0 && current_tickets == 0) {
                break;
            }
            q.enqueue(current_tickets);
        } else {
            q.enqueue(current_tickets);
        }
        // k = ((k-1)%n) + 1; 
        // k=(k%n)-1
        // k=(k-1)%n
        // k=(k+n-1)
        k=(k+n-1)%n;
    }
    return time;
}

int main()
{
    int t[4]={3,5,3,7};
    int r=timeToBuyTickets(t,4,2);
    cout<<r;
    return 0;

}