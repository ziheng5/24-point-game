#include "generate24.h"

// n参与运算数字个数，value是目标值，fixed_number是一定会出现的一个数字
std::vector<std::string> generate24(int n, int VALUE, int Fixed_Number) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> cal(1, 4); 
    std::uniform_int_distribution<> num_gen(1, 20);
    std::string jia = "+";
    std::string jian = "-";
    std::string cheng = "*";
    std::string chu = "/";
    int random_number = cal(gen);
    int transmiss;
    int express_on;
    int trans_value=VALUE;
    std::vector<std::string> Expession;
    int First_Number = Fixed_Number;
    for (int i = 1; i <= n - 1; i++) {
        if (i == 1) {
            random_number = cal(gen);
            if (random_number == 1) {//加
                Expession.push_back(std::to_string(First_Number));
                if (trans_value - First_Number > 0) {
                    trans_value = trans_value - First_Number;

                    Expession.insert(Expession.begin(), jia);
                    Expession.insert(Expession.begin(), ")");
                }
                else
                {
                    trans_value = trans_value + First_Number;

                    Expession.insert(Expession.begin(), jian);
                    Expession.insert(Expession.begin(), ")");
                }
            }
            if (random_number == 2) {//减
                Expession.push_back(std::to_string(First_Number));
                trans_value = trans_value + First_Number;

                Expession.insert(Expession.begin(), jian);
                Expession.insert(Expession.begin(), ")");
            }
            if (random_number == 3) {//乘
                Expession.push_back(std::to_string(First_Number));
                if (trans_value % First_Number == 0) {
                    trans_value = trans_value / First_Number;

                    Expession.insert(Expession.begin(), cheng);
                    Expession.insert(Expession.begin(), ")");
                }
                else {
                    trans_value = trans_value + First_Number;

                    Expession.insert(Expession.begin(), jian);
                    Expession.insert(Expession.begin(), ")");
                }
            }
            if (random_number == 4) {//除
                Expession.push_back(std::to_string(First_Number));
                trans_value = trans_value * First_Number;

                Expession.insert(Expession.begin(), chu);
                Expession.insert(Expession.begin(), ")");
            }
        }
        if (i != 1) {
            random_number = cal(gen);
            if (random_number == 1) {//加
                First_Number = num_gen(gen);
                if (trans_value - First_Number > 0) {
                    Expession.insert(Expession.begin(), std::to_string(First_Number));
                    trans_value = trans_value - First_Number;

                    Expession.insert(Expession.begin(), jia);
                    Expession.insert(Expession.begin(), ")");
                }
                else
                {
                    Expession.insert(Expession.begin(), std::to_string(First_Number));
                    trans_value = trans_value + First_Number;

                    Expession.insert(Expession.begin(), jian);
                    Expession.insert(Expession.begin(), ")");
                }
            }
            if (random_number == 2) {//减
                First_Number = num_gen(gen);
                Expession.insert(Expession.begin(), std::to_string(First_Number));
                trans_value = trans_value + First_Number;

                Expession.insert(Expession.begin(), jian);
                Expession.insert(Expession.begin(), ")");
            }
            if (random_number == 3) {//乘
                First_Number = num_gen(gen);
                if (trans_value % First_Number == 0) {
                    Expession.insert(Expession.begin(), std::to_string(First_Number));
                    trans_value = trans_value / First_Number;

                    Expession.insert(Expession.begin(), cheng);
                    Expession.insert(Expession.begin(), ")");
                }
                else {
                    Expession.insert(Expession.begin(), std::to_string(First_Number));
                    trans_value = trans_value + First_Number;

                    Expession.insert(Expession.begin(), jian);
                    Expession.insert(Expession.begin(), ")");
                }
            }
            if (random_number == 4) {//除
                First_Number = num_gen(gen);
                First_Number = cal(gen);
                Expession.insert(Expession.begin(), std::to_string(First_Number));
                trans_value = trans_value * First_Number;

                Expession.insert(Expession.begin(), chu);
                Expession.insert(Expession.begin(), ")");
            }
        }
    }
        Expession.insert(Expession.begin(), std::to_string(trans_value));
        for (int i = 1;i < n - 1;i++) {
            Expession.insert(Expession.begin(),"(");
        }
    return Expession;
}
// 判断字符串是否全由数字构成
bool isAllDigits(const std::string& str) {
    return all_of(str.begin(), str.end(), [](unsigned char c) { return std::isdigit(c); });
}

// 从向量中提取前四个纯数字字符串并返回
std::vector<std::string> getFirstFourNumericStrings(const std::vector<std::string>& strings,int n) {
    std::vector<std::string> numericStrings;
    int count = 0; // 计数器，记录已经找到的纯数字字符串数量
    for (const auto& str : strings) {
        if (isAllDigits(str)) {
            numericStrings.push_back(str);
            count++;
            // 如果已经找到4个纯数字字符串，则结束循环
            if (count == n) {
                break;
            }
        }
    }
    return numericStrings;
}
