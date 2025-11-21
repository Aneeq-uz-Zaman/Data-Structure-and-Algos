#include <iostream>
using namespace std;


int countWays(int numStairs) {
    int r;
    if (numStairs == 0)
        return 1;  
    if (numStairs == 1)
        return 1;
    r = countWays(numStairs - 1) + countWays(numStairs - 2);
    return r;
}


int main() {
    int n;

    cout << "Enter number of stairs: ";
    cin >> n;

    cout << "Number of ways to climb " << n << " stairs is: " << countWays(n) << endl;

    return 0;
}
