#include <iostream>
using namespace std;

int binomial(int n, int m) {
    if (n == m || m == 0)
        return 1;
    return binomial(n - 1, m) + binomial(n - 1, m - 1);
}

int main() {
    cout << binomial(7, 5);
    return 0;
}
