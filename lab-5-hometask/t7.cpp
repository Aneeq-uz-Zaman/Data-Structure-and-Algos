#include <iostream>
using namespace std;

void printBitStrings(int n, string prefix) {
    if (n == 0) {
        cout << prefix << endl;
        return;
    }
    printBitStrings(n - 1, prefix + "0");
    printBitStrings(n - 1, prefix + "1");
}

int main() {
    int n;
    cin >> n;
    printBitStrings(n, "");
    return 0;
}
