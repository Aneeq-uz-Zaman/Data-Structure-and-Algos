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
            if (current_tickets == 0) {
                break;
            }
            q.enqueue(current_tickets);
        } else {
            q.enqueue(current_tickets);
        }
    }
    return time;
}

int main()
{
    int t[4]={5,1,1,1};
    int r=timeToBuyTickets(t,4,0);
    cout<<r;
    return 0;

}