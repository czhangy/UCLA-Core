//
//  eval.cpp
//  hw2
//
//  Created by Charles Zhang on 2/2/20.
//  Copyright © 2020 Charles Zhang. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>

using namespace std;

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int evaluate(string infix, const Map& values, string& postfix, int& result) {
    
    // remove spaces
    string newString = "";
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] != ' ') {
            newString += infix[i];
        }
    }
    
    // to postfix
    postfix = "";
    stack<char> operators;
    bool notInValue = false;
    for (int i = 0; i < newString.size(); i++) {
        switch(newString[i]) {
            case '(':
                if (i + 1 == newString.size() || isOperator(newString[i + 1]) || newString[i + 1] == ')') return 1;
                operators.push(newString[i]);
                break;
            case ')':
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                if (operators.empty()) return 1; // if there wasn't a '(' preceding the ')'
                operators.pop();
                break;
            case '+':
            case '-':
                if (i + 1 == newString.size() || isOperator(newString[i + 1]) || newString[i + 1] == ')') return 1;
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(newString[i]);
                break;
            case '*':
            case '/':
                if (i + 1 == newString.size() || isOperator(newString[i + 1]) || newString[i + 1] == ')') return 1;
                while (!operators.empty() && operators.top() != '(' && operators.top() != '+' && operators.top() != '-') {
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(newString[i]);
                break;
            default:
                if (!isalpha(newString[i]) || !islower(newString[i])) return 1;
                else if (!values.contains(newString[i])) { // if syntactically valid, but not in values map
                    postfix += newString[i];
                    notInValue = true;
                    break;
                } else if ((i - 1 >= 0 && isalpha(newString[i - 1])) || (i + 1 < newString.size() && isalpha(newString[i + 1]))) { // a letter cannot precede/be preceded by another letter
                    return 1;
                } else {
                    postfix += newString[i];
                    break;
                }
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    if (notInValue) return 2;
    
    // evaluate postfix
    stack<int> operands;
    int operand1;
    int operand2;
    int insert;
    for (int i = 0; i < postfix.size(); i++) {
        if (values.contains(postfix[i])) {
            values.get(postfix[i], insert);
            operands.push(insert);
        } else {
            if (operands.size() < 2) return 1; // check if there are enough operands remaining
            operand2 = operands.top();
            operands.pop();
            operand1 = operands.top();
            operands.pop();
            if (operand2 == 0 && postfix[i] == '/') return 3; // check for division by 0
            else if (postfix[i] == '+') operands.push(operand1 + operand2);
            else if (postfix[i] == '-') operands.push(operand1 - operand2);
            else if (postfix[i] == '*') operands.push(operand1 * operand2);
            else operands.push(operand1 / operand2);
        }
    }
    if (operands.size() != 1) return 1; // if not enough operators to reduce size to 1 operand
    result = operands.top();
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  && pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999); // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2 && pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 && pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  && pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  && pf == "a"  &&  answer == 3);
    assert(evaluate(")(", m, pf, answer) == 1);
    assert(evaluate("+)(", m, pf, answer) == 1);
    assert(evaluate("o+-*y", m, pf, answer) == 1);
    assert(evaluate("(a+)", m, pf, answer) == 1);
    assert(evaluate("+ac", m, pf, answer) == 1);
    cout << "Passed all tests" << endl;
}
