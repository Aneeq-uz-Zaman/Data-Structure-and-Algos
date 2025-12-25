#include <iostream>
#include <vector>
using namespace std;

class Heap
{
private:
    vector<int> heap; // 0-based indexing

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Move value upward
    void heapifyUp(int i)
    {
        while (i != 0 && heap[parent(i)] < heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Move value downward
    void heapifyDown(int i)
    {
        int n = heap.size();
        while (true)
        {
            int l = left(i), r = right(i), largest = i;

            if (l < n && heap[l] > heap[largest])
                largest = l;
            if (r < n && heap[r] > heap[largest])
                largest = r;

            if (largest == i)
                break;

            swap(heap[i], heap[largest]);
            i = largest;
        }
    }

public:
    // Insert value
    void insert(int value)
    {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    // Return maximum element
    int getMax()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty");
        return heap[0];
    }

    // Delete root (max element)
    int deleteMax()
    {
        if (heap.empty())
            throw runtime_error("Heap is empty");

        int maxValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty())
            heapifyDown(0);

        return maxValue;
    }

    // Increase the value at an index
    void increaseKey(int index, int newValue)
    {
        if (index < 0 || index >= heap.size())
            throw runtime_error("Invalid index");

        if (newValue < heap[index])
            throw runtime_error("New value is smaller than current value");

        heap[index] = newValue;
        heapifyUp(index);
    }

    // Decrease the value at an index
    void decreaseKey(int index, int newValue)
    {
        if (index < 0 || index >= heap.size())
            throw runtime_error("Invalid index");

        if (newValue > heap[index])
            throw runtime_error("New value is greater than current value");

        heap[index] = newValue;
        heapifyDown(index);
    }

    // Merge another heap into current heap
    void merge(const Heap &other)
    {
        for (int x : other.heap)
            heap.push_back(x);

        // Rebuild entire heap
        for (int i = heap.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    // Print heap (level order)
    void print()
    {
        cout << "Heap: ";
        for (int x : heap)
            cout << x << " ";
        cout << endl;
    }
};

// Example usage
int main()
{
    Heap h1;
    h1.insert(40);
    h1.insert(20);
    h1.insert(50);
    h1.insert(10);
    cout << "Heap h1: ";
    h1.print();

    cout << "Max deleted: " << h1.deleteMax() << endl;
    h1.print();

    h1.increaseKey(1, 45);
    cout << "After increaseKey: ";
    h1.print();

    h1.decreaseKey(0, 15);
    cout << "After decreaseKey: ";
    h1.print();

    Heap h2;
    h2.insert(60);
    h2.insert(5);

    h1.merge(h2);
    cout << "After merging h2 into h1: ";
    h1.print();

    return 0;
}