//
//  calculator.cpp
//  calculator
//
//  Created by hatlonely on 16/5/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "calculator.h"
#include <iostream>
#include <algorithm>
#include <cmath>

namespace hatlonely {

std::string& Trim(std::string& str) {
    int idx1 = 0;
    int idx2 = str.length() - 1;
    while (idx1 <= idx2 && isspace(str[idx1])) {
        idx1++;
    }
    while (idx1 <= idx2 && isspace(str[idx2])) {
        idx2--;
    }
    str.erase(idx2 + 1);
    str.erase(0, idx1);
    return str;
}

std::string TrimCopy(const std::string& str) {
    std::string strCopy(str);
    Trim(strCopy);
    return strCopy;
}
    
std::string& RemoveSpace(std::string& str) {
    int idx = 0;
    for (int i = 0; i < str.length(); i++) {
        if (!std::isspace(str[i])) {
            str[idx++] = str[i];
        }
    }
    return str.erase(idx);
}

std::string RemoveSpaceCopy(const std::string& str) {
    std::string strCopy(str);
    RemoveSpace(strCopy);
    return strCopy;
}
    
void SplitWithSeparators(const std::string& str, std::vector<std::string>& result, std::function<bool (char)> sepPred) {
    std::vector<std::string> tokens;
    int idx = 0;
    for (int i = 0; i < str.length(); i++) {
        if (sepPred(str[i])) {
            if (idx != i) {
                tokens.push_back(str.substr(idx, i - idx));
            }
            tokens.push_back(str.substr(i, 1));
            idx = i + 1;
        }
    }
    if (idx != str.length()) {
        tokens.push_back(str.substr(idx, str.length() - idx));
    }
    result.swap(tokens);
}
    
void Split(const std::string& str, std::vector<std::string>& result, std::function<bool (char)> sepPred) {
    std::vector<std::string> tokens;
    int idx = 0;
    for (int i = 0; i < str.length(); i++) {
        if (sepPred(str[i])) {
            if (idx != i) {
                tokens.push_back(str.substr(idx, i - idx));
            }
            idx = i + 1;
        }
    }
    if (idx != str.length()) {
        tokens.push_back(str.substr(idx, str.length() - idx));
    }
    result.swap(tokens);
}

std::unordered_map<std::string, op_info_t> Calculator::_opmap = {
    {"+", {2, [](std::vector<double>& nums) {return nums[1] + nums[0];}}},
    {"-", {2, [](std::vector<double>& nums) {return nums[1] - nums[0];}}},
    {"*", {2, [](std::vector<double>& nums) {return nums[1] * nums[0];}}},
    {"/", {2, [](std::vector<double>& nums) {return nums[1] / nums[0];}}},
    {"sin", {1, [](std::vector<double>& nums) {return std::sin(nums[0]);}}},
    {"cos", {1, [](std::vector<double>& nums) {return std::cos(nums[0]);}}},
    {"tan", {1, [](std::vector<double>& nums) {return std::tan(nums[0]);}}},
    {"asin", {1, [](std::vector<double>& nums) {return std::asin(nums[0]);}}},
    {"acos", {1, [](std::vector<double>& nums) {return std::acos(nums[0]);}}},
    {"atan", {1, [](std::vector<double>& nums) {return std::atan(nums[0]);}}},
    {"pow", {2, [](std::vector<double>& nums) {return std::pow(nums[1], nums[0]);}}},
    {"sqrt", {1, [](std::vector<double>& nums) {return std::sqrt(nums[0]);}}},
    {"abs", {1, [](std::vector<double>& nums) {return std::fabs(nums[0]);}}},
};

std::unordered_map<std::string, double> Calculator::_constant = {
    {"PI", M_PI},
    {"E", M_E},
};
    
std::unordered_map<std::string, int> Calculator::_priority = {
    {"(", 0},
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"sin", 9},
    {"cos", 9},
    {"tan", 9},
    {"asin", 9},
    {"acos", 9},
    {"atan", 9},
    {"pow", 9},
    {"sqrt", 9},
    {"abs", 9},
};
    
std::unordered_set<char> Calculator::_separators = {
    '+', '-', '*', '/', ',', '(', ')'
};
  
bool Calculator::calculate(const std::string& expression, double& result) {
    std::vector<std::string> environment;
    Split(expression, environment, [](char ch) {return ch == '|';});
    std::string valueExpression = environment.back();
    environment.pop_back();
    return calculate(environment, valueExpression, result);
}

bool Calculator::calculate(std::unordered_map<std::string, double> values,
                           const std::string& expression, double& result) {
    std::vector<token_t> infix;
    std::vector<token_t> postfix;
    return syntaxAnalysis(values, expression, infix) && infixToPostfix(infix, postfix) && evaluate(values, postfix, result);
}
    
bool Calculator::calculate(const std::vector<std::string>& environment, const std::string& expression, double& result) {
    std::unordered_map<std::string, double> values;
    for (const auto& equation : environment) {
        auto idx = equation.find('=');
        if (idx == std::string::npos) {
            std::cerr << "未找到等号 [" << equation << "]" << std::endl;
            return false;
        }
        std::string key   = TrimCopy(equation.substr(0, idx));
        std::string valueExpression = TrimCopy(equation.substr(idx + 1));
        double valueResult = 0.0;
        if (!calculate(values, valueExpression, valueResult)) {
            std::cerr << "表达式错误 [" << equation << "]" << std::endl;
            return false;
        }
        values[key] = valueResult;
    }
    
    return calculate(values, expression, result);
}
    
bool Calculator::syntaxAnalysis(std::unordered_map<std::string, double> values,
                                const std::string& expression, std::vector<token_t>& infix) {
    std::string expressionWithoutSpace = RemoveSpaceCopy(expression);
    std::vector<std::string> tokenStrs;
    SplitWithSeparators(expressionWithoutSpace, tokenStrs, [](char ch) {return _separators.count(ch) > 0;});
    
    for (int i = 0; i < tokenStrs.size(); i++) {
        token_t token;
        const std::string& tokenStr = tokenStrs[i];
        token.identify = tokenStr;
        // "-"需要单独处理，因为"-"有两种含义，减号或者负号
        if (tokenStr == "-") {
            // 如果前一个token是一个数或者是一个括号，那么肯定是减号
            if (!infix.empty() && (infix.back().type == TokenType::kNumber || infix.back().type == TokenType::kBracket)) {
                token.type = TokenType::kOperation;
                infix.push_back(token);
            } else {
                // 如果是负数，等价于乘以-1 [-x == -1 * x]
                // 不直接写成-x，是因为x有可能为一个包含在括号内的表达式
                token_t token1;
                token_t token2;
                token1.type     = TokenType::kNumber;
                token1.identify = "-1";
                token1.number   = -1;
                token2.type     = TokenType::kOperation;
                token2.identify = "*";
                infix.push_back(token1);
                infix.push_back(token2);
            }
        } else if (tokenStr == ",") {
            // 逗号是函数的参数，将逗号替换成")("，逗号之间的表达式会作为一个整体求值
            token_t token1;
            token_t token2;
            token1.type = TokenType::kBracket;
            token1.identify = ")";
            token2.type = TokenType::kBracket;
            token2.identify = "(";
            infix.push_back(token1);
            infix.push_back(token2);
        } else if (_opmap.count(tokenStr) > 0) {
            token.type = TokenType::kOperation;
            infix.push_back(token);
        } else if (std::all_of(tokenStr.begin(), tokenStr.end(), [](char ch) {
            return isnumber(ch) || ch == '-' || ch == '.' || ch == 'e';
        })) {
            token.type = TokenType::kNumber;
            token.number = std::stold(tokenStr);
            infix.push_back(token);
        } else if (tokenStr == "(" || tokenStr == ")") {
            token.type = TokenType::kBracket;
            infix.push_back(token);
        } else if (_constant.count(tokenStr) > 0) {
            token.type = TokenType::kNumber;
            token.number = _constant[tokenStr];
            infix.push_back(token);
        } else if (values.count(tokenStr) > 0) {
            token.type = TokenType::kNumber;
            token.number = values[tokenStr];
            infix.push_back(token);
        } else {
            std::cerr << "未定义的标识符 [" << tokenStr << "]" << std::endl;
            return false;
        }
    }
    
    return true;
}
    
bool Calculator::infixToPostfix(const std::vector<token_t>& infix, std::vector<token_t>& postfix) {
//    for (auto& token : infix) {
//        std::cout << token.toString() << ", ";
//    }
//    std::cout << std::endl;

    std::stack<token_t> tokens;
    for (auto& token : infix) {
        if (token.type == TokenType::kNumber) {
            postfix.push_back(token);
        } else if (token.type == TokenType::kOperation) {
            while (!tokens.empty() && _priority[token.identify] <= _priority[tokens.top().identify]) {
                postfix.push_back(tokens.top());
                tokens.pop();
            }
            tokens.push(token);
        } else if (token.type == TokenType::kBracket) {
            if (token.identify == "(") {
                tokens.push(token);
            } else if (token.identify == ")") {
                while (!tokens.empty() && tokens.top().identify != "(") {
                    postfix.push_back(tokens.top());
                    tokens.pop();
                }
                if (tokens.empty()) {
                    std::cout << "括号不匹配" << std::endl;
                    return false;
                }
                tokens.pop();
            }
        }
    }
    
    while (!tokens.empty()) {
        postfix.push_back(tokens.top());
        tokens.pop();
    }
    
    return true;
}
    
bool Calculator::evaluate(std::unordered_map<std::string, double> values,
                          std::vector<token_t>& postfix, double& result) {
//    for (auto& token : postfix) {
//        std::cout << token.toString() << ", ";
//    }
//    std::cout << std::endl;

    std::stack<token_t> tokens;
    for (auto& token : postfix) {
        if (token.type == TokenType::kNumber) {
            tokens.push(token);
        } else if (token.type == TokenType::kOperation) {
            op_info_t info = _opmap[token.identify];
            std::vector<double> nums;
            for (int i = 0; i < info.opnum; i++) {
                if (tokens.empty()) {
                    std::cout << "操作数个数不匹配" << std::endl;
                    return false;
                }
                nums.push_back(tokens.top().number);
                tokens.pop();
            }
            token_t resultToken;
            resultToken.type = TokenType::kNumber;
            resultToken.number = info.func(nums);
            tokens.push(resultToken);
        }
    }
    
    if (tokens.size() != 1) {
        std::cout << "计算结果不匹配" << std::endl;
        return false;
    }
    result = tokens.top().number;
    
    return true;
}
    
}
