#include <iostream>
using namespace std;

bool isprime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
bool iseven(int n)
{
    return (n % 2 == 0);
}
bool isGoodNumber(const string &digits, int base)
{
    int temp;
    bool r = true;
    if(base==digits.size())
        return true;
    else
    {
        temp = digits[base] - '0';
        if(base%2==0)
        {
            if(!iseven(temp))
                return false;
        }
        else
        {
            if(!isprime(temp))
                return false;
        }
        r = isGoodNumber(digits, base + 1);
    }
    return r;
}

int main()
{
    string digit_strings[] = {"02468", "23478", "224365"};
    for (string digits : digit_strings)
    {
        bool is_good = isGoodNumber(digits, 0);
        cout << "Digit string: " << digits<< " is " << (is_good ? "good" : "not good") << endl;
    }
    return 0;

}