#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class StringHashTable {
private:
    static const int TABLE_SIZE = 10;
    list<string> table[TABLE_SIZE];

    int hashFunction(const string &key) {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % TABLE_SIZE;
    }

public:
    // ---------------- Basic Hash Table Operations ----------------
    void insert(const string &key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool search(const string &key) {
        int index = hashFunction(key);
        for (auto &s : table[index])
            if (s == key) return true;
        return false;
    }

    void remove(const string &key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": ";
            for (auto &s : table[i])
                cout << s << " -> ";
            cout << "NULL\n";
        }
    }

    // ---------------- Classic String Problems ----------------

    // 1. Count occurrences of a string
    int countOccurrences(const string &key) {
        int index = hashFunction(key);
        int count = 0;
        for (auto &s : table[index])
            if (s == key) count++;
        return count;
    }

    // 2. Detect if any duplicate exists
    bool hasDuplicate() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            set<string> seen;
            for (auto &s : table[i]) {
                if (seen.count(s)) return true;
                seen.insert(s);
            }
        }
        return false;
    }

    // 3. Find first unique string
    string firstUnique() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto &s : table[i]) {
                if (countOccurrences(s) == 1)
                    return s;
            }
        }
        return "None";
    }

    // 4. Count number of distinct strings
    int countDistinct() {
        set<string> distinct;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                distinct.insert(s);
        return distinct.size();
    }

    // 5. Remove duplicates (keep first occurrence)
    void removeDuplicates() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            set<string> seen;
            list<string> newList;
            for (auto &s : table[i]) {
                if (!seen.count(s)) {
                    newList.push_back(s);
                    seen.insert(s);
                }
            }
            table[i] = newList;
        }
    }

    // 6. Find all duplicate strings
    vector<string> getDuplicates() {
        vector<string> duplicates;
        for (int i = 0; i < TABLE_SIZE; i++) {
            map<string,int> freq;
            for (auto &s : table[i])
                freq[s]++;
            for (auto &p : freq)
                if (p.second > 1)
                    duplicates.push_back(p.first);
        }
        return duplicates;
    }

    // 7. Check if two lists share any common string
    bool hasCommonString(const vector<string> &other) {
        for (auto &s : other)
            if (search(s)) return true;
        return false;
    }

    // 8. Get all strings in sorted order (lexicographically)
    vector<string> getAllStringsSorted() {
        vector<string> allStrings;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                allStrings.push_back(s);
        sort(allStrings.begin(), allStrings.end());
        return allStrings;
    }

    // 9. Count total strings inserted
    int totalStrings() {
        int total = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            total += table[i].size();
        return total;
    }

    // 10. Check if all strings are unique
    bool allUnique() {
        set<string> seen;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i]) {
                if (seen.count(s)) return false;
                seen.insert(s);
            }
        return true;
    }

    // 11. Reverse all strings in the table
    void reverseAllStrings() {
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                reverse(s.begin(), s.end());
    }

    // 12. Count strings that start with a given prefix
    int countPrefix(const string &prefix) {
        int count = 0;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                if (s.substr(0, prefix.size()) == prefix)
                    count++;
        return count;
    }

    // 13. Get strings of specific length
    vector<string> getStringsOfLength(int len) {
        vector<string> result;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                if (s.size() == len)
                    result.push_back(s);
        return result;
    }

    // 14. Concatenate all strings
    string concatenateAll() {
        string result;
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                result += s;
        return result;
    }

    // 15. Find longest string
    string longestString() {
        string longest = "";
        for (int i = 0; i < TABLE_SIZE; i++)
            for (auto &s : table[i])
                if (s.size() > longest.size())
                    longest = s;
        return longest;
    }
};

// -------------------- Example Usage --------------------
int main() {
    StringHashTable ht;

    ht.insert("apple");
    ht.insert("banana");
    ht.insert("apple");
    ht.insert("orange");
    ht.insert("grape");
    ht.insert("kiwi");

    ht.display();

    cout << "\nHas duplicate? " << (ht.hasDuplicate() ? "Yes" : "No") << endl;
    cout << "Occurrences of 'apple': " << ht.countOccurrences("apple") << endl;
    cout << "First unique string: " << ht.firstUnique() << endl;
    cout << "Number of distinct strings: " << ht.countDistinct() << endl;

    vector<string> other = {"mango", "kiwi"};
    cout << "Has common with {mango, kiwi}? " << (ht.hasCommonString(other) ? "Yes" : "No") << endl;

    ht.removeDuplicates();
    cout << "\nAfter removing duplicates:\n";
    ht.display();

    cout << "Total strings: " << ht.totalStrings() << endl;
    cout << "All unique? " << (ht.allUnique() ? "Yes" : "No") << endl;
    cout << "Longest string: " << ht.longestString() << endl;
    cout << "Concatenate all strings: " << ht.concatenateAll() << endl;
    cout << "Strings with prefix 'a': " << ht.countPrefix("a") << endl;

    return 0;
}
