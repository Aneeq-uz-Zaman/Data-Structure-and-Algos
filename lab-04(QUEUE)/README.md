# Circular Queue Implementation

A templated circular queue class with **O(1) dequeue** operations as requested.

## Data Members
- `front`: Index of the front element
- `*data`: Dynamic array to store queue elements  
- `capacity`: Total capacity (including one extra slot for full/empty distinction)
- `rear`: Index where the next element will be inserted

## Key Features
- **O(1) dequeue operation** - Simply moves the front pointer without shifting elements
- **O(1) enqueue operation** - Uses modular arithmetic for wrap-around
- Template-based for any data type
- Exception-safe with proper RAII (destructor cleans up dynamic memory)
- Move semantics support for efficiency

## API Reference

### Constructor
```cpp
CircularQueue<T>(std::size_t capacity)  // Creates queue with given capacity
```

### Core Operations (All O(1))
```cpp
void enqueue(const T& value)     // Add element to rear
void enqueue(T&& value)          // Move version
T dequeue()                      // Remove and return front element (O(1)!)
T& getFront()                    // Access front element without removing
```

### Query Operations (All O(1))
```cpp
bool isEmpty() const             // Check if queue is empty
bool isFull() const              // Check if queue is full  
std::size_t size() const         // Current number of elements
std::size_t getCapacity() const  // Maximum capacity
```

### Safe Variants
```cpp
bool tryEnqueue(const T& value)  // Returns false if full
bool tryDequeue(T& out)          // Returns false if empty
void clear()                     // Reset to empty state
```

## Big-O Complexity
- **Enqueue**: O(1) - Direct insertion at rear index
- **Dequeue**: O(1) - **Constant time as requested** - only moves front pointer
- **getFront**: O(1) - Direct array access  
- **isEmpty/isFull/size**: O(1) - Simple arithmetic on indices

## Build Instructions (Windows cmd)

### Using g++ (MinGW/MSYS2)
```cmd
cd "d:\C++\DSA\lab-04(QUEUE)"
g++ -std=c++11 -Wall -Wextra -O2 src\main.cpp -o build\queue_test.exe
build\queue_test.exe
```

### Using Visual Studio Developer Command Prompt
```cmd
cd "d:\C++\DSA\lab-04(QUEUE)"
cl /EHsc /std:c++11 src\main.cpp /Fe:build\queue_test.exe
build\queue_test.exe
```

### Alternative: Direct compilation without build directory
```cmd
cd "d:\C++\DSA\lab-04(QUEUE)"
g++ -std=c++11 src\main.cpp -o queue_test.exe
queue_test.exe
```

## Usage Example
```cpp
#include "include/CircularQueue.hpp"

CircularQueue<int> q(5);  // Capacity of 5

// Enqueue elements
for(int i = 1; i <= 5; i++) {
    q.enqueue(i);
}

// O(1) dequeue operations
while(!q.isEmpty()) {
    std::cout << q.dequeue() << " ";  // Prints: 1 2 3 4 5
}
```

## Implementation Details
The circular queue uses the "waste one slot" approach:
- Allocates `capacity + 1` elements internally
- `front == rear` means empty
- `(rear + 1) % capacity == front` means full
- **Dequeue is O(1)**: Simply increments front pointer with `front = (front + 1) % capacity`
- No element shifting required, making dequeue constant time as requested

This ensures the **dequeue operation has constant Big-O complexity** while maintaining efficient memory usage and wrap-around behavior.
// Move k to the next person in line