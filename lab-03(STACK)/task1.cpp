// A palindrome is a word, phrase, number or other sequence of units that has the property of reading the 
// same in either direction. Write a program that could determine whether the given string is a palindrome. 
// Examples: 
// Palindrome Words: 
// Dad 
// 1221 
// Racecar 
// Rotator 
// Level 
// Civic 
// Palindrome phrases: 
// Too bad--I hid a boot. 
// Do geese see God? 
// Go Hang a Salami! I'm a Lasagna Hog! 
// (title of a book on palindromes by Jon Agee, 1991) 
// Note: Handle spaces and punctuation marks carefully. 
#include <iostream>
#include "Stack.h"
#include "ExpressionEval.h"
#include <string>
using namespace std;
bool ispal(const string& s)
{
    bool r=true;
    Stack<int> st1;
    Stack<int> st2;
    int size=0;
    for(char i:s)
    {
        if((i>=48&&i<=57) || (i>=65&&i<=90) || (i>=97&&i<=122) ){
            st1.push(i);
            
        }
        
    }
    for(int i=s.size()-1;i>=0;i--)
    {
        if((s[i]>=48&&s[i]<=57) || (s[i]>=65&&s[i]<=90) || (s[i]>=97&&s[i]<=122) ){
            st2.push(s[i]);
        }
    }
    cout<<st1.gettopindex();
    cout<<st2.gettopindex();
    for(int i=0;i<st1.gettopindex();i++)
    {
        // cout<<st1.pop()<<endl;
        // cout<<st2.pop();
        if(st1.pop()!=st2.pop())
        {
            r=false;
        }
    }

    return r;
}
int main() 
{
    bool r=ispal("do geese see god?");
    cout<<"result"<<r;


    // // Test Stack class
    // Stack<int> s;
    // s.push(10);
    // s.push(20);
    // std::cout << "Stack top: " << s.top() << std::endl;
    // s.pop();
    // std::cout << "Stack top after pop: " << s.top() << std::endl;
    // s.clear();
    // std::cout << "Stack empty after clear: " << (s.empty() ? "true" : "false") << std::endl;

    // // Test infix to postfix
    // std::string infix = "A+B*(C-D)";
    // std::string postfix = infixToPostfix(infix);
    // std::cout << "Infix: " << infix << "\nPostfix: " << postfix << std::endl;

    // // Test postfix evaluation
    // int result = evaluatePostfix(postfix);
    // std::cout << "Postfix Evaluation: " << result << std::endl;

    // // Test postfix to infix
    // std::string infix2 = postfixToInfix(postfix);
    // std::cout << "Postfix to Infix: " << infix2 << std::endl;

    return 0;
}
