#include <iostream>
using namespace std;

int pow(int number, int power) {
    if (power == 0)
        return 1;
    return number * pow(number, power - 1);
}

int main() {
    int number, power;
    cin >> number >> power;
    cout << pow(number, power);
    return 0;
}
