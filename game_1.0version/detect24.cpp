#include "detect24.h"
#include <cmath>
#include <iostream>

std::string trimDecimal(const std::string& str) {
    // 找到小数点的位置
    size_t decimalPoint = str.find('.');
    if (decimalPoint != std::string::npos) {
        // 截取小数点之前的部分
        return str.substr(0, decimalPoint);
    }
    else {
        // 如果没有小数点，返回原字符串
        return str;
    }
}

// 实现Find函数
Result Find(std::vector<double>& numbers, std::vector<std::string>& expressions, int n, double VOLUE) {
    Result result;
    result.isPossible = false;

    if (n == 1) {
        if (std::fabs(numbers[0] - VOLUE) <= 1e-6) {
            result.isPossible = true;
            result.expressions.push_back(expressions[0]);
            return result;
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double a = numbers[i];
                double b = numbers[j];
                std::string expressiona = expressions[i];
                std::string expressionb = expressions[j];
                numbers[j] = numbers[n - 1];
                expressions[j] = expressions[n - 1];

                // 加法
                expressions[i] = '(' + trimDecimal(expressiona) + '+' + trimDecimal(expressionb) + ')';
                numbers[i] = a + b;
                Result subResult = Find(numbers, expressions, n - 1, VOLUE);
                if (subResult.isPossible) {
                    result.isPossible = true;
                    result.expressions.insert(result.expressions.end(), subResult.expressions.begin(), subResult.expressions.end());
                }

                // 减法
                expressions[i] = '(' + trimDecimal(expressiona) + '-' + trimDecimal(expressionb) + ')';
                numbers[i] = a - b;
                subResult = Find(numbers, expressions, n - 1, VOLUE);
                if (subResult.isPossible) {
                    result.isPossible = true;
                    result.expressions.insert(result.expressions.end(), subResult.expressions.begin(), subResult.expressions.end());
                }

                // 乘法
                expressions[i] = '(' + trimDecimal(expressiona) + '*' + trimDecimal(expressionb) + ')';
                numbers[i] = a * b;
                subResult = Find(numbers, expressions, n - 1, VOLUE);
                if (subResult.isPossible) {
                    result.isPossible = true;
                    result.expressions.insert(result.expressions.end(), subResult.expressions.begin(), subResult.expressions.end());
                }

                // 除法
                if (b != 0) {
                    expressions[i] = '(' + trimDecimal(expressiona) + '/' + trimDecimal(expressionb) + ')';
                    numbers[i] = a / b;
                    subResult = Find(numbers, expressions, n - 1, VOLUE);
                    if (subResult.isPossible) {
                        result.isPossible = true;
                        result.expressions.insert(result.expressions.end(), subResult.expressions.begin(), subResult.expressions.end());
                    }
                }

                // 恢复原始值
                numbers[i] = a;
                numbers[j] = b;
                expressions[i] = expressiona;
                expressions[j] = expressionb;
            }
        }
    }
    return result;
}