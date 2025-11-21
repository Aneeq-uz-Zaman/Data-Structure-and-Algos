    // ⚡ Problem: "Unique Digit Number"

    // Write a program that:

    // Takes an integer n as input.

    // Checks if all digits in n are unique (no digit repeats).

    // If unique → print "YES".

    // Otherwise → print "NO".

    // Example 1

    // Input:

    // 1234


    // Output:

    // YES


    // (All digits are different)

    // Example 2

    // Input:

    // 1223


    // Output:

    // NO


    // (Digit 2 repeats)

    // Constraints

    // 1 ≤ n ≤ 10^9
// solve the above problem in C++ language

#include<iostream>
#include<string>
#include<fstream>
#include<cstring>




using namespace std;
bool isUniqueDigits(int n)
{
    bool digits[10] = {false}; // Array to track seen digits

    while (n > 0) {
        int digit = n % 10; // Extract the last digit
        if (digits[digit]) {
            return false; // Digit already seen, not unique
        }
        digits[digit] = true; // Mark this digit as seen
        n /= 10; // Remove the last digit
    }
    return true; // All digits are unique
}