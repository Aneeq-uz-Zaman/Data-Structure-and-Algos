#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Student {
public:
    double cgpa;
    int rollNo;

    Student() {
        cgpa = 0.0;
        rollNo = 0;
    }

    Student(int r, double c) {
        rollNo = r;
        cgpa = c;
    }
};

class StudentMaxHeap {
private:
    Student* st;
    int currSize;
    int maxSize;


    bool isGreater(const Student& a, const Student& b) {
        if (a.cgpa > b.cgpa) return true;
        if (a.cgpa < b.cgpa) return false;
        return a.rollNo < b.rollNo; // tie break
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (isGreater(st[index], st[parent])) {
                swap(st[index], st[parent]);
                index = parent;
            } else break;
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < currSize && isGreater(st[left], st[largest]))
                largest = left;

            if (right < currSize && isGreater(st[right], st[largest]))
                largest = right;

            if (largest != index) {
                swap(st[index], st[largest]);
                index = largest;
            } else break;
        }
    }

public:
    StudentMaxHeap(int size) {
        maxSize = size;
        currSize = 0;
        st = new Student[maxSize];
    }

    ~StudentMaxHeap() {
        delete[] st;
    }

    bool isEmpty() {
        return currSize == 0;
    }

    bool isFull() {
        return currSize == maxSize;
    }

    // --- Task 1.1 Insert function ---
    bool insert(int rollNo, double cgpa) {
        if (isFull()) return false;

        st[currSize] = Student(rollNo, cgpa);
        heapifyUp(currSize);
        currSize++;
        return true;
    }

    // --- Task 1.2 Remove max student ---
    bool removeBestStudent(int& rollNo, double& cgpa) {
        if (isEmpty()) return false;

        rollNo = st[0].rollNo;
        cgpa = st[0].cgpa;

        st[0] = st[currSize - 1];
        currSize--;

        heapifyDown(0);

        return true;
    }

    // --- Task 1.3 Level Order ---
    void levelOrder() {
        for (int i = 0; i < currSize; i++) {
            cout << "(" << st[i].rollNo << ", " << st[i].cgpa << ") ";
        }
        cout << endl;
    }

    // Height of complete binary tree
    int height() {
        if (currSize == 0) return 0;
        return (int)floor(log2(currSize)) + 1;
    }
};

// ---------------- DRIVER ----------------
int main() {
    StudentMaxHeap heap(20);

    heap.insert(10, 3.2);
    heap.insert(5, 3.9);
    heap.insert(12, 3.5);
    heap.insert(3, 3.9);
    heap.insert(7, 2.8);
    heap.insert(18, 3.7);
    heap.insert(1, 4.0);
    heap.insert(20, 3.4);
    heap.insert(11, 3.7);
    heap.insert(4, 3.8);

    cout << "===== Level Order After Insertions =====\n";
    heap.levelOrder();

    cout << "\nHeight of the heap: " << heap.height() << endl;

    int roll;
    double cg;

    if (heap.removeBestStudent(roll, cg))
        cout << "Removed Student - Roll No: " << roll << ", CGPA: " << cg << endl;

    if (heap.removeBestStudent(roll, cg))
        cout << "Removed Student - Roll No: " << roll << ", CGPA: " << cg << endl;

    cout << "\n===== Level Order After Two Removals =====\n";
    heap.levelOrder();

    cout << "\nHeight of the heap: " << heap.height() << endl;
}