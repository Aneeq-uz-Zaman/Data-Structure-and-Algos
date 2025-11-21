#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashTable {
private:
    int size;  
    vector<list<int>> table;  

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int s) : size(s) {
        table.resize(size);
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool searchKey(int key) {
        int index = hashFunction(key);
        for (int x : table[index]) {
            if (x == key) return true;
        }
        return false;
    }


    void removeKey(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            for (int x : table[i]) cout << x << " -> ";
            cout << "NULL\n";
        }
    }
};