// ==================================================
// Name: Edgar Sanchez
// Course: Data Structs & Algorithms
// Program: 01
// Due Date: 10/05/2017 @ 11:59PM
// Summary: Infix to postfix converter and calculator
// ==================================================
#include <iostream>
#include <cstring>
#include <stack>
#include <queue>

int getWeight(const std::string &x) {
    if (x == "^") {
        return 4;
    }
    else if ( x == "%") {
        return 3;
    }
    else if ( x == "*" || x == "/") {
        return 2;
    }
    else if ( x == "+" || x == "-") {
        return 1;
    }
    return -1;
}

void infixToPostfix(std::string& infix, std::stack<std::string>& operatorStack, std::queue<std::string>& postfixQueue) {
    std::string delimiter = " ";
    std::locale loc;
    size_t position = 0;
    std::string token;
    std::string temp;
    while ((position = infix.find(delimiter)) != std::string::npos) {
        token = infix.substr(0, position);

        if (token.find_first_of("()^%/*+-") != std::string::npos) {
            // Input is an operator

            // Current operator is a parenthesis
            if (token == "(") {
                operatorStack.push(token);
            }
            else if (token == ")") {
                while (!operatorStack.empty() && operatorStack.top() != "(") {
                    temp = operatorStack.top();
                    postfixQueue.push(temp);
                    operatorStack.pop();
                }
                if (operatorStack.top() == "(") {
                    operatorStack.pop();
                }
            }
            else {
                // Current operator is NOT a parenthesis
                //getWeight(token);
                if (operatorStack.empty()) {
                    operatorStack.push(token);
                }
                else {
                    while (!operatorStack.empty() && operatorStack.top() != "(" &&
                           getWeight(token) <= getWeight(operatorStack.top())) {
                        temp = operatorStack.top();
                        postfixQueue.push(temp);
                        operatorStack.pop();
                    }
                    operatorStack.push(token);
                }
            }
        }
        else {
            // Input is an operand
            postfixQueue.push(token);
            //std::cout << std::stod(token, nullptr) << std::endl;
        }

        infix.erase(0, position + delimiter.length());
    }
    postfixQueue.push(infix);
    while (!operatorStack.empty()) {
        temp = operatorStack.top();
        postfixQueue.push(temp);
        operatorStack.pop();
    }
}

void printQueue(std::queue<std::string> q)
{
    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Enter a valid infix expression: " << std::endl;
    std::string infix = "( 20.4 + 3 ) ^ -5"; // Temp "input"
    //std::getline(std::cin, infix);

    std::stack<std::string> operatorStack;
    std::queue<std::string> postfixQueue;

    infixToPostfix(infix, operatorStack, postfixQueue);

    printQueue(postfixQueue);

    return 0;
}