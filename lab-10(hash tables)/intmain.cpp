#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

class HashTable
{
private:
    int *table;
    int S;
    int n;

public:
    HashTable(int size)
    {
        S = size;
        n = 0;
        table = new int[S];
        for (int i = 0; i < S; i++)
            table[i] = -1;
    }
    ~HashTable()
    {
        delete[] table;
    }

    bool isEmpty() { return n == 0; }
    bool isFull() { return n == S; }

    double loadFactor() { return double(n) / S; }

    int getHashValue(int x)
    {
        return x % S;
    }

    void display()
    {
        cout << "\nIndex\tValue\n";
        cout << "-----------------------\n";
        for (int i = 0; i < S; i++)
        {
            if (table[i] == -1)
                cout << i << "\tEMPTY\n";
            else if (table[i] == -2)
                cout << i << "\tDELETED\n";
            else
                cout << i << "\t" << table[i] << endl;
        }
        cout << endl;
    }
    bool insert(int x)
    {
        if (isFull())
        {
            cout << "Hash Table is FULL!\n";
            return false;
        }

        int index = getHashValue(x);
        

        if (table[index] == -1 || table[index] == -2)
            {
                table[index] = x;
                n++;
                return true;
            }
        
        return false;
        
    }
};
int getRandomNumber(int start, int end)
    {
        return rand() % (end - start + 1) + start;
    }
int experiment(int tableSize)
    {
        HashTable ht(tableSize);
        int count = 0;
        bool check=ht.insert(getRandomNumber(1,100));
        while(check)
        {
            check=ht.insert(getRandomNumber(1,100));
            count++;
        }
        return count;
}
int main()
{
    // HashTable t(10);
    // t.insert("a");
    // t.insert("quick");
    // t.insert("brown");
    // t.insert("fox");
    // t.insert("jump");
    // t.insert("over");
    // t.insert("the");
    // t.insert("lazy");
    // t.insert("dog");
    // t.insert("o");
    // t.insert("gg");
    // t.insert("rr");
    // t.display();

    srand(static_cast<unsigned>(time(0))); // seed random generator
    const int numExperiments = 50;
    cout << "Table Size\tAverage Inserted\n";
    cout << "-----------\t----------------\n";
    // Run experiments for table sizes 10, 20, 30, ..., 100
    for (int S = 10; S <= 100; S += 10)
    {
        double totalInserted = 0.0;
        for (int i = 0; i < numExperiments; i++)
            totalInserted += experiment(S);
        double averageInserted = totalInserted / numExperiments;
        cout << setw(5) << S << "\t\t" << fixed << setprecision(2) << averageInserted << endl;
    }
}