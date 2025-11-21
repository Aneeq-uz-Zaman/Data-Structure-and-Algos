#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashTable {
private:
    int size;
    vector<int> tableLP;        // For Linear & Quadratic Probing
    vector<int> tableDB;        // For Double Hashing
    vector<list<int>> chain;    // For Chaining

public:
    HashTable(int s) : size(s) {
        tableLP.assign(size, -1);    // -1 = empty
        tableDB.assign(size, -1);    // -1 = empty
        chain.resize(size);          // list for chaining
    }

    // ======================
    // COMMON HASH FUNCTIONS
    // ======================

    int hash1(int key) {
        return key % size;
    }

    int hash2(int key) {
        return 5 - (key % 5); // For double hashing
    }

    // ======================================================
    // 1) INSERT USING SEPARATE CHAINING
    // ======================================================
    void insertChaining(int key) {
        int index = hash1(key);
        chain[index].push_back(key);
    }

    // SEARCH in chaining
    bool searchChaining(int key) {
        int index = hash1(key);
        for (int x : chain[index]) {
            if (x == key) return true;
        }
        return false;
    }

    // DELETE from chaining
    void deleteChaining(int key) {
        int index = hash1(key);
        chain[index].remove(key);
    }

    // ======================================================
    // 2) INSERT USING LINEAR PROBING
    // ======================================================
    void insertLinear(int key) {
        int index = hash1(key);

        while (tableLP[index] != -1) {
            index = (index + 1) % size;
        }
        tableLP[index] = key;
    }

    // SEARCH using linear probing
    bool searchLinear(int key) {
        int index = hash1(key);
        int start = index;

        while (tableLP[index] != -1) {
            if (tableLP[index] == key) return true;
            index = (index + 1) % size;
            if (index == start) break;
        }
        return false;
    }

    // DELETE using linear probing (lazy delete)
    void deleteLinear(int key) {
        int index = hash1(key);
        int start = index;

        while (tableLP[index] != -1) {
            if (tableLP[index] == key) {
                tableLP[index] = -2;   // -2 = deleted slot
                return;
            }
            index = (index + 1) % size;
            if (index == start) break;
        }
    }

    // ======================================================
    // 3) INSERT USING QUADRATIC PROBING
    // ======================================================
    void insertQuadratic(int key) {
        int index = hash1(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * i) % size;
            if (tableLP[newIndex] == -1) {
                tableLP[newIndex] = key;
                return;
            }
        }
        cout << "Table full (Quadratic)" << endl;
    }

    // SEARCH Quadratic
    bool searchQuadratic(int key) {
        int index = hash1(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * i) % size;
            if (tableLP[newIndex] == key) return true;
            if (tableLP[newIndex] == -1) return false;
        }
        return false;
    }

    // DELETE Quadratic
    void deleteQuadratic(int key) {
        int index = hash1(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * i) % size;
            if (tableLP[newIndex] == key) {
                tableLP[newIndex] = -2; // lazy delete
                return;
            }
            if (tableLP[newIndex] == -1) return;
        }
    }

    // ======================================================
    // 4) INSERT USING DOUBLE HASHING
    // ======================================================
    void insertDouble(int key) {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * step) % size;

            if (tableDB[newIndex] == -1) {
                tableDB[newIndex] = key;
                return;
            }
        }
        cout << "Table full (Double Hashing)" << endl;
    }

    // SEARCH double hashing
    bool searchDouble(int key) {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * step) % size;

            if (tableDB[newIndex] == key) return true;
            if (tableDB[newIndex] == -1) return false;
        }
        return false;
    }

    // DELETE double hashing
    void deleteDouble(int key) {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < size; i++) {
            int newIndex = (index + i * step) % size;

            if (tableDB[newIndex] == key) {
                tableDB[newIndex] = -2;   // lazy delete
                return;
            }
            if (tableDB[newIndex] == -1) return;
        }
    }

    // ======================================================
    // DISPLAY ALL TYPES
    // ======================================================
    void displayChaining() {
        cout << "\n--- Separate Chaining ---\n";
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            for (auto &x : chain[i]) cout << x << " -> ";
            cout << "NULL\n";
        }
    }

    void displayLinearQuadratic() {
        cout << "\n--- Linear / Quadratic Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << i << ": " << tableLP[i] << "\n";
        }
    }

    void displayDouble() {
        cout << "\n--- Double Hashing Table ---\n";
        for (int i = 0; i < size; i++) {
            cout << i << ": " << tableDB[i] << "\n";
        }
    }
};