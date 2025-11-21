#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class HashTable
{
private:
    string *table;
    int S;
    int n;
    

public:
    HashTable(int size)
    {
        S = size;
        n = 0;
        table = new string[S];
        for (int i = 0; i < S; i++)
            table[i] = "";
    }
    ~HashTable()
    {
        delete[] table;
    }

    bool isEmpty() { return n == 0; }
    bool isFull() { return n == S; }

    double loadFactor() { return double(n) / S; }

    int getHashValue(string name)
    {
        int sum = 0;
        for (char c : name)
            sum += int(c);
        return sum % S;
    }

    bool insert(string name)
    {
        if (isFull())
        {
            cout << "Hash Table is FULL!\n";
            return false;
        }

        int index = getHashValue(name);
        int start = index;

        cout << "Traversed indices: ";

        while (true)
        {
            cout << index << " ";

            if (table[index] == "" || table[index] == "#")
            {
                table[index] = name;
                n++;
                cout << "\nInserted at index " << index << endl;
                return true;
            }
            index = (index + 1) % S;

            if (index == start)
            {
                cout << "\nNo empty slot found!\n";
                return false;
            }
        }
    }

    bool search(string name)
    {
        int index = getHashValue(name);
        int start = index;

        cout << "Traversed indices: ";

        while (true)
        {
            cout << index << " ";

            if (table[index] == name)
            {
                cout << "\nFound at index " << index << endl;
                return true;
            }
            if (table[index] == "")
                break;

            index = (index + 1) % S;
            if (index == start)
                break;
        }

        cout << "\nNot found.\n";
        return false;
    }

    bool remove(string name)
    {
        int index = getHashValue(name);
        int start = index;

        while (true)
        {
            if (table[index] == name)
            {
                table[index] = "#"; 
                n--;
                cout << "Removed from index " << index << endl;
                return true;
            }
            if (table[index] == "")
                break;

            index = (index + 1) % S;
            if (index == start)
                break;
        }

        cout << "Name not found.\n";
        return false;
    }

    void display()
    {
        cout << "\nIndex\tValue\n";
        cout << "-----------------------\n";
        for (int i = 0; i < S; i++)
        {
            if (table[i] == "")
                cout << i << "\tEMPTY\n";
            else if (table[i] == "#")
                cout << i << "\tDELETED\n";
            else
                cout << i << "\t" << table[i] << endl;
        }
        cout << endl;
    }
};
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

    int size;
    cout << "Enter the size of Hash Table: ";
    cin >> size;

    HashTable ht(size);

    int choice;
    string name;

    while (true) {
        cout << "\n1. Insert a name\n";
        cout << "2. Search for a name\n";
        cout << "3. Remove a name\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Display Load Factor\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice==1){

        
            cout << "Enter name to insert: ";
            cin >> name;
            ht.insert(name);
            
        }
        else if(choice==2){

        
            cout << "Enter name to search: ";
            cin >> name;
            ht.search(name);
           
        }
        else if(choice==3){        
            cout << "Enter name to remove: ";
            cin >> name;
            ht.remove(name);
        }
        else if(choice==4)
            ht.display();
        else if(choice==5)
            cout << "Load Factor = " << ht.loadFactor() << endl;
        else if(choice==6)
            return 0;
        else
            cout << "Invalid choice!\n";
        
    }
   

}