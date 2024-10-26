#ifndef DETECT24_H
#define DETECT24_H
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <random>
struct Result {
    bool isPossible; // 是否能构成目标值
    std::vector<std::string> expressions; // 构成的表达式
};

Result Find(std::vector<double>& numbers, std::vector<std::string>& expressions, int n, double VOLUE);

#endif // DETECT24_H