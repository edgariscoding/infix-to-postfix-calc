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
#include <deque>
#include <cmath>

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

void infixToPostfix(std::string& infix, std::stack<std::string>& operatorStack, std::deque<std::string>& postfixQueue) {
    std::string delimiter = " ";
    std::locale loc;
    size_t position = 0;
    std::string token;
    std::string temp;
    while ((position = infix.find(delimiter)) != std::string::npos) {
        token = infix.substr(0, position);
        if (token.find_first_of("()^%/*+-") != std::string::npos) {
            // Input is an operator
            if (token == "(") {
                // Current operator is an opening parenthesis
                operatorStack.push(token);
            }
            else if (token == ")") {
                // Current operator is a closing parenthesis
                while (!operatorStack.empty() && operatorStack.top() != "(") {
                    temp = operatorStack.top();
                    postfixQueue.push_back(temp);
                    operatorStack.pop();
                }
                if (operatorStack.top() == "(") {
                    operatorStack.pop();
                }
            }
            else {
                // Current operator is NOT a parenthesis
                if (operatorStack.empty()) {
                    operatorStack.push(token);
                }
                else {
                    while (!operatorStack.empty() && operatorStack.top() != "(" &&
                           getWeight(token) <= getWeight(operatorStack.top())) {
                        temp = operatorStack.top();
                        postfixQueue.push_back(temp);
                        operatorStack.pop();
                    }
                    operatorStack.push(token);
                }
            }
        }
        else {
            // Input is an operand
            postfixQueue.push_back(token);
        }

        infix.erase(0, position + delimiter.length());
    }
    postfixQueue.push_back(infix);
    while (!operatorStack.empty()) {
        temp = operatorStack.top();
        postfixQueue.push_back(temp);
        operatorStack.pop();
    }
}

void printQueue(std::deque<std::string> pQueue) {
    while (!pQueue.empty()) {
        std::cout << pQueue.front() << " ";
        pQueue.pop_front();
    }
    std::cout << std::endl;
}

double calculatePostfix(std::deque<std::string>& postfixQueue) {
    std::string op1, op2;
    double result = 0;
    std::stack<std::string> operandStack;
    std::string temp;

    while (!postfixQueue.empty()) {
        if (postfixQueue.front().find_first_of("()^%/*+-") != std::string::npos) {
            op1 = operandStack.top();
            operandStack.pop();
            op2 = operandStack.top();
            operandStack.pop();

            if (postfixQueue.front() == "^") {
                result = pow(std::stod(op1), std::stod(op2));
                std::cout << result << std::endl;
            }
            else if (postfixQueue.front() == "%") {
                result = fmod(std::stod(op1), std::stod(op2));
                std::cout << result << std::endl;
            }
            else if (postfixQueue.front() == "*") {
                result = std::stod(op1) * std::stod(op2);
                std::cout << result << std::endl;
            }
            else if (postfixQueue.front() == "/") {
                result = std::stod(op1) / std::stod(op2);
                std::cout << result << std::endl;
            }
            else if (postfixQueue.front() == "+") {
                result = std::stod(op1) + std::stod(op2);
                std::cout << result << std::endl;
            }
            else if (postfixQueue.front() == "-") {
                result = std::stod(op1) - std::stod(op2);
                std::cout << result << std::endl;
            }

            // Push the result
            operandStack.push(std::to_string(result));
        }
        else {
            // Is operand
            temp = postfixQueue.front();
            operandStack.push(temp);
            // TODO: The correct element in operatorStack is not popped.
            postfixQueue.pop_front();
        }
    }
    return std::stod(operandStack.top());
}

int main() {
    std::cout << "Enter a valid infix expression: " << std::endl;
    std::string infix = "( 20.4 + 3 ) ^ -5"; // Temp "input"
    //std::getline(std::cin, infix);

    std::stack<std::string> operatorStack;
    std::deque<std::string> postfixQueue;

    infixToPostfix(infix, operatorStack, postfixQueue);
    printQueue(postfixQueue);
    std::cout << calculatePostfix(postfixQueue);

    return 0;
}