#pragma once
#include <string>
#include "Stack.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

// Helper: precedence of operators
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

// Helper: check if character is operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Helper: check if character is operand
bool isOperand(char ch) {
    return std::isalnum(ch);
}

// Convert infix to postfix
std::string infixToPostfix(const std::string& infix) {
    Stack<char> opStack;
    std::string postfix;
    for (char ch : infix) {
        if (isOperand(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();
        } else if (isOperator(ch)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch);
        }
    }
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}

// Evaluate postfix expression (single-digit operands)
int evaluatePostfix(const std::string& postfix) {
    Stack<int> valStack;
    for (char ch : postfix) {
        if (std::isdigit(ch)) {
            valStack.push(ch - '0');
        } else if (isOperator(ch)) {
            if (valStack.size() < 2) throw std::runtime_error("Invalid postfix expression");
            int b = valStack.top(); valStack.pop();
            int a = valStack.top(); valStack.pop();
            switch (ch) {
                case '+': valStack.push(a + b); break;
                case '-': valStack.push(a - b); break;
                case '*': valStack.push(a * b); break;
                case '/': valStack.push(a / b); break;
                case '^': valStack.push(static_cast<int>(pow(a, b))); break;
            }
        }
    }
    if (valStack.size() != 1) throw std::runtime_error("Invalid postfix expression");
    return valStack.top();
}

// Convert postfix to infix
std::string postfixToInfix(const std::string& postfix) {
    Stack<std::string> exprStack;
    for (char ch : postfix) {
        if (isOperand(ch)) {
            exprStack.push(std::string(1, ch));
        } else if (isOperator(ch)) {
            if (exprStack.size() < 2) throw std::runtime_error("Invalid postfix expression");
            std::string b = exprStack.top(); exprStack.pop();
            std::string a = exprStack.top(); exprStack.pop();
            std::string expr = "(" + a + ch + b + ")";
            exprStack.push(expr);
        }
    }
    if (exprStack.size() != 1) throw std::runtime_error("Invalid postfix expression");
    return exprStack.top();
}
char swapBracket(char ch) {
    if (ch == '(') return ')';
    if (ch == ')') return '(';
    return ch;
}
string infixToPrefix(string infix) {
    // Step 1: Reverse the infix expression
    reverse(infix.begin(), infix.end());

    // Step 2: Swap brackets
    for (char &ch : infix)
        ch = swapBracket(ch);

    // Step 3: Convert reversed infix to postfix
    string postfix = infixToPostfix(infix);

    // Step 4: Reverse postfix to get prefix
    reverse(postfix.begin(), postfix.end());

    return postfix;
}
