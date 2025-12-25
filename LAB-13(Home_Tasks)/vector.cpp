#include <iostream>
#include <vector>
using namespace std;

int main() {

    // Create vector
    vector<int> v;

    // push_back()
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    cout << "Initial vector: ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // size() and capacity()
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;

    // Access elements
    cout << "v[2] = " << v[2] << endl;
    cout << "at(1) = " << v.at(1) << endl;
    cout << "Front = " << v.front() << endl;
    cout << "Back = " << v.back() << endl;

    // insert() at index 1
    v.insert(v.begin() + 1, 99);

    cout << "After insert: ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // erase() element at index 2
    v.erase(v.begin() + 2);

    cout << "After erase index 2: ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // erase() range [1, 2)
    if(v.size() >= 3) {
        v.erase(v.begin() + 1, v.begin() + 3);
    }

    cout << "After erase range [1,3): ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // pop_back()
    v.pop_back();

    cout << "After pop_back: ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // resize()
    v.resize(5);

    cout << "After resize(5): ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // empty()
    if(v.empty())
        cout << "Vector is empty\n";
    else
        cout << "Vector is NOT empty\n";

    // clear()
    v.clear();
    cout << "After clear(), size = " << v.size() << endl;

    // swap()
    vector<int> a = {1, 2, 3};
    vector<int> b = {7, 8, 9};

    cout << "Before swap: \nA: ";
    for(int x : a) cout << x << " ";
    cout << "\nB: ";
    for(int x : b) cout << x << " ";
    cout << endl;

    a.swap(b);

    cout << "After swap: \nA: ";
    for(int x : a) cout << x << " ";
    cout << "\nB: ";
    for(int x : b) cout << x << " ";
    cout << endl;

    return 0;
}
