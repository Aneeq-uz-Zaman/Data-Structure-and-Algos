#include <bits/stdc++.h>
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
    // Basic insert/search/remove
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
            for (auto &s : table[i]) cout << s << " -> ";
            cout << "NULL\n";
        }
    }

    // --- Famous Hash Table Problems ---

    // 1. Valid Anagram
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;
        for (char c : t) {
            if (freq.find(c) == freq.end() || freq[c] == 0) return false;
            freq[c]--;
        }
        return true;
    }

    // 2. Group Anagrams
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (auto s : strs) {
            string temp = s;
            sort(temp.begin(), temp.end());
            mp[temp].push_back(s);
        }
        vector<vector<string>> result;
        for (auto it : mp) result.push_back(it.second);
        return result;
    }

    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int start = 0, maxLen = 0;
        for (int end = 0; end < s.size(); end++) {
            if (mp.find(s[end]) != mp.end()) start = max(mp[s[end]] + 1, start);
            mp[s[end]] = end;
            maxLen = max(maxLen, end - start + 1);
        }
        return maxLen;
    }

    // 4. First Unique Character in a String
    int firstUniqChar(string s) {
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;
        for (int i = 0; i < s.size(); i++)
            if (freq[s[i]] == 1) return i;
        return -1;
    }

    // 5. Word Pattern (string pattern matching)
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> p2s;
        unordered_map<string, char> s2p;
        stringstream ss(s);
        string word;
        vector<string> words;
        while (ss >> word) words.push_back(word);
        if (pattern.size() != words.size()) return false;
        for (int i = 0; i < pattern.size(); i++) {
            char c = pattern[i];
            if (p2s.count(c) && p2s[c] != words[i]) return false;
            if (s2p.count(words[i]) && s2p[words[i]] != c) return false;
            p2s[c] = words[i];
            s2p[words[i]] = c;
        }
        return true;
    }
};

int main() {
    StringHashTable ht;

    ht.insert("apple");
    ht.insert("banana");
    ht.insert("orange");
    ht.display();

    cout << "\nCheck anagram 'listen' & 'silent': " 
         << (ht.isAnagram("listen","silent") ? "Yes" : "No") << endl;

    vector<string> words = {"eat","tea","tan","ate","nat","bat"};
    auto groups = ht.groupAnagrams(words);
    cout << "\nGroup Anagrams:\n";
    for (auto g : groups) {
        for (auto w : g) cout << w << " ";
        cout << endl;
    }

    string s = "abcabcbb";
    cout << "\nLongest substring without repeating: " 
         << ht.lengthOfLongestSubstring(s) << endl;

    string s2 = "leetcode";
    cout << "\nFirst unique character index in 'leetcode': " 
         << ht.firstUniqChar(s2) << endl;

    cout << "\nWord Pattern check 'abba' and 'dog cat cat dog': "
         << (ht.wordPattern("abba","dog cat cat dog") ? "Yes" : "No") << endl;

    return 0;
}
