#include <iostream>
#include "Stack.h"
using namespace std;

string reversewords(const string &str)
{
    Stack<char> s(100);
    string result="";
    for(int i=0;i<str.length();i++)
    {
        if(str[i]!=' ')
        {
            s.push(str[i]);
        }
        else
        {
            while(!s.empty())
            {
                result+=s.pop();
            }
            result+=' ';
        }
    }
    while(!s.empty())
    {
        result+=s.pop();
    }
    return result;
}


int main()
{
    string a="welcome to dtasceince aneeq     ";
    a=reversewords(a);
    cout<<a;
    return 0;
}