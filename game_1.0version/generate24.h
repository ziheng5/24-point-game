#ifndef GENERATE24_H
#define GENERATE24_H
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <random>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
std::vector<std::string> generate24(int n, int VALUE, int Fixed_Number);
bool isAllDigits(const std::string& str);
std::vector<std::string> getFirstFourNumericStrings(const std::vector<std::string>& strings,int n);
#endif
//A=getFirstFourNumericStrings(generate24(int n, int VALUE, int Fixed_Number))
//A[0]
