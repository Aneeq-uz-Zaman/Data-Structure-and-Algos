#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class SimpleQueue {
private:
    T* data;
    int capacity;
    int size;

public:
    // Constructor
    SimpleQueue(int cap) {
        capacity = cap;
        data = new T[capacity];
        size = 0;
    }

    // Destructor
    ~SimpleQueue() {
        delete[] data;
    }

    // Check if queue is empty
    bool isEmpty() {
        return size == 0;
    }

    // Check if queue is full
    bool isFull() {
        return size == capacity;
    }

    // Get current size
    int getSize() {
        return size;
    }

    // Get capacity
    int getCapacity() {
        return capacity;
    }

    // Enqueue operation - O(1)
    // Add element at the end
    void enqueue(T value) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        data[size] = value;
        size++;
    }

    // Dequeue operation - O(n) - NOT constant time
    // Remove front element and shift all remaining elements left
    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        
        T frontValue = data[0];  // Get front element
        
        // Shift all elements one position to the left - O(n) operation
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        
        size--;
        return frontValue;
    }

    // Get front element without removing
    T front() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return data[0];
    }

    // Get rear element
    T rear() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return data[size - 1];
    }

    // Display queue contents
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Clear the queue
    void clear() {
        size = 0;
    }
};

#endif