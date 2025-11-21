#include <iostream>
using namespace std;

int squares_sum(int n) {
    if (n == 1)
        return 1;
    return n * n + squares_sum(n - 1);
}

int main() {
    int n;
    cin >> n;
    cout << squares_sum(n);
    return 0;
}
