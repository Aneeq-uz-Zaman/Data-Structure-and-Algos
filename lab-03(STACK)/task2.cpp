#include <iostream>
#include "Stack.h"
#include "ExpressionEval.h"
#include <string>
using namespace std;


bool check(int n,string s)
{
    Stack<char> st1;
    Stack<char> st2;
    int size=0;
    for(char i:s)
    {
        if(i=='a'){
            st1.push(i);
        }
        else if(i=='b'){
            st2.push(i);
        }
    }
    
    if(st1.size() != n || st2.size() != n) {
        return false; 
    }

    for(int i=0;i<n;i++)
    {
        if(st1.pop() != 'a' || st2.pop() != 'b') {
            return false; 
        }
    }

    return true; 

}
int main() 
{
    bool r=check(4,"aaabbb");
    cout<<r;

  

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
