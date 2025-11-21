#include <iostream>
#include "queue.h"
using namespace std;

int main() {
    cout << "=== Testing Queue Resize Functionality ===" << endl;
    
    // Create a small queue
    CircularQueue<int> q(3);
    
    cout << "Initial capacity: " << q.getCapacity() << endl;
    cout << "Is empty: " << q.isEmpty() << endl;
    
    // Fill the queue
    cout << "\nFilling queue to capacity:" << endl;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    cout << "Size: " << q.size() << "/" << q.getCapacity() << endl;
    cout << "Is full: " << q.isFull() << endl;
    
    // Try to add more (will fail with current enqueue)
    cout << "\nTrying to add 40 with regular enqueue:" << endl;
    q.enqueue(40);  // This will show "Queue is full!"
    
    // Manual resize
    cout << "\nManually resizing to capacity 6:" << endl;
    q.resize(6);
    cout << "New capacity: " << q.getCapacity() << endl;
    q.display();
    cout << "Size after resize: " << q.size() << endl;
    
    // Now we can add more elements
    cout << "\nAdding more elements after resize:" << endl;
    q.enqueue(40);
    q.enqueue(50);
    q.display();
    
    // Test auto-resize functionality
    cout << "\n=== Testing Auto-Resize ===" << endl;
    CircularQueue<string> sq(2);
    
    cout << "String queue capacity: " << sq.getCapacity() << endl;
    
    // Fill it up
    sq.enqueueWithResize("First");
    sq.enqueueWithResize("Second");
    sq.display();
    cout << "Queue is now full. Adding more with auto-resize:" << endl;
    
    // This will trigger auto-resize
    sq.enqueueWithResize("Third");
    cout << "New capacity after auto-resize: " << sq.getCapacity() << endl;
    sq.display();
    
    sq.enqueueWithResize("Fourth");
    sq.display();
    
    // Test dequeue after resize
    cout << "\nTesting dequeue after resize:" << endl;
    cout << "Dequeued: " << sq.dequeue() << endl;
    cout << "Dequeued: " << sq.dequeue() << endl;
    sq.display();
    
    // Test resize with smaller capacity (should fail)
    cout << "\n=== Testing Invalid Resize ===" << endl;
    cout << "Current size: " << sq.size() << ", trying to resize to 1:" << endl;
    sq.resize(1);  // Should show error
    
    // Demonstrate wrap-around preservation after resize
    cout << "\n=== Testing Wrap-around Preservation ===" << endl;
    CircularQueue<int> wq(4);
    
    // Fill and create wrap-around situation
    wq.enqueue(1);
    wq.enqueue(2);
    wq.enqueue(3);
    wq.enqueue(4);
    
    cout << "Before dequeue: ";
    wq.display();
    
    // Remove some elements to create space at front
    wq.dequeue();
    wq.dequeue();
    
    // Add new elements (will wrap around)
    wq.enqueue(5);
    wq.enqueue(6);
    
    cout << "After wrap-around: ";
    wq.display();
    
    // Resize and check if order is preserved
    cout << "Resizing to capacity 8:" << endl;
    wq.resize(8);
    cout << "After resize: ";
    wq.display();
    cout << "Order preserved: " << (wq.getFront() == 3 ? "YES" : "NO") << endl;
    
    return 0;
}