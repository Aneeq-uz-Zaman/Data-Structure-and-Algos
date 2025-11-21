#include <iostream>
using namespace std;

void printStars(int n) {
    if (n == 0)
        return;
    cout << "*";
    printStars(n - 1);
}

void printPattern(int rows) {
    if (rows == 0)
        return;
    printStars(rows);
    cout << endl;
    printPattern(rows - 1);
}

int main() {
    int n;
    cin >> n;
    printPattern(n);
    return 0;
}
