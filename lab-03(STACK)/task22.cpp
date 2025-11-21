#include <iostream>
#include "Stack.h"
#include "ExpressionEval.h"
#include <string>
using namespace std;


bool check(string s)
{
    Stack<char> st1;
    Stack<char> st2;
    Stack<char> r;
    int size=0;
    int n1=0,n2=0;
    for(char i:s)
    {
        if(i=='a'){
            st1.push(i);
            n1++;
        }
        else if(i=='b'){
            st2.push(i);
            n2++;
        }
    }
    
    if(n1!=n2) {
        return false; 
    }
    else{
        cout<<"N="<<st1.size();
    }
    char rr='a';
    for(int i=1;i<s.size();i++)
    {
        if(s[i]=='a' && i==0)
        {
            continue;
        }
        else if(i==0 && s[i]!='a')
        {
            return false;
        }
        if(s[i]=='b')
        {
            if(s[i+1]=='a')
                false;
        }
    }
    return true; 

}
int main() 
{
    bool r=check("bbaa");
    cout<<endl;
    cout<<"Answer:"<<r;

  

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
