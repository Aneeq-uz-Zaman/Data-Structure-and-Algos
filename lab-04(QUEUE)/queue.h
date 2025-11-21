#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <typename T>
class CircularQueue {
private:
    int front;
    T* data;
    int capacity;
    int rear;
    int count;  

public:
    CircularQueue(int cap) {
        capacity = cap;
        data = new T[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] data;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    int size() {
        return count;
    }

    void enqueue(T value) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }

    void enqueueWithResize(T value) {
        if (isFull()) {
            autoResize();
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }


    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T(); 
        }
        T value = data[front];
        front = (front + 1) % capacity;  
        count--;
        return value;
    }

    T getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return data[front];
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            int index = (front + i) % capacity;
            cout << data[index] << " ";
        }
        cout << endl;
    }

    // Clear the queue
    void clear() {
        front = 0;
        rear = -1;
        count = 0;
    }

    // Resize the queue to new capacity - O(n)
    void resize(int newCapacity) {
        if (newCapacity < count) {
            cout << "Error: New capacity cannot be smaller than current size!" << endl;
            return;
        }
        
        // Create new array with new capacity
        T* newData = new T[newCapacity];
        
        // Copy existing elements to new array in correct order
        for (int i = 0; i < count; i++) {
            int index = (front + i) % capacity;
            newData[i] = data[index];
        }
        
        // Delete old array and update pointers
        delete[] data;
        data = newData;
        capacity = newCapacity;
        front = 0;
        rear = (count > 0) ? count - 1 : -1;
    }

    // Get current capacity
    int getCapacity() {
        return capacity;
    }

    // Auto-resize when queue is full (doubles the capacity)
    void autoResize() {
        int newCapacity = capacity * 2;
        cout << "Auto-resizing from " << capacity << " to " << newCapacity << endl;
        resize(newCapacity);
    }
};

#endif