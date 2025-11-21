// The 
// largest 
// magnitude 
// of 
// integers 
// is 
// limited, 
// so 
// we 
// cannot 
// add 
// 18,274,364,583,929,273,748,459,595,684,373 and 8,129,498,165,026,350,236, because integer 
// variables cannot hold such large values, let alone their sum. The problem can be solved if we treat these 
// numbers as strings of numerals, store the numbers corresponding to these numerals on two stacks, and 
// then perform addition by popping numbers from the stacks. The pseudocode for this algorithm is as 
// follows: 
// addingLargeNumbers() 
// a. read the numerals (digits) of the first number and store the numbers corresponding to them on 
// one stack; 
// b. read the numerals (digits) of the second number and store the numbers corresponding to them 
// on another stack; 
// c. carry = 0; 
// d. while at least one stack is not empty 
// i. 
// pop a number from each nonempty stack and add them to carry; 
// ii. 
// iii. 
// push the unit part on the result stack; 
// store carry in carry; 
// e. push carry on the result stack if it is not zero; 
// f. 
// pop numbers from the result stack and display them; 

// The step-by-step working of the above example is explained below: 
// 1. Numbers corresponding to digits composing the first number are pushed onto operandStack1, 
// and numbers corresponding to the digits of 3,784 are pushed onto operandStack2. Note the 
// order of digits on the stacks. 
// 2. Numbers 2 and 4 are popped from the stacks, and the result, 6, is pushed onto resultStack. 
// 3. Numbers 9 and 8 are popped from the stacks, and the unit part of their sum, 7, is pushed onto 
// resultStack; the tens part of the result, number 1, is retained as a carry in the variable carry for 
// subsequent addition. 
// 4. Numbers 5 and 7 are popped from the stacks, added to the carry, and the unit part of the result, 
// 3, is pushed onto resultStack, and the carry, 1, becomes a value of the variable carry. 
// 5. One stack is empty, so a number is popped from the nonempty stack, added to carry, and the 
// result is stored on resultStack. 
// 6. Both operand stacks are empty, so the numbers from resultStack are popped and printed as the 
// final result. 
    // for(char i:s1)
    // {
    //     st1.push(i);

    // }
    // for(char i:s2)
    // {
    //     st1.push(i);
    // }
    // int carry=0;
    

#include <iostream>
#include "Stack.h"
#include "ExpressionEval.h"
#include <string>
using namespace std;

Stack<int> adding(string s1,string s2)
{
    Stack<int> st1,st2;
    Stack<int> r;
    for(char i:s1)
    {
        st1.push(i);
    }
    for(char i:s2)
    {
        st2.push(i);
    }
    int carry=0;
    while(!st1.empty() || !st2.empty() || carry)
    {
        int sum=carry;
        if(!st1.empty())
        {
            sum+=st1.top()-'0';
            st1.pop();
        }
        if(!st2.empty())
        {
            sum+=st2.top()-'0';
            st2.pop();
        }
        carry=sum/10;
        r.push(sum%10);
    }
    return r;
}

int main() 
{
    Stack<int> out;
    out=adding("23","27");
    for(int i=0;i<out.size();i++)
    {
        cout<<out.pop();
    }

    return 0;
}
