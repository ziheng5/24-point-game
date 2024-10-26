#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <functional>
#include"equation.h"
using namespace std;
int calculate(const string& expr) {
    stack<int> num;
    stack<char> op;

    auto eval = [&num, &op]() {
        int b = num.top();
        num.pop();
        int a = num.top();
        num.pop();
        char c = op.top();
        op.pop();
        if (c == '+') num.push(a + b);
        else if (c == '-') num.push(a - b);
        else if (c == '*') num.push(a * b);
        else if (c == '/') {
            if (b != 0) num.push(a / b);
            else throw invalid_argument("Division by zero.");
        }
    };

    map<char, int> mp = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

    for (size_t i = 0; i < expr.size(); ++i) {
        if (isdigit(expr[i])) {
            int operand = 0;
            while (i < expr.size() && isdigit(expr[i])) {
                operand = operand * 10 + (expr[i] - '0');
                ++i;
            }
            num.push(operand);
            --i;
        }
        else if (expr[i] == '(') {
            op.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!op.empty() && op.top() != '(') eval();
            if (!op.empty()) op.pop();
        }
        else {
            while (!op.empty() && op.top() != '(' && mp[op.top()] >= mp[expr[i]])
                eval();
            op.push(expr[i]);
        }
    }
    while (!op.empty()) eval();

    if (num.empty()) throw runtime_error("No result found.");
    return num.top();
}

double evaluate(const std::string& expr) {
    std::regex opsRegex(R"([+\-*/()])");
    std::sregex_token_iterator it(expr.begin(), expr.end(), opsRegex, -1);
    std::vector<std::string> tokens{it, {}};

    std::vector<double> values;
    std::vector<char> operators;

    for (const auto& token : tokens) {
        if (isdigit(token[0])) {
            values.push_back(std::stod(token));
        }
        else if (token.size() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
            operators.push_back(token[0]);
        }
    }

    double result = values[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        double nextValue = values[i + 1];
        switch (operators[i]) {
        case '+':
            result += nextValue;
            break;
        case '-':
            result -= nextValue;
            break;
        case '*':
            result *= nextValue;
            break;
        case '/':
            if (nextValue != 0) {
                result /= nextValue;
            }
            else {
                throw std::runtime_error("Division by zero.");
            }
            break;
        }
    }

    return result;
}
// 提取数字并计算表达式
bool evaluateExpression(const std::string& expr, std::vector<int>& numbers) {
    std::regex digitRegex(R"(\d+)");
    std::smatch matches;
    std::string::const_iterator searchStart(expr.cbegin());

    // 提取所有数字
    while (std::regex_search(searchStart, expr.end(), matches, digitRegex)) {
        numbers.push_back(std::stoi(matches[0]));
        searchStart = matches.suffix().first;
    }

    // 计算表达式的值
    std::string evalExpr = expr.substr(0, expr.find('='));
    return evaluate(evalExpr) == std::stod(expr.substr(expr.find('=') + 1));
}

// 递归计算表达式的值

