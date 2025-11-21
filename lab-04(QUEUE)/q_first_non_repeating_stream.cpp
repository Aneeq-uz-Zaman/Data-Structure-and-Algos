#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

// First non-repeating character in a stream
void firstNonRepeating(const string& s) {
    CircularQueue<char> q(2 * s.size() + 5);
    int freq[256] = {0};

    for (char ch : s) {
        freq[(unsigned char)ch]++;
        q.enqueue(ch);
        while (!q.isEmpty() && freq[(unsigned char)q.getFront()] > 1) q.dequeue();
        cout << (q.isEmpty() ? '#': q.getFront());
    }
    cout << endl;
}

int main() {
    string s = "aabc"; // Output: a#bb
    firstNonRepeating(s);
    return 0;
}