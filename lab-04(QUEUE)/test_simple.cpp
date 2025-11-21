#include <iostream>
#include "simple_queue.h"
using namespace std;

int main() {
    cout << "=== Testing Simple Queue (Non-Constant Dequeue) ===" << endl;
    
    SimpleQueue<int> sq(6);
    
    cout << "Is empty: " << sq.isEmpty() << endl;
    cout << "Capacity: " << sq.getCapacity() << endl;
    
    // Test enqueue
    cout << "\nEnqueuing 10, 20, 30, 40:" << endl;
    sq.enqueue(10);
    sq.enqueue(20);
    sq.enqueue(30);
    sq.enqueue(40);
    
    sq.display();
    cout << "Size: " << sq.getSize() << endl;
    cout << "Front: " << sq.front() << endl;
    cout << "Rear: " << sq.rear() << endl;
    
    // Test dequeue - O(n) operations (shifts all elements)
    cout << "\nTesting O(n) dequeue operations:" << endl;
    cout << "Before dequeue: ";
    sq.display();
    
    cout << "Dequeued: " << sq.dequeue() << endl;
    cout << "After 1st dequeue (notice all elements shifted): ";
    sq.display();
    
    cout << "Dequeued: " << sq.dequeue() << endl;
    cout << "After 2nd dequeue (again, all elements shifted): ";
    sq.display();
    
    cout << "Size now: " << sq.getSize() << endl;
    
    // Add more elements
    cout << "\nAdding 50 and 60:" << endl;
    sq.enqueue(50);
    sq.enqueue(60);
    sq.display();
    
    // Demonstrate the shifting behavior clearly
    cout << "\n=== Demonstrating O(n) Shifting Behavior ===" << endl;
    SimpleQueue<string> strQueue(4);
    
    strQueue.enqueue("First");
    strQueue.enqueue("Second");  
    strQueue.enqueue("Third");
    strQueue.enqueue("Fourth");
    
    cout << "Initial queue: ";
    strQueue.display();
    
    cout << "\nRemoving 'First' - all elements will shift left:" << endl;
    cout << "Removed: " << strQueue.dequeue() << endl;
    cout << "After removal: ";
    strQueue.display();
    
    cout << "\nRemoving 'Second' - remaining elements shift again:" << endl;
    cout << "Removed: " << strQueue.dequeue() << endl;
    cout << "After removal: ";
    strQueue.display();
    
    // Show the difference with circular queue
    cout << "\n=== Comparison Summary ===" << endl;
    cout << "Simple Queue:" << endl;
    cout << "- Enqueue: O(1) - add at end" << endl;
    cout << "- Dequeue: O(n) - remove from front + shift all elements" << endl;
    cout << "- Memory: Contiguous, no wrap-around" << endl;
    cout << "\nCircular Queue:" << endl;
    cout << "- Enqueue: O(1) - add at rear pointer" << endl;
    cout << "- Dequeue: O(1) - just move front pointer" << endl;
    cout << "- Memory: Wrap-around with pointers" << endl;
    
    return 0;
}