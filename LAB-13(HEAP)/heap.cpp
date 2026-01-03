#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Heap
{
private:
    vector<int> h;
    bool isMin;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    bool compare(int a, int b)
    {
        return isMin ? (a < b) : (a > b);
    }

    void heapifyDown(int i)
    {
        int l = left(i);
        int r = right(i);
        int best = i;

        if (l < h.size() && compare(h[l], h[best]))
            best = l;

        if (r < h.size() && compare(h[r], h[best]))
            best = r;

        if (best != i)
        {
            swap(h[i], h[best]);
            heapifyDown(best);
        }
    }

    void heapifyUp(int i)
    {
        while (i != 0 && compare(h[i], h[parent(i)]))
        {
            swap(h[i], h[parent(i)]);
            i = parent(i);
        }
    }

public:
    Heap(bool type = true) { isMin = type; }

    void insert(int key)
    {
        h.push_back(key);
        heapifyUp(h.size() - 1);
    }

    int getRoot()
    {
        if (h.empty())
            return INT_MIN;
        return h[0];
    }

    int extractRoot()
    {
        if (h.empty())
            return INT_MIN;

        int root = h[0];
        h[0] = h.back();
        h.pop_back();
        heapifyDown(0);
        return root;
    }

    void decreaseKey(int i, int newVal)
    {
        h[i] = newVal;
        heapifyUp(i);
    }

    void increaseKey(int i, int newVal)
    {
        h[i] = newVal;
        heapifyUp(i);
    }

    void deleteKey(int i)
    {
        if (isMin)
            decreaseKey(i, INT_MIN);
        else
            increaseKey(i, INT_MAX);

        extractRoot();
    }

    int search(int val)
    {
        for (int i = 0; i < h.size(); i++)
            if (h[i] == val)
                return i;
        return -1;
    }

    void buildHeap(vector<int> arr)
    {
        h = arr;
        for (int i = h.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void convertHeap()
    {
        isMin = !isMin;
        for (int i = h.size() / 2 - 1; i >= 0; i--)
            heapifyDown(i);
    }

    void print()
    {
        cout << "Heap: ";
        for (int x : h)
            cout << x << " ";
        cout << endl;
    }

    vector<int> heapSort()
    {
        vector<int> backup = h;
        vector<int> sorted;

        while (!h.empty())
            sorted.push_back(extractRoot());

        h = backup;
        return sorted;
    }

    int kthElement(int k)
    {
        Heap temp = *this;
        int ans;
        while (k--)
            ans = temp.extractRoot();
        return ans;
    }

    void mergeHeap(Heap &other)
    {
        for (int x : other.h)
            insert(x);
    }

    static bool isHeap(vector<int> &arr, bool isMinHeap)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            if (l < arr.size())
            {
                if (isMinHeap && arr[i] > arr[l])
                    return false;
                if (!isMinHeap && arr[i] < arr[l])
                    return false;
            }
            if (r < arr.size())
            {
                if (isMinHeap && arr[i] > arr[r])
                    return false;
                if (!isMinHeap && arr[i] < arr[r])
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    Heap h(true); // true = Min Heap, false = Max Heap

    h.insert(20);
    h.insert(5);
    h.insert(15);
    h.insert(22);
    h.insert(9);

    h.print();

    cout << "Root: " << h.getRoot() << endl;

    cout << "Extracted Root: " << h.extractRoot() << endl;
    h.print();

    int idx = h.search(15);
    cout << "Search 15 at index: " << idx << endl;

    h.deleteKey(1);
    h.print();

    vector<int> arr = {10, 40, 20, 5, 8, 50};
    h.buildHeap(arr);
    cout << "After buildHeap: ";
    h.print();

    vector<int> sorted = h.heapSort();
    cout << "Heap Sort Result: ";
    for (int x : sorted)
        cout << x << " ";
    cout << endl;

    cout << "3rd smallest: " << h.kthElement(3) << endl;

    return 0;
}
