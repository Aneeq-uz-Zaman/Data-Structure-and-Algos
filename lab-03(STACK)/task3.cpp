#include <iostream>
#include "Stack.h"   // your custom stack class
#include <string>
using namespace std;

bool isValid(const string &expr)
{
    Stack<char> st;

    for (char ch : expr)
    {
        if (ch == '(' || ch == '{' || ch == '[')
        {
            st.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            // check before using top()
            if (st.empty())
                return false;

            char top = st.top();
            if ((ch == ')' && top == '(') ||
                (ch == '}' && top == '{') ||
                (ch == ']' && top == '['))
            {
                st.pop();
            }
            else
            {
                return false;
            }
        }
    }

    // all opening brackets must be matched
    return st.empty();
}

int main()
{
    string expr = "5*{3+(1-2";
    bool r = isValid(expr);

    if (r)
        cout << "Valid Expression\n";
    else
        cout << "Invalid Expression\n";

    return 0;
}
