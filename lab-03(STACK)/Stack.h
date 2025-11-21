#pragma once
#include <stdexcept>
#include <iostream>

// Templated Stack class with dynamic array and Big Three

template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIdx;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < topIdx; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    int gettopindex()
    {
        return topIdx;
    }
    // Default constructor
    Stack(int initialCapacity = 8)
        : data(new T[initialCapacity]), capacity(initialCapacity), topIdx(0) {}

    // Destructor
    ~Stack() {
        delete[] data;
    }

    // Copy constructor
    Stack(const Stack& other)
        : data(new T[other.capacity]), capacity(other.capacity), topIdx(other.topIdx) {
        for (int i = 0; i < topIdx; ++i) {
            data[i] = other.data[i];
        }
    }

    // Copy assignment operator
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            topIdx = other.topIdx;
            data = new T[capacity];
            for (int i = 0; i < topIdx; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Push element
    void push(const T& value) {
        if(capacity==topIdx)
        {
            resize(capacity*2);
        }
        data[topIdx] = value;
        topIdx++;
    }

    // Pop element
    T pop() {
        if (topIdx == 0) {
            throw std::out_of_range("Stack underflow");
        }
        topIdx--;
        return data[topIdx];
    }

    // Top element
    T& top() {
        if (topIdx == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[topIdx - 1];
    }

    // Clear stack
    void clear() {
        topIdx = 0;
    }

    // Size
    int size() const {
        return topIdx;
    }

    // Empty check
    bool empty() const {
        return topIdx == 0;
    }
};
